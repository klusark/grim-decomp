/* Differential test (agent r1): the music state / sequence transitions of IMUSE.DLL, original machine code against the C
 * of build/overrides_imuse_r1.c.
 *   orig_FUN_10006560 / orig_FUN_10006620 / orig_FUN_100068b0: sliced from the base assembly (85dd22f), called through
 *   thunks.s with the frames of the original callers (ESI = 0xffffffff of the dispatcher, random EDI / saved words);
 *   orig_FUN_100064d0: transcribed from the original DLL (thunks.s).
 * Stand-ins for the iMUSE API they call (ImGetNextSound, ImGetParam, ImOpenSound, ImSetTrigger, ...) log every call and
 * answer from a random per-case model.  ImSetTrigger logs what the real one uses: sound, marker text, command, the words the
 * call pushes, and p9 (the 13th stack word, stored in all ten parameter words of the trigger); an orig_ret_* return address
 * of the slice is mapped to the original address it stands for (0x100065f3, ...).  Each case randomises the state and
 * sequence tables, the name alias table and the globals of the data image, runs one entry point both ways from the same
 * start state and compares: return value, call log, the data regions written (globals 0x1002df00..0x1002e400).
 * usage: r1_test.exe [cases] [seed] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

extern unsigned char sect_data[] __asm__("_sect_data");   /* .data of IMUSE.DLL, 0x10017000 */
#define D(va)   (sect_data + ((va) - 0x10017000u))
#define DW(va)  (*(int *)D(va))

/* the code under test */
int orig_FUN_10006560(int) __asm__("_orig_FUN_10006560");
int call_orig_6560(int id, unsigned esi, unsigned edi);
int call_orig_6620(int id, unsigned esi, unsigned edi);
int call_orig_64d0(unsigned esi, unsigned edi);
void call_orig_68b0(char *entry, int index, int no_attr, unsigned w10, unsigned w14);
extern char orig68b0_ret[];
extern char orig_ret_100065f3[], orig_ret_100066eb[], orig_ret_1000672c[], orig_ret_10006778[];
int FUN_10006560(int id);
int FUN_10006620(int id);
int FUN_100064d0(void);
void FUN_100068b0(char *entry, int index, int no_attr, unsigned caller_esi, unsigned ret_word);

/* ---- random numbers ---- */
static uint64_t seed = 0x9e3779b97f4a7c15ull;
static uint32_t rnd(void) { seed ^= seed << 13; seed ^= seed >> 7; seed ^= seed << 17; return (uint32_t)(seed >> 11); }
static uint32_t hash3(uint32_t a, uint32_t b, uint32_t c)
{
    uint32_t h = a * 0x9e3779b1u ^ b * 0x85ebca6bu ^ c * 0xc2b2ae35u;
    h ^= h >> 15; h *= 0x2c1b3c6du; h ^= h >> 12; h *= 0x297a2d39u; h ^= h >> 15;
    return h;
}

/* ---- call log ---- */
typedef struct { int tag; unsigned a[8]; char s[72]; } Ev;
#define MAXEV 512
static Ev logbuf[2][MAXEV];
static int nlog[2], side;
static Ev *ev(int tag)
{
    Ev *e = &logbuf[side][nlog[side] < MAXEV ? nlog[side]++ : MAXEV - 1];
    memset(e, 0, sizeof *e);
    e->tag = tag;
    return e;
}
static void str(Ev *e, const char *s) { if (s) strncpy(e->s, s, sizeof e->s - 1); else strcpy(e->s, "(null)"); }

/* ---- per-case model of the sound engine ---- */
static uint32_t cseed;                 /* case seed: answers depend on it and on the arguments only */
static unsigned snds[6]; static int nsnd;
static unsigned open_ret, start_ret;

