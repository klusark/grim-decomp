#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned (*decomp_t)(void*, int*, unsigned*, unsigned*, unsigned*, int*, unsigned*);
int main(int argc, char **argv) {
    HMODULE a = LoadLibraryA("imuse_a.dll"), c = LoadLibraryA("imuse_c.dll");
    if (!a || !c) { printf("load fail\n"); return 1; }
    decomp_t fa = (decomp_t)GetProcAddress(a, "Im_VimaDecompress"), fc = (decomp_t)GetProcAddress(c, "Im_VimaDecompress");
    FILE *m = fopen(argv[1], "r"); char lab[300], nm[200]; long off, sz; int total = 0, bad = 0;
    while (fscanf(m, "%s %ld %ld %s", lab, &off, &sz, nm) == 4) {
        FILE *f = fopen(lab, "rb"); fseek(f, off, SEEK_SET);
        unsigned char *b = malloc(sz + 64), *b2 = malloc(sz + 64); memset(b, 0, sz + 64); fread(b, 1, sz, f); fclose(f); memcpy(b2, b, sz + 64);
        for (int mask = 0; mask < 64; mask += 21) {   /* 0, 21, 42, 63 */
            int pa2 = 0x11111111, pc2 = 0x11111111, pa6 = 0x22222222, pc6 = 0x22222222;
            unsigned pa3 = 0x33333333, pa4 = 0x44444444, pa5 = 0x55555555, pa7 = 0x77777777, pc3 = pa3, pc4 = pa4, pc5 = pa5, pc7 = pa7;
            unsigned ra = fa(b, (mask & 1) ? 0 : &pa2, (mask & 2) ? 0 : &pa3, (mask & 4) ? 0 : &pa4, (mask & 8) ? 0 : &pa5, (mask & 16) ? 0 : &pa6, (mask & 32) ? 0 : &pa7);
            unsigned rc = fc(b2, (mask & 1) ? 0 : &pc2, (mask & 2) ? 0 : &pc3, (mask & 4) ? 0 : &pc4, (mask & 8) ? 0 : &pc5, (mask & 16) ? 0 : &pc6, (mask & 32) ? 0 : &pc7);
            int offa = ra ? (int)(ra - (unsigned)b) : -1, offc = rc ? (int)(rc - (unsigned)b2) : -1;
            total++;
            if (!(offa == offc && pa2 == pc2 && pa3 == pc3 && pa4 == pc4 && pa5 == pc5 && pa6 == pc6 && pa7 == pc7)) {
                bad++; if (bad < 6) printf("%s mask %d: A off=%d %x %x %x %x %x %x | C off=%d %x %x %x %x %x %x\n", nm, mask, offa, pa2, pa3, pa4, pa5, pa6, pa7, offc, pc2, pc3, pc4, pc5, pc6, pc7);
            }
        }
        free(b); free(b2);
    }
    printf("%d calls, %d differ\n", total, bad);
    return 0;
}
