/* Differential test: the polygon span drivers FUN_00410330 / 00410970 / 00411740 / 004125c0 / 00413590 / 00414d20 /
 * 00416580 (the +0x1b4 callbacks of the rdRaster_Select_* functions).  Every callee (the span routines, Mem_DumpLog,
 * rdRaster_SpanR_FlatZw / _2) is redirected to the recorder, so the order of the calls and their span arguments are
 * compared with the memory. */
#include "harness.h"
#define CAM   0x30000100u
#define CAM4  0x30000200u
#define CANV  0x30000300u
#define REC   0x30001000u
#define SPANS 0x30002000u
#define FB    0x30010000u
#define TAB   0x30110000u
static const uint32_t callees[] = {
    0x451fa0, 0x452070, 0x45ff00,
    0x00452150, 0x004522b0, 0x004523f0, 0x00452530, 0x00452670, 0x004527b0, 0x004528f0, 0x00452a30, 0x00452b90,
    0x00452cd0, 0x00452e10, 0x00452f50, 0x00453090, 0x004531d0, 0x00453310, 0x004534d0, 0x00453660, 0x004537f0,
    0x00453980, 0x00453b10, 0x00453ca0, 0x00453e30, 0x00454780, 0x00455050, 0x00455920, 0x004561f0, 0x00456ac0,
    0x00457390, 0x00457c60, 0x004585b0, 0x00458e80, 0x00459750, 0x0045a020, 0x0045a8f0, 0x0045b1c0, 0x0045ba90,
    0x0045c4e0, 0x0045ce90, 0x0045d840, 0x0045e1f0, 0x0045eba0, 0x0045f550};
static void setup(int *args)
{
    static const int bpps[4] = {8, 16, 16, 24};
    static const int sizes[8] = {8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x30, 0};
    int bpp = bpps[rnd() & 3];
    G(0x7f0fc8) = CAM; G(CAM + 4) = CAM4; G(CAM4 + 4) = CANV;
    G(CAM4 + 0x14) = (rnd() & 1) ? 0 : (int)rnd();
    G(CANV + 0x18) = 0x400 + (rnd() & 0x7ff); G(CANV + 0x24) = bpp; G(CANV + 0x5c) = FB;
    fill_rand(REC, 0x200);
    G(REC + 0x1cc) = (rnd() & 7) == 7 ? (int)rnd() : sizes[rnd() & 7];
    G(REC + 0x1dc) = TAB + rndn(0x10000); G(REC + 0x1e0) = TAB + 0x20000 + rndn(0x10000);
    /* span list */
    int ns = rndn(5);
    G(REC + 0x1b8) = ns ? SPANS : 0;
    for (int i = 0; i < ns; i++) {
        uint32_t s = SPANS + i * 0x40;
        fill_rand(s, 0x40);
        G(s) = rndn(600); G(s + 4) = rndn(40); G(s + 8) = rndn(400);
        G(s + 0x28) = i + 1 < ns ? s + 0x40 : 0;
    }
    /* globals the drivers write */
    for (uint32_t a = 0x8ddf00; a < 0x8ddf50; a += 4) G(a) = rnd();
    G(0x7f3214) = callees[rndn(sizeof callees / sizeof callees[0])];
    args[0] = REC;
}
extern void FUN_00410330(void), FUN_00410970(void), FUN_00411740(void), FUN_004125c0(void), FUN_00413590(void),
    FUN_00414d20(void), FUN_00416580(void);
#ifdef SLICE
/* SLICE: the reassembled asm of the build (sliced, renamed orig_FUN_00410330) against the 1.01 bytes */
extern void orig_FUN_00410330(void), orig_FUN_00410970(void), orig_FUN_00411740(void), orig_FUN_004125c0(void),
    orig_FUN_00413590(void), orig_FUN_00414d20(void), orig_FUN_00416580(void);
#define FUN_00410330 orig_FUN_00410330
#define FUN_00410970 orig_FUN_00410970
#define FUN_00411740 orig_FUN_00411740
#define FUN_004125c0 orig_FUN_004125c0
#define FUN_00413590 orig_FUN_00413590
#define FUN_00414d20 orig_FUN_00414d20
#define FUN_00416580 orig_FUN_00416580
#endif
static const Fn fns[] = {
    {"FUN_00410330", 0x410330, (void *)FUN_00410330, setup, 0},
    {"FUN_00410970", 0x410970, (void *)FUN_00410970, setup, 0},
    {"FUN_00411740", 0x411740, (void *)FUN_00411740, setup, 0},
    {"FUN_004125c0", 0x4125c0, (void *)FUN_004125c0, setup, 0},
    {"FUN_00413590", 0x413590, (void *)FUN_00413590, setup, 0},
    {"FUN_00414d20", 0x414d20, (void *)FUN_00414d20, setup, 0},
    {"FUN_00416580", 0x416580, (void *)FUN_00416580, setup, 0},
};
int main(int argc, char **argv)
{
    rt_init();
    for (unsigned i = 0; i < sizeof callees / sizeof callees[0]; i++) { rt_patch(callees[i], 1 + i, 0); rec_nargs[1 + i] = 1; }
    fill_rand(0x30000000, ARENA_SZ);
    return run_all(fns, sizeof fns / sizeof fns[0], argc > 1 ? atol(argv[1]) : 1000, argc > 2 ? argv[2] : 0);
}