int ImPrintf(const char *fmt, ...)
{
    Ev *e = ev(1);
    str(e, fmt);
    if (fmt && strchr(fmt, '%'))
        e->a[0] = ((unsigned *)&fmt)[1];
    return 0;
}
unsigned ImGetNextSound(unsigned s)
{
    int i;
    Ev *e = ev(2);
    unsigned r = 0;
    e->a[0] = s;
    if (s == 0)
        r = nsnd ? snds[0] : 0;
    else
        for (i = 0; i < nsnd; i++)
            if (snds[i] == s) { r = i + 1 < nsnd ? snds[i + 1] : 0; break; }
    e->a[1] = r;
    return r;
}
unsigned ImGetParam(int s, int p)
{
    Ev *e = ev(3);
    uint32_t h = hash3(cseed, s, p);
    unsigned r;
    switch (h & 7) {
    case 0: case 1: r = 0; break;
    case 2: case 3: r = 2; break;
    case 4: case 5: r = 4; break;
    case 6: r = 1; break;
    default: r = h >> 8; break;
    }
    e->a[0] = s; e->a[1] = p; e->a[2] = r;
    return r;
}
int ImFadeParam(int s, int p, unsigned v, int t) { Ev *e = ev(4); e->a[0] = s; e->a[1] = p; e->a[2] = v; e->a[3] = t; return (int)hash3(cseed, 4, s); }
int ImSetHook(int s, unsigned h) { Ev *e = ev(5); e->a[0] = s; e->a[1] = h; return (int)hash3(cseed, 5, s); }
int ImOpenSound(char *name, int x) { Ev *e = ev(6); str(e, name); e->a[0] = x; return (int)open_ret; }
int ImSwitchStream(int a, int b, unsigned c, unsigned d, unsigned f)
{
    Ev *e = ev(7); e->a[0] = a; e->a[1] = b; e->a[2] = c; e->a[3] = d; e->a[4] = f; return (int)hash3(cseed, 7, a);
}
int ImSetParam(int s, int p, unsigned v) { Ev *e = ev(8); e->a[0] = s; e->a[1] = p; e->a[2] = v; return (int)hash3(cseed, 8, s); }
int ImStartStream(unsigned s, int p, unsigned g) { Ev *e = ev(9); e->a[0] = s; e->a[1] = p; e->a[2] = g; return (int)start_ret; }
int ImCloseSound(int s) { Ev *e = ev(10); e->a[0] = s; return (int)hash3(cseed, 10, s); }
int ImProcessStreams(void) { ev(11); return (int)hash3(cseed, 11, 0); }
int ImFlushSounds(void) { ev(12); return (int)hash3(cseed, 12, 0); }

static long cov_trig, cov_ret, cov_cmd0, cov_esi0;   /* coverage of the stack-word cases (original side) */
static int touched_state[8], ntouched_state, touched_seq[8], ntouched_seq;
/* ImSetTrigger(sound, marker, cmd, p0..p9): the real one keeps sound, marker, cmd and p9 (in all ten words) */
static unsigned map_ret(unsigned w)
{
    if (w == (unsigned)(uintptr_t)orig_ret_100065f3) return 0x100065f3u;
    if (w == (unsigned)(uintptr_t)orig_ret_100066eb) return 0x100066ebu;
    if (w == (unsigned)(uintptr_t)orig_ret_1000672c) return 0x1000672cu;
    if (w == (unsigned)(uintptr_t)orig_ret_10006778) return 0x10006778u;
    return w;
}
int ImSetTrigger(int sound, char *marker, int cmd, int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9)
{
    Ev *e = ev(13);
    int n = cmd == 0 ? 0 : cmd == 0x1a ? 5 : cmd == 0xe ? 4 : cmd == 0xc ? 3 : cmd == 0xf ? 2 : 10;   /* words pushed */
    int p[10] = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9}, i;
    e->a[0] = sound; e->a[1] = cmd;
    for (i = 0; i < n && i < 5; i++)
        e->a[2 + i] = p[i];
    e->a[7] = map_ret((unsigned)p9);
    if (side == 0) {
        cov_trig++;
        if (e->a[7] != (unsigned)p9) cov_ret++;
        if (cmd == 0) { cov_cmd0++; if (p9 == 0) cov_esi0++; }
    }
    str(e, marker);
    return (int)hash3(cseed, 13, sound);
}

