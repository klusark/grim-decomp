#include <windows.h>
#include "rt.h"
uint32_t g_ret, g_saved_esp;
extern char gcall_recover[];
static volatile int fault_count;
static LONG CALLBACK veh(PEXCEPTION_POINTERS e)
{
    DWORD c = e->ExceptionRecord->ExceptionCode;
    if (c == EXCEPTION_ACCESS_VIOLATION || c == EXCEPTION_ILLEGAL_INSTRUCTION || c == EXCEPTION_INT_DIVIDE_BY_ZERO ||
        c == EXCEPTION_INT_OVERFLOW || c == EXCEPTION_PRIV_INSTRUCTION || (c >= 0xc000008d && c <= 0xc0000093) ||
        c == EXCEPTION_STACK_OVERFLOW) {
        fault_count++;
        if (getenv("FAULTLOG")) printf("fault %08lx at %08lx addr %08lx\n", c, e->ContextRecord->Eip, (unsigned long)e->ExceptionRecord->ExceptionInformation[1]);
        e->ContextRecord->Eip = (DWORD)(uintptr_t)gcall_recover;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}
static void load(const char *f, uint32_t va)
{
    FILE *fp = fopen(f, "rb");
    if (!fp) { printf("cannot open %s\n", f); exit(2); }
    fseek(fp, 0, SEEK_END); long n = ftell(fp); fseek(fp, 0, SEEK_SET);
    if (fread((void *)(uintptr_t)va, 1, n, fp) != (size_t)n) { printf("short read %s\n", f); exit(2); }
    fclose(fp);
}
void rt_init(void)
{
    extern char grim_img[];
    DWORD old;
    void *p;
    if (grim_img != (char *)0x401000) { printf("image section at %p, not 0x401000\n", grim_img); exit(2); }
    if (!VirtualProtect((void *)0x401000, 0x54d000, PAGE_EXECUTE_READWRITE, &old)) { printf("VirtualProtect failed\n"); exit(2); }
    const char *root = getenv("SECTIONS") ? getenv("SECTIONS") : "raw/GRIMFANDANGO.EXE/sections";
    char b[512];
    sprintf(b, "%s/text.bin", root); load(b, 0x401000);
    sprintf(b, "%s/rdata.bin", root); load(b, 0x4d7000);
    sprintf(b, "%s/data.bin", root); load(b, 0x4dd000);
    p = VirtualAlloc(ARENA, ARENA_SZ, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (p != ARENA) { printf("cannot map arena\n"); exit(2); }
    AddVectoredExceptionHandler(1, veh);
}
static uint64_t rng = 88172645463325252ull;
uint32_t rnd(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return (uint32_t)(rng >> 16); }
uint32_t rnd_edge(void)
{
    switch (rnd() & 7) {
    case 0: return 0;
    case 1: return 0x10000u * (rnd() & 0xff);
    case 2: return (uint32_t)-(int)(rnd() & 0xffff);
    case 3: return rnd() & 0xffff;
    default: return rnd();
    }
}
size_t st_size(void) { return (DATA_HI - DATA_LO) + ARENA_SZ; }
void st_save(void *buf) { memcpy(buf, (void *)DATA_LO, DATA_HI - DATA_LO); memcpy((char *)buf + (DATA_HI - DATA_LO), ARENA, ARENA_SZ); }
void st_load(const void *buf) { memcpy((void *)DATA_LO, buf, DATA_HI - DATA_LO); memcpy(ARENA, (const char *)buf + (DATA_HI - DATA_LO), ARENA_SZ); }
long st_cmp(const void *a, const void *b, uint32_t *first)
{
    const uint32_t *x = a, *y = b; size_t n = st_size() / 4; long d = 0;
    if (!memcmp(a, b, st_size())) return 0;
    for (size_t i = 0; i < n; i++) if (x[i] != y[i]) {
        if (!d && first) { size_t off = i * 4; *first = off < DATA_HI - DATA_LO ? DATA_LO + off : 0x30000000 + off - (DATA_HI - DATA_LO); }
        d++;
    }
    return d;
}
unsigned short fpu_cw(void) { unsigned short c; __asm__ volatile("fnstcw %0" : "=m"(c)); return c; }
void fpu_set(unsigned short cw) { __asm__ volatile("fninit; fldcw %0" : : "m"(cw)); }
long st_cmp_live(const void *saved, uint32_t *first)
{
    const uint32_t *x = saved; long d = 0; size_t n1 = (DATA_HI - DATA_LO) / 4, n2 = ARENA_SZ / 4;
    if (!memcmp(saved, (void *)DATA_LO, DATA_HI - DATA_LO) && !memcmp((const char *)saved + (DATA_HI - DATA_LO), ARENA, ARENA_SZ)) return 0;
    for (size_t i = 0; i < n1; i++) if (x[i] != ((uint32_t *)DATA_LO)[i]) { if (!d && first) *first = DATA_LO + i * 4; d++; }
    for (size_t i = 0; i < n2; i++) if (x[n1 + i] != ((uint32_t *)ARENA)[i]) { if (!d && first) *first = 0x30000000 + i * 4; d++; }
    return d;
}
int g_want_st0;
long double g_ret_st0;
rec_fn rec_handler[256];
uint32_t rec_ret[256];
int rec_nargs[256];
uint32_t __cdecl rec_dispatch(uint32_t *f)
{
    uint32_t id = f[0], *args = f + 2, n = G(REC_LOG);
    if (n < REC_MAX) {
        uint32_t *e = (uint32_t *)(uintptr_t)(REC_LOG + 4 + n * REC_W * 4);
        e[0] = id;
        for (int i = 1; i < REC_W; i++) e[i] = i <= rec_nargs[id] ? args[i - 1] : 0;
        G(REC_LOG) = n + 1;
    }
    return rec_handler[id] ? rec_handler[id](args) : rec_ret[id];
}
void rec_append(uint32_t tag, const void *words, int n)
{
    const uint32_t *w = words;
    for (int k = 0; k < n; k += REC_W - 1) {
        uint32_t c = G(REC_LOG);
        if (c >= REC_MAX) return;
        uint32_t *e = (uint32_t *)(uintptr_t)(REC_LOG + 4 + c * REC_W * 4);
        e[0] = tag;
        for (int i = 1; i < REC_W; i++) e[i] = k + i - 1 < n ? w[k + i - 1] : 0;
        G(REC_LOG) = c + 1;
    }
}
int is_stack(uint32_t p) { return !((p >= 0x401000 && p < 0x94e000) || (p >= 0x30000000 && p < 0x30000000 + ARENA_SZ)); }
void rt_patch(uint32_t addr, int id, int argbytes)
{
    extern char rec_thunk_0[], rec_thunk_4[], rec_thunk_8[], rec_thunk_12[], rec_thunk_16[], rec_thunk_20[],
        rec_thunk_24[], rec_thunk_28[], rec_thunk_32[];
    static char *const th[9] = {rec_thunk_0, rec_thunk_4, rec_thunk_8, rec_thunk_12, rec_thunk_16, rec_thunk_20,
                                rec_thunk_24, rec_thunk_28, rec_thunk_32};
    extern char rec_thunkf_0[];
    uint8_t *p = (uint8_t *)(uintptr_t)addr;
    char *t = argbytes < 0 ? rec_thunkf_0 : th[argbytes / 4];
    p[0] = 0x68; *(uint32_t *)(p + 1) = (uint32_t)id;
    p[5] = 0xe9; *(int32_t *)(p + 6) = (int32_t)((uintptr_t)t - (uintptr_t)(p + 10));
}
