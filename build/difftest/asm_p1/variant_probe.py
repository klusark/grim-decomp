"""variant_probe.py <overrides.c> <slice.s>: experiment variant for FUN_00410330: the game runs the sliced original
(orig_FUN_00410330) and the C (renamed p1_c_FUN_00410330) on the same input, compares the pixels of every span and the
four globals, and logs the first mismatches to C:/Users/Joel/grimP1_run/probe330.txt."""
import sys
p, s = sys.argv[1], sys.argv[2]
t = open(p).read()
key = '#include "functions.h"\n'
t = t.replace(key, key + "#define FUN_00410330 p1_c_FUN_00410330\n", 1)
asm = open(s).read()
lines = "".join('"%s\\n"\n' % l.replace("\\", "\\\\").replace('"', '\\"') for l in asm.split("\n"))
tail = r'''
#undef FUN_00410330
__asm__(
%s".att_syntax prefix\n");
extern void orig_FUN_00410330(int);
extern int p1_vsprintf(char *, const char *, __builtin_va_list) __asm__("_vsprintf");
static void probe_log(const char *fmt, ...)
{
    char b[600];
    unsigned w;
    void *hf;
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    p1_vsprintf(b, fmt, ap);
    __builtin_va_end(ap);
    hf = (void *)CreateFileA("C:\\Users\\Joel\\grimP1_run\\probe330.txt", 4, 3, 0, 4, 0x80, 0);
    if (hf != (void *)-1) { WriteFile(hf, b, __builtin_strlen(b), &w, 0); CloseHandle(hf); }
}
static int probe_calls, probe_bad;
static unsigned char probe_buf[64][4096], probe_save[64][4096];
void FUN_00410330(int p)
{
    int bpp = P1_BPP(), k, sp, n;
    int sz = bpp == 8 ? 1 : 2;
    uint g[4], h[4];
    void *f;
    probe_calls++;
    (void)f;
    if (probe_calls == 1 || probe_calls %% 20000 == 0)
        probe_log("calls %%d bpp %%d bad %%d\n", probe_calls, bpp, probe_bad);
    if ((bpp != 8 && bpp != 16) || probe_bad > 40) { orig_FUN_00410330(p); return; }
    /* save the pixels */
    for (k = 0, sp = P1_I32(p + 0x1b8); sp && k < 64; sp = P1_I32(sp + 0x28), k++) {
        int cv = P1_CANVAS();
        char *d = bpp == 8 ? (char *)(P1_I32(sp + 8) * P1_I32(cv + 0x18) + P1_I32(cv + 0x5c) + P1_I32(sp))
                           : (char *)(P1_I32(cv + 0x5c) + (P1_I32(sp + 8) * (int)(P1_U32(cv + 0x18) >> 1) + P1_I32(sp)) * 2);
        n = P1_I32(sp + 4) * sz; if (n > 4096 || n < 0) n = 0;
        memcpy(probe_save[k], d, n);
    }
    orig_FUN_00410330(p);
    g[0] = DAT_008ddf40; g[1] = UINT_008ddf0c; g[2] = UINT_008ddf30; g[3] = UINT_008ddf24;
    for (k = 0, sp = P1_I32(p + 0x1b8); sp && k < 64; sp = P1_I32(sp + 0x28), k++) {
        int cv = P1_CANVAS();
        char *d = bpp == 8 ? (char *)(P1_I32(sp + 8) * P1_I32(cv + 0x18) + P1_I32(cv + 0x5c) + P1_I32(sp))
                           : (char *)(P1_I32(cv + 0x5c) + (P1_I32(sp + 8) * (int)(P1_U32(cv + 0x18) >> 1) + P1_I32(sp)) * 2);
        n = P1_I32(sp + 4) * sz; if (n > 4096 || n < 0) n = 0;
        memcpy(probe_buf[k], d, n);
        memcpy(d, probe_save[k], n);
    }
    p1_c_FUN_00410330(p);
    h[0] = DAT_008ddf40; h[1] = UINT_008ddf0c; h[2] = UINT_008ddf30; h[3] = UINT_008ddf24;
    for (k = 0, sp = P1_I32(p + 0x1b8); sp && k < 64; sp = P1_I32(sp + 0x28), k++) {
        int cv = P1_CANVAS();
        char *d = bpp == 8 ? (char *)(P1_I32(sp + 8) * P1_I32(cv + 0x18) + P1_I32(cv + 0x5c) + P1_I32(sp))
                           : (char *)(P1_I32(cv + 0x5c) + (P1_I32(sp + 8) * (int)(P1_U32(cv + 0x18) >> 1) + P1_I32(sp)) * 2);
        n = P1_I32(sp + 4) * sz; if (n > 4096 || n < 0) n = 0;
        if (memcmp(probe_buf[k], d, n) || memcmp(g, h, sizeof g)) {
            probe_bad++;
            {
                probe_log("call %%d bpp %%d span %%d x %%d n %%d row %%d l %%08x dl %%08x col %%02x tab0c %%08x tab30 %%08x g %%08x/%%08x %%08x/%%08x\n",
                        probe_calls, bpp, k, P1_I32(sp), P1_I32(sp + 4), P1_I32(sp + 8), P1_I32(sp + 0x20), P1_I32(sp + 0x24),
                        P1_U8(p + 0x1d0), P1_I32(p + 0x1dc), P1_I32(p + 0x1e0), g[1], h[1], g[2], h[2]);
            }
            break;
        }
    }
}
''' % lines
i = t.rindex("#endif /* GRIM_EXE */")
t = t[:i] + tail + t[i:]
open(p, "w", newline="\n").write(t)