/* ---- data image ---- */
#define GLOB_LO 0x1002df00u
#define GLOB_HI 0x1002e400u
static unsigned char glob_start[GLOB_HI - GLOB_LO], glob_a[GLOB_HI - GLOB_LO];
static int flag_start, flag_a;
#define STATE_TAB 0x100172e8u
#define SEQ_TAB   0x1001ae50u
#define ALIAS     0x1001bbc8u
static unsigned char state_orig[181 * 0x54], seq_orig[41 * 0x54], alias_orig[0x40 * 12];

static const char *names[] = {"a", "ab", "abc", "mus1.imu", "mus2.imu", "x", "", "longername_with_more.imu"};
static void rnd_name(char *dst, int max)
{
    int k = rnd() % 10;
    if (k < 8) { strncpy(dst, names[k], max - 1); dst[max - 1] = 0; }
    else if (k == 8) { int i, n = rnd() % max; for (i = 0; i < n; i++) dst[i] = 'a' + rnd() % 3; if (n < max) dst[n] = 0; }
    else { int i; for (i = 0; i < max; i++) dst[i] = 'a' + rnd() % 3; }   /* no terminator inside the field */
}
static int rnd_type(void)
{
    uint32_t r = rnd() % 20;
    if (r < 14) return (int)r;                /* 0..13 */
    if (r < 16) return 2 + (rnd() & 1);
    if (r < 18) return 10 + rnd() % 3;
    return r == 18 ? -1 : (int)(rnd() | 0x80000000u);
}
static int rnd_small(void)
{
    switch (rnd() % 8) {
    case 0: case 1: return 0;
    case 2: return 1;
    case 3: return 2;
    case 4: return 100;
    case 5: return rnd() % 8;
    case 6: return (int)rnd();
    default: return -(int)(rnd() % 4);
    }
}
static void rnd_entry(unsigned char *e, int nslots)
{
    memset(e, 0, 0x54);
    rnd_name((char *)e, 0x20);
    *(int *)(e + 0x20) = rnd_type();
    *(int *)(e + 0x40) = rnd() % 3 ? 0 : (int)(rnd() % nslots);
    *(int *)(e + 0x44) = rnd() % 2 ? 0 : (rnd() % 3 ? (int)(rnd() % 5) : rnd_small());
    *(int *)(e + 0x48) = rnd() % 2 ? 0 : (rnd() % 4 ? (int)(rnd() % 5000) : (int)rnd());
    *(int *)(e + 0x4c) = rnd() % 128;
    *(int *)(e + 0x50) = rnd() % 4 ? (int)(rnd() % 128) : 0;
}

