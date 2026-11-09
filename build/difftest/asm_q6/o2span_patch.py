"""Task 2 of agent q6: put the span fillers of build/overrides_asm_o2.c (rdRaster_Span16_TexLitZw*) under -O2 with the
x87 rounding points kept (volatile float stores at the original's FSTP m32, the float read after the first conversion
volatile, span_fist clobbering memory).  usage: python -I o2span_patch.py <in.c> <out.c>"""
import sys

s = open(sys.argv[1]).read()


def rep(old, new):
    global s
    assert s.count(old) == 1, old
    s = s.replace(old, new)


rep(r'''#define RG32(a) (*(int *)IMG_ADDR(a))
#define RGU32(a) (*(uint *)IMG_ADDR(a))
#define RG16(a) (*(ushort *)IMG_ADDR(a))''', r'''/* the globals of the original's .data by address (constants: no img_addr_ call, which -O2 code cannot inline) */
#define SPAN_DATA(a) ((void *)(sect_data + ((a) - 0x004dd000u)))
#define RG32(a) (*(int *)SPAN_DATA(a))
#define RGU32(a) (*(uint *)SPAN_DATA(a))
#define RG16(a) (*(ushort *)SPAN_DATA(a))''')
a = s.index('#define SPAN_DATA(a)')
s = s[:a] + s[a:].replace('IMG_ADDR(0x', 'SPAN_DATA(0x')
rep(r'''static int span_fist(float x)
{
    int r;

    __asm__ volatile("fldcw %2\n\tfistpl %0\n\tfldcw %3"
                     : "=m"(r)
                     : "t"(x), "m"(RG16(0x00900526)), "m"(RG16(0x00900524))
                     : "st");
    return r;
}

static int span_mul16(int a, int b)    /* imul + shrd 16: bits 16..47 of the 64 bit product */''',
    r'''/* These spans are what the game's opaque textured drivers call per scan line (Draw_FlatLit_7 .. 9 of
 * build/overrides_asm_q4.c with the z shift 0), so they are compiled at -O2 (build/link.py compiles override files at
 * -O0; agent q6 measured the gain, docs/notes/asm_q6.md).  At -O2 gcc keeps x87 values in registers, so every FSTP m32
 * of the original is a store through a volatile float (span_f), the float the z start reads after the first conversion
 * is a volatile (its arithmetic cannot move before that conversion's control-word loads), and span_fist clobbers
 * memory.  The differential test build/difftest/asm_q6/o2span.sh compiles this file as build/link.py does. */
#pragma GCC push_options
#pragma GCC optimize("O2", "no-strict-aliasing", "no-omit-frame-pointer")

static inline __attribute__((always_inline)) float span_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

static inline __attribute__((always_inline)) int span_fist(float x)
{
    int r;

    __asm__ volatile("fldcw %2\n\tfistpl %0\n\tfldcw %3"
                     : "=m"(r)
                     : "t"(x), "m"(RG16(0x00900526)), "m"(RG16(0x00900524))
                     : "st", "memory");
    return r;
}

static inline __attribute__((always_inline)) int span_mul16(int a, int b)    /* imul + shrd 16: bits 16..47 of the 64 bit product */''')
rep(r'''    int u, v, z, du, dv, dz;
    float dzf, f;''', r'''    int u, v, z, du, dv, dz;
    volatile float dzf;
    float f;''')
rep(r'''        dzf = (float)d;
        f = (float)(d * 65536.0f);
    }
    RG32(0x007f4c54) = span_fist(f);
    f = (float)(((long double)frac * 1.52587890625e-05f * dzf + *(float *)&left[0x10 / 4]) * 65536.0f);''',
    r'''        dzf = (float)d;
        f = span_f(d * 65536.0f);
    }
    RG32(0x007f4c54) = span_fist(f);
    f = span_f(((long double)frac * 1.52587890625e-05f * dzf + *(float *)&left[0x10 / 4]) * 65536.0f);''')
rep(r'''    int u, v, z, l, du, dv, dz, dl;
    float fracf, dzf, f;''', r'''    int u, v, z, l, du, dv, dz, dl;
    volatile float dzf;
    float fracf, f;''')
rep(r'''    fracf = (float)((long double)frac * 1.52587890625e-05f);''',
    r'''    fracf = span_f((long double)frac * 1.52587890625e-05f);''')
rep(r'''        dzf = (float)d;
        f = (float)(d * 65536.0f);
    }
    RG32(0x007f4c54) = span_fist(f);
    f = (float)(((long double)dzf * fracf + *(float *)&left[0x10 / 4]) * 65536.0f);''',
    r'''        dzf = (float)d;
        f = span_f(d * 65536.0f);
    }
    RG32(0x007f4c54) = span_fist(f);
    f = span_f(((long double)dzf * fracf + *(float *)&left[0x10 / 4]) * 65536.0f);''')
rep(r'''void rdRaster_Span16_TexLitZw_8(uint *left, uint *right) { span16_texlit_zw((int *)left, (int *)right, 0x8, 0xff0000, 0x3f0000); }
''', r'''void rdRaster_Span16_TexLitZw_8(uint *left, uint *right) { span16_texlit_zw((int *)left, (int *)right, 0x8, 0xff0000, 0x3f0000); }

#pragma GCC pop_options
''')
open(sys.argv[2], 'w', newline='\n').write(s)
