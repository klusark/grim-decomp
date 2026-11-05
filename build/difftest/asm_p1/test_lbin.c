/* Differential test: rdModel3_LoadBinary (0x0040b8e0).  The file services of g_pSvcRdroid are recorders: pFread
 * copies the next bytes of a random "file" (mostly small words, so that the counts in it stay small), pAlloc is a
 * bump allocator in the arena (0 for large sizes), pFree logs.  rdModel3_NewEntry clears the record, rdMaterial_Load
 * logs the name and returns a value derived from it.  Buffers on the caller's stack are logged by content. */
#include "harness.h"
#define SVC    0x30000000u
#define MODEL  0x30000100u
#define POS    0x30000300u   /* stream position */
#define HEAP_P 0x30000304u   /* heap pointer */
#define STREAM 0x30100000u
#define STREAM_SZ 0x20000u
#define HEAP   0x30200000u
#define HEAP_END 0x303e0000u
static uint32_t hsh(const uint32_t *w, int n) { uint32_t h = 2166136261u; for (int i = 0; i < n; i++) h = (h ^ w[i]) * 16777619u; return h; }
static uint32_t h_fread(uint32_t *a)
{
    uint32_t w[3] = {a[0], is_stack(a[1]) ? 0x5ac0000u : a[1], a[2]};
    rec_append(0x101, w, 3);
    uint32_t n = a[2], pos = G(POS);
    if (a[1] == 0 || n > 0x10000 || pos + n > STREAM_SZ) return 0;
    memcpy((void *)(uintptr_t)a[1], (void *)(uintptr_t)(STREAM + pos), n);
    G(POS) = pos + n;
    return n;
}
static uint32_t h_alloc(uint32_t *a)
{
    rec_append(0x201, a, 3);
    uint32_t n = a[0], p = G(HEAP_P);
    if (n > 0x8000 || p + n > HEAP_END) return 0;
    G(HEAP_P) = (p + n + 7) & ~7u;
    return p;
}
static uint32_t h_free(uint32_t *a) { rec_append(0x301, a, 1); return 0; }
static uint32_t h_newentry(uint32_t *a) { rec_append(0x401, a, 1); memset((void *)(uintptr_t)a[0], 0, 0x90); return 0; }
static uint32_t h_matload(uint32_t *a)
{
    uint32_t w[10]; memcpy(w, (void *)(uintptr_t)a[0], 32); w[8] = a[1]; w[9] = a[2];
    rec_append(0x501, a, 1); rec_append(0x502, w, 10);
    return hsh(w, 8) | 1;
}
static void setup(int *args)
{
    G(0x900004) = SVC;
    fill_rand(SVC, 0x70);
    G(SVC + 0x38) = 0x40aa20; G(SVC + 0x20) = 0x40d230; G(SVC + 0x24) = 0x405770;
    G(POS) = 0; G(HEAP_P) = HEAP;
    *(volatile int16_t *)0x4ddb84 = (int16_t)rnd();
    int big = rnd() & 3;
    for (uint32_t i = 0; i < STREAM_SZ; i += 4) {
        uint32_t r = rnd(), v;
        switch (r & 15) {
        case 0: case 1: case 2: case 3: case 4: case 5: v = 0; break;
        case 6: case 7: case 8: case 9: v = 1 + (r >> 8) % 3; break;
        case 10: v = (r >> 8) % 8; break;
        case 11: v = big == 0 ? rnd() : (r >> 8) % 3; break;
        case 12: v = (uint32_t)-1; break;
        default: v = rnd(); break;
        }
        G(STREAM + i) = v;
    }
    fill_rand(MODEL, 0x100);
    args[0] = (int)rnd(); args[1] = MODEL;
}
extern void rdModel3_LoadBinary(void);
static const Fn fns[] = {{"rdModel3_LoadBinary", 0x40b8e0, (void *)rdModel3_LoadBinary, setup, 1}};
int main(int argc, char **argv)
{
    rt_init();
    rt_patch(0x40aa20, 1, 0); rec_handler[1] = h_fread;
    rt_patch(0x40d230, 2, 0); rec_handler[2] = h_alloc;
    rt_patch(0x405770, 3, 0); rec_handler[3] = h_free;
    rt_patch(0x40a8c0, 4, 0); rec_handler[4] = h_newentry;
    rt_patch(0x417eb0, 5, 0); rec_handler[5] = h_matload;
    fill_rand(0x30000000, ARENA_SZ);
    return run_all(fns, 1, argc > 1 ? atol(argv[1]) : 1000, 0);
}
