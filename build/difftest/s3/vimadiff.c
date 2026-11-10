/* Movie sound: run the Smush "Wave" codec (module "LECMODULE insane_wave flobdec", FUN_004cbc00 -> FUN_004cbf50, the VIMA /
 * IMA ADPCM decoder) of a program image on the Wave chunks of a real SNM movie and record what it hands to the SOUND service.
 * docs/notes/s3.md.
 *
 * The image (the original GRIMFANDANGO.EXE or a rebuilt grimfandango.exe) is mapped at its preferred base (0x400000) like the
 * Windows loader would, without imports, relocations or start-up code: the codec calls nothing but FUN_004cbf50 and the
 * SOUND callback, and its state is plain globals of the image (every import slot is pointed at a function that exits).
 * Build (32 bit; the program must not occupy 0x400000-0xcfffff itself, and its main thread stack must be small enough to be
 * placed below 0x400000; it starts a suspended copy of itself and reserves the range there before that copy runs):
 *   /c/msys64/mingw32/bin/gcc -O1 -w vimadiff.c -o vimadiff.exe -Wl,--image-base=0x30000000 -Wl,--disable-dynamicbase \
 *       -Wl,--stack,0x80000
 *
 * usage: vimadiff <image> <FUN_004cbc00> <g_dwSoundServices> <g_pDWave_outputBuffer> <UINT_008d7860> <total> <waves> <out>
 *   addresses in hex (the original's, or nm's for a rebuilt image); <total> = the sample total of the FLHD Wave entry
 *   (UINT_008d7860, written by FUN_004cbbe0); <waves> = u32 count, then u32 size + payload per Wave chunk (snmparse.py);
 *   <out> gets, per chunk: "CALL" u32 len + the buffer passed to the callback (header + PCM, len = BE size field + 8), then
 *   "RET " u32 return value.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

static FILE *out;
static unsigned char *pcmbuf;

static void bad_import(void)
{
    fprintf(stderr, "the codec called an import\n");
    exit(3);
}

static unsigned be32(const unsigned char *p) { return (unsigned)p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]; }

static int __cdecl sound_cb(unsigned char *buf, int a, int b, int c, int d)
{
    unsigned n = be32(buf + 4) + 8;
    if (n > 500000) n = 500000;
    fwrite("CALL", 1, 4, out);
    fwrite(&n, 4, 1, out);
    fwrite(buf, 1, n, out);
    (void)a; (void)b; (void)c; (void)d;
    return 0;
}

static void *cbtable[4] = {(void *)sound_cb, 0, 0, 0};

int main(int argc, char **argv)
{
    int child = argc == 10 && !strcmp(argv[9], "--child");
    if (argc != 9 && !child) {
        fprintf(stderr, "usage: vimadiff <image> <fn> <p_cb> <p_buf> <p_total> <total> <waves> <out>\n");
        return 2;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror(argv[1]); return 2; }
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char *file = malloc(fsz);
    fread(file, 1, fsz, f);
    fclose(f);
    IMAGE_NT_HEADERS32 *nt = (IMAGE_NT_HEADERS32 *)(file + ((IMAGE_DOS_HEADER *)file)->e_lfanew);
    unsigned base = nt->OptionalHeader.ImageBase, size = nt->OptionalHeader.SizeOfImage;
    if (!child) {
        /* the process heap / system allocations of a running process may already sit in 0x400000..: start a suspended copy
         * of this program, reserve the image range in it before it runs, then let it map the image there */
        char cmd[4096];
        snprintf(cmd, sizeof cmd, "%s --child", GetCommandLineA());
        STARTUPINFOA si = {sizeof si};
        PROCESS_INFORMATION pi;
        int tries;
        for (tries = 0; tries < 200; tries++) {  /* the initial stack / heap are placed at random: retry until the range is free */
            if (!CreateProcessA(0, cmd, 0, 0, TRUE, CREATE_SUSPENDED, 0, 0, &si, &pi)) {
                fprintf(stderr, "CreateProcess failed %lu\n", GetLastError());
                return 2;
            }
            if (VirtualAllocEx(pi.hProcess, (void *)base, size, MEM_RESERVE, PAGE_EXECUTE_READWRITE) == (void *)base)
                break;
            if (getenv("VIMADIFF_DEBUG")) {
                MEMORY_BASIC_INFORMATION mi;
                for (unsigned a = base; a < base + size && VirtualQueryEx(pi.hProcess, (void *)a, &mi, sizeof mi);
                     a = (unsigned)mi.BaseAddress + mi.RegionSize)
                    if (mi.State != MEM_FREE)
                        fprintf(stderr, "  in use %08x +%08lx state %lx type %lx\n", a, (unsigned long)mi.RegionSize, mi.State, mi.Type);
            }
            TerminateProcess(pi.hProcess, 2);
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        if (tries == 200) {
            fprintf(stderr, "cannot reserve %08x-%08x in a child process\n", base, base + size);
            return 2;
        }
        ResumeThread(pi.hThread);
        WaitForSingleObject(pi.hProcess, INFINITE);
        DWORD code = 2;
        GetExitCodeProcess(pi.hProcess, &code);
        return (int)code;
    }
    unsigned char *img = VirtualAlloc((void *)base, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (img != (unsigned char *)base) {
        MEMORY_BASIC_INFORMATION mi;
        VirtualQuery((void *)base, &mi, sizeof mi);
        fprintf(stderr, "cannot map %08x-%08x (in use: %p state %lx)\n", base, base + size, mi.AllocationBase, mi.State);
        return 2;
    }
    memcpy(img, file, nt->OptionalHeader.SizeOfHeaders);
    IMAGE_SECTION_HEADER *sh = IMAGE_FIRST_SECTION(nt);
    for (int i = 0; i < nt->FileHeader.NumberOfSections; i++) {
        unsigned n = sh[i].SizeOfRawData < sh[i].Misc.VirtualSize || !sh[i].Misc.VirtualSize ? sh[i].SizeOfRawData : sh[i].Misc.VirtualSize;
        if (sh[i].PointerToRawData && n)
            memcpy(img + sh[i].VirtualAddress, file + sh[i].PointerToRawData, n);
    }
    /* imports: every IAT slot -> bad_import (the codec must not call any) */
    IMAGE_DATA_DIRECTORY *dd = &nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (dd->Size) {
        for (IMAGE_IMPORT_DESCRIPTOR *id = (void *)(img + dd->VirtualAddress); id->Name; id++)
            for (unsigned *slot = (unsigned *)(img + id->FirstThunk); *slot; slot++)
                *slot = (unsigned)bad_import;
    }
    unsigned fn = strtoul(argv[2], 0, 16), p_cb = strtoul(argv[3], 0, 16), p_buf = strtoul(argv[4], 0, 16);
    unsigned p_total = strtoul(argv[5], 0, 16), total = strtoul(argv[6], 0, 0);
    pcmbuf = calloc(1, 500000);
    *(void **)p_cb = cbtable;
    *(void **)p_buf = pcmbuf;
    *(unsigned *)p_total = total;
    f = fopen(argv[7], "rb");
    if (!f) { perror(argv[7]); return 2; }
    out = fopen(argv[8], "wb");
    unsigned count;
    fread(&count, 4, 1, f);
    typedef unsigned (__cdecl *codec_fn)(unsigned, unsigned, unsigned, unsigned, unsigned, void *);
    for (unsigned k = 0; k < count; k++) {
        unsigned n;
        fread(&n, 4, 1, f);
        unsigned char *chunk = calloc(1, n + 64);
        fread(chunk, 1, n, f);
        unsigned r = ((codec_fn)fn)(0, 0, 0, 0, 0, chunk);
        fwrite("RET ", 1, 4, out);
        fwrite(&r, 4, 1, out);
        free(chunk);
    }
    fclose(out);
    printf("%u chunks\n", count);
    return 0;
}
