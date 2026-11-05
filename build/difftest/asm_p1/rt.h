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
int gcall8(void *fn, const int *args8);
extern int g_want_st0;
extern long double g_ret_st0;
/* callee recorders (gcall.s, rt.c): rt_patch(addr, id, stdcall_argbytes) redirects a 1.01 function to rec_dispatch.
 * Every call is appended to the log in the arena (REC_LOG: count, then REC_W words per call: id and the first
 * REC_W - 1 argument words), so the log is part of the compared memory.  rec_handler[id], if set, is called with the
 * argument words and its result is the callee's EAX (default: rec_ret[id]). */
#define REC_LOG 0x303f0000u
#define REC_W 8
#define REC_MAX 1900   /* the log ends below the end of the arena */
typedef uint32_t (*rec_fn)(uint32_t *args);
extern rec_fn rec_handler[256];
extern uint32_t rec_ret[256];
extern int rec_nargs[256];   /* argument words logged per callee id (the rest of the entry is 0) */
void rt_patch(uint32_t addr, int id, int argbytes);
static inline void rec_reset(void) { G(REC_LOG) = 0; }
/* argbytes -1: a float-returning cdecl callee (the handler's result is the float's bits, loaded into ST0) */
/* append n raw words to the log (entries tagged tag), e.g. the contents a stack pointer argument points to */
void rec_append(uint32_t tag, const void *words, int n);
/* a pointer outside the image and the arena (the caller's stack: its address differs between the two sides) */
int is_stack(uint32_t p);