static void randomise(void)
{
    int i, k;
    /* tables: start from the shipped ones, re-randomise some entries (ids from the shipped set so that lookups hit) */
    memcpy(D(STATE_TAB), state_orig, sizeof state_orig);
    memcpy(D(SEQ_TAB), seq_orig, sizeof seq_orig);
    memcpy(D(ALIAS), alias_orig, sizeof alias_orig);
    ntouched_state = ntouched_seq = 0;
    for (k = rnd() % 6; k > 0; k--) {
        i = rnd() % 181;
        touched_state[ntouched_state++] = i;
        int id = *(int *)D(STATE_TAB + i * 0x54 + 0x24);
        rnd_entry(D(STATE_TAB + i * 0x54), 64);
        *(int *)D(STATE_TAB + i * 0x54 + 0x24) = id;
        if (rnd() % 4 == 0) *(int *)D(STATE_TAB + i * 0x54 + 0x24) = rnd() % 4 ? 1000 + rnd() % 200 : (int)rnd();
    }
    for (k = rnd() % 4; k > 0; k--) {
        i = rnd() % 41;
        touched_seq[ntouched_seq++] = i;
        int id = *(int *)D(SEQ_TAB + i * 0x54 + 0x24);
        rnd_entry(D(SEQ_TAB + i * 0x54), 64);
        *(int *)D(SEQ_TAB + i * 0x54 + 0x24) = id;
        if (rnd() % 4 == 0) *(int *)D(SEQ_TAB + i * 0x54 + 0x24) = rnd() % 4 ? 2000 + rnd() % 300 : (int)rnd();
    }
    if (rnd() % 3 == 0) {                      /* alias records */
        int n = rnd() % 6;
        for (i = 0; i < n; i++) {
            rnd_name((char *)D(ALIAS + i * 0x40), 0x20);
            if (rnd() % 3 == 0) memcpy(D(ALIAS + i * 0x40), D(STATE_TAB + (rnd() % 181) * 0x54), 0x20);
            rnd_name((char *)D(ALIAS + i * 0x40 + 0x20), 0x20);
        }
        *D(ALIAS + n * 0x40) = 0;
    }
    /* globals */
    for (i = 0; i < (int)(GLOB_HI - GLOB_LO); i += 4)
        *(unsigned *)D(GLOB_LO + i) = rnd() % 3 ? rnd() % 6 : rnd();
    DW(0x1001e688) = rnd() % 16 ? 1 : 0;
    DW(0x1002df70) = rnd() % 4 ? (int)(rnd() % 181) : 0;
    DW(0x1002e308) = rnd() % 3 ? 0 : (int)(rnd() % 41);
    DW(0x1002e30c) = rnd() % 3 ? 0 : (int)(rnd() % 41);
    DW(0x1002e304) = rnd() % 2;
    for (i = 0; i < 64; i++) DW(0x1002df84 + 4 * i) = rnd() % 4 ? (int)(rnd() % 6) : rnd_small();
    /* sound engine model */
    cseed = rnd();
    nsnd = rnd() % 5;
    for (i = 0; i < nsnd; i++) {               /* distinct ids (a repeated one would make the sound list circular) */
        int j;
        do {
            snds[i] = rnd() % 4 ? 0x2711 + rnd() % 6 : rnd() | 1;
            for (j = 0; j < i && snds[j] != snds[i]; j++)
                ;
        } while (j < i);
    }
    switch (rnd() % 4) {
    case 0: open_ret = 0; break;
    case 1: open_ret = nsnd ? snds[rnd() % nsnd] : 0x2711; break;
    default: open_ret = 0x2711 + rnd() % 4; break;
    }
    start_ret = rnd() % 3 == 0;
}

static void save(void) { memcpy(glob_start, D(GLOB_LO), sizeof glob_start); flag_start = DW(0x1001e688); }
static void restore(void) { memcpy(D(GLOB_LO), glob_start, sizeof glob_start); DW(0x1001e688) = flag_start; }

static long fails;
static void fail(const char *what, long i, int r0, int r1)
{
    int k;
    if (fails++ >= 10) return;
    printf("DIFF %s case %ld: ret %x / %x, logs %d / %d\n", what, i, r0, r1, nlog[0], nlog[1]);
    for (k = 0; k < nlog[0] || k < nlog[1]; k++) {
        Ev *a = &logbuf[0][k], *b = &logbuf[1][k];
        if (k < nlog[0] && k < nlog[1] && !memcmp(a, b, sizeof *a)) continue;
        if (k < nlog[0]) printf("  orig[%d] tag %d %x %x %x %x %x %x %x %x '%s'\n", k, a->tag, a->a[0], a->a[1], a->a[2], a->a[3], a->a[4], a->a[5], a->a[6], a->a[7], a->s);
        if (k < nlog[1]) printf("  mine[%d] tag %d %x %x %x %x %x %x %x %x '%s'\n", k, b->tag, b->a[0], b->a[1], b->a[2], b->a[3], b->a[4], b->a[5], b->a[6], b->a[7], b->s);
        break;
    }
    for (k = 0; k < (int)sizeof glob_a; k++)
        if (glob_a[k] != *D(GLOB_LO + k)) { printf("  data differs at 0x%x\n", GLOB_LO + k); break; }
}

