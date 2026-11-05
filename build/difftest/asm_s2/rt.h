/* Runtime of the rasteriser differential tests: the original GRIMFANDANGO.EXE image (text, rdata, data from
 * raw/GRIMFANDANGO.EXE/sections) is mapped at its own addresses (0x400000 - 0x94e000), so the original machine code
 * runs unmodified and the C under test (linked with absolute symbols for every global it names, gensyms.py) works on
 * the same memory.  Faults are caught (vectored handler) and reported as a crash of that side. */
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
extern uint32_t g_ret;
int gcall(void *fn, int a, int b, int c, int d);
void rt_init(void);
uint32_t rnd(void);
static inline uint32_t rndn(uint32_t n) { return n ? rnd() % n : 0; }
/* random 32 bit value with a bias to edge cases */
uint32_t rnd_edge(void);
#define DATA_LO 0x4dd000u
#define DATA_HI 0x929aa0u
#define G(addr) (*(volatile int32_t *)(uintptr_t)(addr))
#define GB(addr) (*(volatile uint8_t *)(uintptr_t)(addr))
#define GF(addr) (*(volatile float *)(uintptr_t)(addr))
/* arena: scratch memory for frame buffers, textures, tables, edge records (fixed address) */
#define ARENA ((uint8_t *)0x30000000)
#define ARENA_SZ (4u << 20)
/* state save / compare of .data + arena */
void st_save(void *buf);
void st_load(const void *buf);
long st_cmp(const void *a, const void *b, uint32_t *first);
size_t st_size(void);
unsigned short fpu_cw(void);
void fpu_set(unsigned short cw);
long st_cmp_live(const void *saved, uint32_t *first);
