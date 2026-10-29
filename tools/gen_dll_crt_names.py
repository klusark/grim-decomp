"""Names for the MSVC 6 C runtime linked into LUA.DLL and IMUSE.DLL.

Matched function by function (size, callees, Win32 API usage) against the
already-named runtime in GRIMFANDANGO.EXE.  Writes names/lua_crt.json and
names/imuse_crt.json.
"""
import json, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

LUA = {
 0xef80: '_ftol', 0xefa8: '_setjmp3', 0xf030: '_CallSettingFrame', 0xf080: '_UnwindNestedFrames',
 0xf180: '__CxxFrameHandler', 0xf390: '_global_unwind2', 0xf3d2: '_local_unwind2',
 0xf43a: '_unwind_handler', 0xf466: '_NLG_Notify', 0xf480: '_snprintf', 0xf4f0: 'sprintf',
 0xf560: 'printf', 0xf680: 'strtol', 0xf6a0: 'strtoxl', 0xfa20: 'memcpy', 0xfd58: '_except_handler3',
 0xff30: '_dosmaperr', 0xffb0: '_errno', 0xffc0: '__doserrno', 0x11bc0: 'tolower', 0x11c50: '_tolower_lk',
 0x12390: 'bsearch', 0x12430: 'qsort', 0x125e0: 'shortsort', 0x12640: 'qsort_swap', 0x12670: 'strncpy',
 0x12900: '_isctype', 0x12aa0: 'sscanf', 0x12af0: 'strcoll', 0x12e80: '_amsg_exit',
 0x134c0: '__InternalCxxFrameHandler', 0x13590: 'FindHandler', 0x13850: 'Eh_FindForeignHandler',
 0x13930: 'FrameUnwindToState', 0x13a10: 'CatchIt', 0x13aa0: 'CallCatchBlock', 0x13b98: 'Eh_CallCatchBlockInner',
 0x13c30: 'BuildCatchObject', 0x13fd0: '_initptd', 0x13ff0: '_getptd', 0x14120: 'terminate',
 0x14240: '_flsbuf', 0x14370: '_output', 0x14d00: 'write_char', 0x14d50: 'write_multi_char',
 0x14d90: 'write_string', 0x14dd0: 'get_int_arg', 0x14df0: 'get_short_arg', 0x14e10: 'get_int64_arg',
 0x14ee0: '_lock', 0x14f60: '_unlock', 0x14fc0: '_lock_file2', 0x15030: '_unlock_file2', 0x15060: '_stbuf',
 0x15120: '_ftbuf', 0x15440: 'calloc', 0x155c0: 'exit', 0x155f0: 'doexit', 0x156b0: '_lockexit',
 0x156c0: '_unlockexit', 0x156d0: '_initterm', 0x15730: '_flush', 0x15870: 'malloc', 0x15890: '_nh_malloc',
 0x158e0: '_heap_alloc', 0x17ba0: 'free', 0x18790: '__crtLCMapStringW', 0x189a0: 'wcsncnt',
 0x189e0: '__crtLCMapStringA', 0x1b000: '__crtGetStringTypeW', 0x1b190: '__crtGetStringTypeA',
 0x1b2d0: '_input', 0x1c010: '_hextodec', 0x1c050: '_inc', 0x1c080: '_un_inc', 0x1c0a0: '_whiteout',
 0x1c0f0: '__crtCompareStringA', 0x1c3c0: '_strncnt', 0x1c3f0: 'wcstol', 0x1c410: 'wcstoxl',
 0x1c5f0: '__crtGetLocaleInfoA', 0x1d300: '_FF_MSGBANNER', 0x1d340: '_NMSG_WRITE',
 0x1de60: '_ValidateRead', 0x1de80: '_ValidateWrite', 0x1dea0: '_ValidateExecute', 0x1dfa0: 'abort',
 0x1dfc0: '_lseek', 0x1e040: '_lseek_lk', 0x1e0c0: '_write', 0x1e140: '_write_lk', 0x1e350: '_getbuf',
 0x1e3b0: '_isatty', 0x1e3e0: 'wctomb', 0x1e450: '_wctomb_lk', 0x1e4d0: '_aulldiv', 0x1e540: '_aullrem',
 0x1e5c0: '_callnewh', 0x1e5e0: '__sbh_alloc_new_region', 0x1e750: '__sbh_release_region',
 0x1e7b0: '__sbh_decommit_pages', 0x1e880: '__sbh_find_block', 0x1e8e0: '__sbh_free_block',
 0x1e940: '__sbh_alloc_block', 0x1eb80: '__sbh_alloc_new_group', 0x1f670: '_get_osfhandle',
 0x1f6c0: '_lock_fhandle', 0x1f730: '_unlock_fhandle', 0x1f760: '_read', 0x1f7e0: '_read_lk',
 0x20510: 'mbtowc', 0x20590: '_mbtowc_lk', 0x20690: '_allmul', 0x206f0: '_filbuf', 0x207e0: '_ungetc_lk',
 0x20870: 'toupper', 0x20900: '_toupper_lk', 0x20980: 'iswctype', 0x20a10: '__crtMessageBoxA',
 0x20aa0: 'raise', 0x20cb0: 'siglookup',
}
IMUSE = {
 0xd210: '_flsbuf', 0xd340: '_dosmaperr', 0xd3c0: '_errno', 0xd3d0: '__doserrno', 0xd3e0: '_lseek',
 0xd460: '_lseek_lk', 0xd520: '_flush', 0xd660: '_ftell_lk', 0xe0c0: 'free', 0xe130: '_close',
 0xe1a0: '_close_lk', 0xe230: '_freebuf', 0xe270: '_write', 0xe2f0: '_write_lk', 0xe5a0: '_tolower_lk',
 0xe6a0: '_isctype', 0xe780: '__crtLCMapStringA', 0xe9b0: '_strncnt', 0xea10: 'exit', 0xea40: 'doexit',
 0xeb00: '_lockexit', 0xeb10: '_unlockexit', 0xeb20: '_initterm', 0xebd0: '_initptd', 0xebf0: '_getptd',
 0xfa30: '_FF_MSGBANNER', 0xfa70: '_NMSG_WRITE', 0xfc50: 'malloc', 0xfc70: '_nh_malloc', 0xfcc0: '_heap_alloc',
 0xfd20: '_isatty', 0xff30: 'calloc', 0x10080: '_getbuf', 0x10300: '_free_osfhnd', 0x103a0: '_get_osfhandle',
 0x103f0: '_lock_fhandle', 0x10460: '_unlock_fhandle', 0x114c0: '__sbh_alloc_new_region',
 0x11630: '__sbh_release_region', 0x11690: '__sbh_decommit_pages', 0x11760: '__sbh_find_block',
 0x117c0: '__sbh_free_block', 0x11820: '__sbh_alloc_block', 0x11a60: '__sbh_alloc_new_group',
 0x12d50: '__crtGetStringTypeA', 0x12e90: '__crtMessageBoxA', 0x12f20: '_callnewh',
 # the "hmi" range turned out to be CRT stdio as well
 0xb940: 'fseek', 0xb980: '_fseek_lk', 0xbb10: 'fclose', 0xbb50: '_fclose_lk', 0xbbc0: 'fwrite',
 0xbc00: '_fwrite_lk', 0xbd50: 'strchr', 0xbd80: 'strncpy', 0xbe80: '_stricmp', 0xbf50: 'atol',
 0xbff0: 'atoi', 0xc000: 'bsearch', 0xc400: '_amsg_exit', 0xc4f0: '_lock', 0xc570: '_unlock',
 0xc590: '_lock_file', 0xc600: '_unlock_file',
}


def gen(prog, table, out):
    base = 0x10000000
    entries = [{'program': prog, 'addr': '%08x' % (base + a), 'name': n,
                'comment': 'MSVC 6 C runtime (matched against the EXE runtime by structure)', 'tags': 'crt'}
               for a, n in sorted(table.items())]
    json.dump(entries, open(os.path.join(ROOT, 'names', out), 'w'), indent=0)
    print(out, len(entries))


gen('/LUA.DLL', LUA, 'lua_crt.json')
gen('/v101/IMUSE.DLL', IMUSE, 'imuse_crt.json')