int main(int argc, char **argv)
{
    long n = argc > 1 ? atol(argv[1]) : 1000000, i;
    long count[5] = {0}, ntypes[16] = {0};
    if (argc > 2) seed ^= strtoull(argv[2], 0, 0) * 0x2545f4914f6cdd1dull;
    memcpy(state_orig, D(STATE_TAB), sizeof state_orig);
    memcpy(seq_orig, D(SEQ_TAB), sizeof seq_orig);
    memcpy(alias_orig, D(ALIAS), sizeof alias_orig);
    for (i = 0; i < n; i++) {
        int which = rnd() % 5, r0 = 0, r1 = 0, id = 0, k;
        unsigned edi = rnd(), w10 = rnd(), w14 = rnd() % 4 ? 0xffffffffu : rnd();
        char *entry = 0;
        int index = 0, no_attr = 0;
        randomise();
        if (which == 0 || which == 1) {           /* an id of the table (sometimes -1, 0 or unknown) */
            unsigned tab = which == 0 ? STATE_TAB : SEQ_TAB, cnt = which == 0 ? 181 : 41;
            int nt = which == 0 ? ntouched_state : ntouched_seq, *tt = which == 0 ? touched_state : touched_seq;
            switch (rnd() % 8) {
            case 6: case 7:                      /* an entry randomised in this case (other transition types) */
                id = nt ? *(int *)D(tab + tt[rnd() % nt] * 0x54 + 0x24) : -1; break;
            case 0: id = -1; break;
            case 1: id = 0; break;
            case 2: id = (int)rnd(); break;
            default: id = *(int *)D(tab + (rnd() % cnt) * 0x54 + 0x24); break;
            }
        } else if (which == 3) {                  /* the transition itself, with any entry */
            switch (rnd() % 4) {
            case 0: entry = 0; break;
            case 1: entry = (char *)D(SEQ_TAB + (rnd() % 41) * 0x54); break;
            default: entry = (char *)D(STATE_TAB + (rnd() % 181) * 0x54); break;
            }
            if (entry && rnd() % 2) rnd_entry((unsigned char *)entry, 64);
            index = rnd() % 3 ? (int)(rnd() % 64) : rnd_small();
            if (index < 0 || index >= 64) index = rnd() % 64;   /* the counter array: keep the write inside the globals */
            no_attr = rnd() % 3 ? (int)(rnd() % 2) : (int)rnd();
        }
        if (which == 3 && entry) ntypes[(unsigned)*(int *)(entry + 0x20) < 15 ? *(int *)(entry + 0x20) : 15]++;
        save();
        for (side = 0; side < 2; side++) {
            int r;
            nlog[side] = 0;
            restore();
            switch (which) {
            case 0: r = side ? FUN_10006560(id) : call_orig_6560(id, 0xffffffffu, edi); break;
            case 1: r = side ? FUN_10006620(id) : call_orig_6620(id, 0xffffffffu, edi); break;
            case 2: case 4: r = side ? FUN_100064d0() : call_orig_64d0(0xffffffffu, edi); break;
            default:
                if (side) FUN_100068b0(entry, index, no_attr, w14, (unsigned)(uintptr_t)orig68b0_ret);
                else call_orig_68b0(entry, index, no_attr, w10, w14);
                r = 0;
                break;
            }
            if (side == 0) { r0 = r; memcpy(glob_a, D(GLOB_LO), sizeof glob_a); flag_a = DW(0x1001e688); }
            else r1 = r;
        }
        count[which]++;
        if (r0 != r1 || nlog[0] != nlog[1] || memcmp(logbuf[0], logbuf[1], nlog[0] * sizeof(Ev))
            || memcmp(glob_a, D(GLOB_LO), sizeof glob_a) || flag_a != DW(0x1001e688))
            fail(which == 0 ? "FUN_10006560" : which == 1 ? "FUN_10006620" : which == 3 ? "FUN_100068b0" : "FUN_100064d0", i, r0, r1);
    }
    printf("cases %ld: FUN_10006560 %ld, FUN_10006620 %ld, FUN_100064d0 %ld, FUN_100068b0 %ld\n",
           n, count[0], count[1], count[2] + count[4], count[3]);
    printf("ImSetTrigger: %ld calls, %ld with p9 = a return address of FUN_10006560/10006620, %ld command-0 triggers"
           " (p9 = caller ESI), %ld of them with ESI 0\n", cov_trig, cov_ret, cov_cmd0, cov_esi0);
    printf("FUN_100068b0 entry types 0..14,other:");
    for (i = 0; i < 16; i++) printf(" %ld", ntypes[i]);
    printf("\n%ld differences\n", fails);
    return fails != 0;
}
