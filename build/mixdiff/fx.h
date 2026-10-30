/* Trace harness for differential tests of stateful functions (build/mixdiff).
 *
 * A test runs one function twice on the same initial state: the original machine code (orig_<name>) and the C
 * replacement.  Everything the function can observe or change is compared afterwards:
 *   - the return value,
 *   - the memory regions registered with fx_region() (global data, buffers the arguments point to),
 *   - the log of calls to recorder thunks (fx_thunk): COM methods, module-manager services, callbacks, imports.
 * A thunk records its tag and the first 10 dwords of its arguments (string arguments by content, see fx_strmask) and
 * returns a scripted value (fx_ret / fx_queue); it can also run an "effect" (fx_effect) that changes state, to model
 * what the real callee would do (a callback that stops its own timer, a clock that advances ...). */
#ifndef FX_H
#define FX_H
#include <stdint.h>

#define FX_MAXLOG 4096

typedef struct FxEv {
    int tag;
    unsigned a[10];
    char str[3][64];
    unsigned deref[4][5];
    int ret;
} FxEv;

typedef int (*FxEffect)(int tag, unsigned *args);

extern FxEv fx_log[FX_MAXLOG];
extern int fx_nlog;

/* the data image of the game (data_s.o): address of the byte at the original virtual address */
extern unsigned char fx_data[] __asm__("_sect_data");
#define FXDATA(va) (fx_data + ((va) - 0x4dd000))
#define FXU32(va)  (*(unsigned *)FXDATA(va))
#define FXI32(va)  (*(int *)FXDATA(va))

void *fx_thunk(int tag, int nargs, int stdcall_);     /* callable recorder, returns EAX = scripted value */
void fx_ret(int tag, int value);                       /* constant return value of a tag (default 0) */
void fx_queue(int tag, int value);                     /* values consumed one per call before the constant applies */
void fx_effect(int tag, FxEffect fn);                  /* run fn(tag, args) at each call; its result is the return value (if not -12345678) */
void fx_strmask(int tag, int mask);                    /* bit i: argument i is a C string, log its content instead of the pointer */
void fx_ignmask(int tag, int mask);                    /* bit i: argument i is not logged (stack addresses, code addresses of the other implementation) */
void fx_derefmask(int tag, int mask);                  /* bit i (i < 4): argument i is a pointer; log the 5 dwords it points to instead */
void fx_reset(void);                                   /* clears the log and the queues, not the constants */
void fx_clear_all(void);
void fx_clear_queues(void);                            /* forgets the queued return values only */

/* memory regions compared after a run */
void fx_region(void *p, unsigned len);
void fx_region_reset(void);
void fx_save(void);                  /* take the current state as the start state */
void fx_restore(void);               /* put the start state back */
void fx_snap_a(void);                /* remember the state after the first run */
int fx_cmp_a(void);                  /* 0 = equal to the state after the first run */
int fx_cmp_log(void);                /* 0 = the call log equals the one after the first run */

/* a COM object whose methods are recorder thunks: methods[i] = number of dwords of arguments (this included) */
void *fx_com(int objtag, int nmethods, const int *nargs);

/* deterministic random numbers */
uint64_t fx_rnd(void);
extern uint64_t fx_seed;

/* plain test bookkeeping */
extern long fx_fails, fx_cases;
void fx_fail(const char *what, long i);
#endif
