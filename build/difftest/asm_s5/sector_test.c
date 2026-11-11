/* Differential test of WalkPlane_Within (build/overrides_asm_o2.c) against the original machine code, on random
 * sectors (2..8 vertices on a plane, random axes, tolerances) and points on, near and off the plane and the edges, with
 * special values (0, -0, 1e-5 neighbours, inf, NaN) mixed in, under the x87 precision controls 24, 53 and 64 bits.
 * Build: build/difftest/asm_s5/build.sh build/difftest/asm_s5/sector_test.c build/difftest/asm_s5/out/sector_test.exe WalkPlane_Within */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include "fx.h"
static long ninside;

extern int __thiscall orig_WalkPlane_Within(void *, float *, int), WalkPlane_Within(void *, float *, int);
static unsigned R(unsigned n) { return (unsigned)(fx_rnd() % n); }
static float rf(float s) { return (float)((double)(int)(fx_rnd() % 2000001 - 1000000) / 1000000.0 * s); }
static float special(float x)
{
    switch (R(40)) {
    case 0: return 0.0f; case 1: return -0.0f; case 2: return 1e-5f; case 3: return -1e-5f;
    case 4: return 1.0001e-5f; case 5: return 0.9999e-5f; case 6: { unsigned u = 0x7f800000; float f; memcpy(&f, &u, 4); return f; }
    case 7: { unsigned u = 0x7fc00000; float f; memcpy(&f, &u, 4); return f; }
    case 8: return -x;
    }
    return x;
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 100000, i;
    static unsigned char sec[0x100];
    static float vrec[8][4];
    float p[3];
    unsigned pcs[3] = {_PC_24, _PC_53, _PC_64};
    for (i = 0; i < n; i++) {
        int cnt = R(10), ra, rb, chk = R(2);
        float nx = rf(1), ny = rf(1), nz = rf(1);
        unsigned pc = pcs[i % 3];
        memset(sec, 0, sizeof sec);
        for (int k = 0; k < 8; k++) {
            vrec[k][0] = rf(100);
            vrec[k][1] = R(3) ? rf(10) : special(rf(1e-4f));
            vrec[k][2] = R(4) ? rf(10) : vrec[k ? k - 1 : 0][2];
            vrec[k][3] = special(rf(10));
            ((int *)(sec + 0x38))[k] = (int)(uintptr_t)&vrec[k][0] - 0;
        }
        /* vertex pointers point at the record; the coordinates are at +4 */
        for (int k = 0; k < 8; k++) ((int *)(sec + 0x38))[k] = (int)(uintptr_t)&vrec[k][0];
        *(int *)(sec + 0x34) = cnt == 9 ? -1 : cnt;
        *(int *)(sec + 0x3c) = (int)(uintptr_t)&vrec[R(8)][0];
        *(int *)(sec + 0x2c) = R(4) != 0; *(int *)(sec + 0x28) = R(4) != 0;
        *(float *)(sec + 0x30) = R(5) ? rf(1) : special(rf(1e-5f));
        *(float *)(sec + 0x60) = special(nx); *(float *)(sec + 0x64) = special(ny); *(float *)(sec + 0x68) = special(nz);
        *(int *)(sec + 0x7c) = R(3); *(int *)(sec + 0x80) = R(3);
        if (R(2)) {   /* a proper polygon: vertices on a circle in the plane y = h, normal (0, 1, 0) */
            float h = rf(5), r = 1 + rf(3), dir = R(2) ? 1 : -1;
            int m = cnt < 3 ? 3 + R(5) : (cnt > 8 ? 8 : cnt);
            *(int *)(sec + 0x34) = m;
            for (int k = 0; k < m; k++) {
                double ang = dir * 6.283185307 * k / m;
                vrec[k][1] = (float)(r * cos(ang)) + (R(6) ? 0 : special(rf(1e-5f)));
                vrec[k][2] = h + (R(6) ? 0 : special(rf(1e-5f)));
                vrec[k][3] = (float)(r * sin(ang));
            }
            *(float *)(sec + 0x60) = R(8) ? 0 : special(rf(1e-3f)); *(float *)(sec + 0x64) = 1; *(float *)(sec + 0x68) = R(8) ? 0 : special(rf(1e-3f));
            *(int *)(sec + 0x7c) = 0; *(int *)(sec + 0x80) = 2;
            *(int *)(sec + 0x3c) = (int)(uintptr_t)&vrec[0][0];
            p[0] = rf(r * 1.2f); p[1] = h + (R(2) ? special(rf(1e-5f)) : rf(1)); p[2] = rf(r * 1.2f);
            if (R(4) == 0) { int k = R(m); p[0] = vrec[k][1] + special(rf(1e-5f)); p[2] = vrec[k][3] + special(rf(1e-5f)); }
        } else if (R(2)) { float *v = &vrec[R(8)][1]; p[0] = v[0] + special(rf(1e-4f)); p[1] = v[1] + special(rf(1e-4f)); p[2] = v[2] + special(rf(1e-4f)); }
        else { p[0] = special(rf(10)); p[1] = special(rf(10)); p[2] = special(rf(10)); }
        _controlfp(pc, _MCW_PC);
        ra = orig_WalkPlane_Within(sec, p, chk);
        rb = WalkPlane_Within(sec, p, chk);
        _controlfp(_PC_64, _MCW_PC);
        if (ra != rb) fx_fail("ret", i);
        fx_cases++;
        if (ra) ninside++;
    }
    printf("sector_test: %ld inside\n", ninside); printf("sector_test: %ld cases, %ld differences\n", fx_cases, fx_fails);
    return fx_fails != 0;
}
