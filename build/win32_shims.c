/* Win32 entry points the game imports that the mingw import libraries do not
 * provide as functions (they are compiler intrinsics today). Defined with the
 * decorated stdcall names the decompiled code binds to. Linked by link.py. */
long __attribute__((stdcall)) shim_InterlockedIncrement(long *p) __asm__("_InterlockedIncrement@4");
long __attribute__((stdcall)) shim_InterlockedDecrement(long *p) __asm__("_InterlockedDecrement@4");
long __attribute__((stdcall)) shim_InterlockedExchange(long *p, long v) __asm__("_InterlockedExchange@8");

long __attribute__((stdcall)) shim_InterlockedIncrement(long *p) { return __sync_add_and_fetch(p, 1); }
long __attribute__((stdcall)) shim_InterlockedDecrement(long *p) { return __sync_sub_and_fetch(p, 1); }
long __attribute__((stdcall)) shim_InterlockedExchange(long *p, long v) { return __sync_lock_test_and_set(p, v); }

/* libmingwex's math helpers want this error hook; the game never installs one. */
void __mingw_raise_matherr(int typ, const char *name, double a1, double a2, double rslt) { (void)typ; (void)name; (void)a1; (void)a2; (void)rslt; }
/* pseudo-relocation support of the mingw runtime, unused without it */
void _pei386_runtime_relocator(void) {}

/* ---- registry access without elevation ----------------------------------
 * The game opens HKLM\SOFTWARE\LucasArts...\Grim Fandango\v1.0 with
 * KEY_ALL_ACCESS and builds its value cache from that handle. Without
 * administrator rights the open fails and every setting reads as missing
 * (the game then looks for its data on a CD-ROM). These wrappers take the
 * import's decorated name, so the decompiled calls land here first
 * (--allow-multiple-definition), try the original request and fall back to
 * read-only access. Writes to HKLM still fail, as they do in the original. */
extern long (__attribute__((stdcall)) *real_RegOpenKeyExA)(void *, const char *, unsigned, unsigned, void **) __asm__("__imp__RegOpenKeyExA@20");
extern long (__attribute__((stdcall)) *real_RegCreateKeyExA)(void *, const char *, unsigned, char *, unsigned, unsigned, void *, void **, unsigned *) __asm__("__imp__RegCreateKeyExA@36");

long __attribute__((stdcall)) shim_RegOpenKeyExA(void *key, const char *sub, unsigned opt, unsigned sam, void **out) __asm__("_RegOpenKeyExA@20");
long __attribute__((stdcall)) shim_RegCreateKeyExA(void *key, const char *sub, unsigned res, char *cls, unsigned opt, unsigned sam, void *sec, void **out, unsigned *disp) __asm__("_RegCreateKeyExA@36");

long __attribute__((stdcall)) shim_RegOpenKeyExA(void *key, const char *sub, unsigned opt, unsigned sam, void **out)
{
    long r = real_RegOpenKeyExA(key, sub, opt, sam, out);
    if (r == 5 /* ERROR_ACCESS_DENIED */ && (sam & 0x20006) /* write bits */)
        r = real_RegOpenKeyExA(key, sub, opt, 0x20019 /* KEY_READ */, out);
    return r;
}

long __attribute__((stdcall)) shim_RegCreateKeyExA(void *key, const char *sub, unsigned res, char *cls, unsigned opt, unsigned sam, void *sec, void **out, unsigned *disp)
{
    long r = real_RegCreateKeyExA(key, sub, res, cls, opt, sam, sec, out, disp);
    if (r == 5 && (sam & 0x20006)) {
        r = real_RegOpenKeyExA(key, sub, 0, 0x20019, out);
        if (r == 0 && disp) *disp = 2 /* REG_OPENED_EXISTING_KEY */;
    }
    return r;
}
