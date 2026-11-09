"""Task 2 of agent q6: an in-game self-check of the -O2 span fillers of build/overrides_asm_o2.c.  Writes, for a check
build only (never committed into build/):
  build/overrides_zz_q6check.c: the -O0 span fillers (the reference: the span section of <O0 file> with its names
      prefixed q6ref_) and wrappers rdRaster_Span16_TexLitZw* that run the reference and then the -O2 version on the
      same state (both colour / z rows of the span's row, the span state globals 0x007f4c40 .. 0x007f4d00) and count
      the calls whose results differ (q6check.txt in the game's working directory: calls, differences, first cases);
  build/overrides_asm_o2.c: <O2 file> with its span fillers renamed q6o2_*.
usage: ingame_check.py <O0 file> <O2 file>      (restore build/overrides_asm_o2.c afterwards)"""
import re
import sys

o0 = open(sys.argv[1]).read()
o2 = open(sys.argv[2]).read()
a = o0.index('#define RG32(a)')
b = o0.index('#endif /* GRIM_EXE */')
ref = o0[a:b]
for n in ('rdRaster_Span16_TexLitZw', 'span16_tex_zw', 'span16_texlit_zw', 'span_fist', 'span_mul16'):
    ref = re.sub(r'\b%s' % n, 'q6ref_' + n.replace('rdRaster_', ''), ref)
ref = ref.replace('#define RG32', '#undef RG32\n#define RG32').replace('#define RGU32', '#undef RGU32\n#define RGU32') \
         .replace('#define RG16', '#undef RG16\n#define RG16')
names = sorted(set(re.findall(r'\brdRaster_Span16_TexLitZw\w*', o2)))
chk = ['/* in-game self-check of the -O2 span fillers (agent q6, build/difftest/asm_q6/ingame_check.py; not committed) */',
       '#include "ghidra_types.h"', '#ifdef GRIM_EXE', ref,
       'extern void *q6c_fopen(const char *, const char *) __asm__("_fopen");',
       'extern int q6c_fprintf(void *, const char *, ...) __asm__("_fprintf");',
       'extern int q6c_fclose(void *) __asm__("_fclose");',
       'extern void *q6c_memcpy(void *, const void *, unsigned) __asm__("_memcpy");',
       'extern int q6c_memcmp(const void *, const void *, unsigned) __asm__("_memcmp");',
       'static unsigned q6c_calls, q6c_diffs, q6c_big;',
       'static unsigned char q6c_c0[8192], q6c_z0[8192], q6c_g0[0xc0], q6c_c1[8192], q6c_z1[8192], q6c_g1[0xc0];',
       r'''typedef void (*q6c_fn)(uint *, uint *);
static void q6c_check(uint *l, uint *r, q6c_fn ref, q6c_fn o2)
{
    int *canvas = *(int **)IMG_ADDR(0x007f0fc8);
    int *sc = *(int **)(canvas[1] + 4), *sz = *(int **)(canvas[1] + 0x10);
    unsigned char *crow = (unsigned char *)(sc[0x5c / 4] + ((unsigned)sc[0x18 / 4] >> 1) * l[0x10] * 2);
    unsigned char *zrow = (unsigned char *)(sz[0x5c / 4] + sz[0x18 / 4] * l[0x10]);
    unsigned clen = (unsigned)sc[0x18 / 4], zlen = (unsigned)sz[0x18 / 4];
    unsigned char *g = (unsigned char *)IMG_ADDR(0x007f4c40);
    unsigned short cw0, cw1, cw2;
    int x0 = (int)l[0], xr = (int)r[0], d = 0;
    if (x0 & 0xffff) x0 = (x0 + 0x10000) & 0xffff0000;
    if (xr & 0xffff) xr = (xr + 0x10000) & 0xffff0000;
    q6c_calls++;
    if ((int)((unsigned)xr >> 16) - (x0 >> 16) > (int)(clen / 2) || clen > sizeof q6c_c0 || zlen > sizeof q6c_z0 || x0 < 0) {
        q6c_big++;
        o2(l, r);
        return;
    }
    __asm__ volatile("fnstcw %0" : "=m"(cw0));
    q6c_memcpy(q6c_c0, crow, clen); q6c_memcpy(q6c_z0, zrow, zlen); q6c_memcpy(q6c_g0, g, 0xc0);
    ref(l, r);
    __asm__ volatile("fnstcw %0" : "=m"(cw1));
    q6c_memcpy(q6c_c1, crow, clen); q6c_memcpy(q6c_z1, zrow, zlen); q6c_memcpy(q6c_g1, g, 0xc0);
    q6c_memcpy(crow, q6c_c0, clen); q6c_memcpy(zrow, q6c_z0, zlen); q6c_memcpy(g, q6c_g0, 0xc0);
    __asm__ volatile("fldcw %0" : : "m"(cw0));
    o2(l, r);
    __asm__ volatile("fnstcw %0" : "=m"(cw2));
    if (q6c_memcmp(q6c_c1, crow, clen)) d |= 1;
    if (q6c_memcmp(q6c_z1, zrow, zlen)) d |= 2;
    if (q6c_memcmp(q6c_g1, g, 0xc0)) d |= 4;
    if (cw1 != cw2) d |= 8;
    if (d) q6c_diffs++;
    if (d || (q6c_calls & 0xffff) == 0) {
        void *f = q6c_fopen("q6check.txt", d ? "a" : "a");
        if (f) {
            q6c_fprintf(f, "calls %u diffs %u skipped %u%s", q6c_calls, q6c_diffs, q6c_big, d ? "" : "\n");
            if (d) q6c_fprintf(f, "  DIFF %d at l.x %08x r.x %08x y %d\n", d, l[0], r[0], l[0x10]);
            q6c_fclose(f);
        }
    }
}''']
for n in names:
    s = n.replace('rdRaster_', '')
    chk.append('void q6o2_%s(uint *, uint *);' % s)
    chk.append('void %s(uint *l, uint *r) { q6c_check(l, r, q6ref_%s, q6o2_%s); }' % (n, s, s))
chk.append('#endif')
open('build/overrides_zz_q6check.c', 'w', newline='\n').write('\n'.join(chk) + '\n')
o2r = re.sub(r'\brdRaster_Span16_TexLitZw', 'q6o2_Span16_TexLitZw', o2)
open('build/overrides_asm_o2.c', 'w', newline='\n').write(o2r)
print('%d wrappers' % len(names))
