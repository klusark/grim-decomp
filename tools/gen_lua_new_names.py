"""Names for the functions Ghidra discovered in LUA.DLL after the exported entry
points were defined: Lua 3.1 iolib/strlib pieces and more of the MSVC 6 C
runtime (matched against the EXE runtime by structure).  Writes
names/lua_new.json."""
import json, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CRT = 'MSVC 6 C runtime (matched against the EXE runtime by structure)'
T = {
 # Lua library code
 0x1970: ('luaA_normalizeObj', 'lapi', ''),
 0x25f0: ('luaA_callObject', 'lapi', 'Opens stack space and runs luaD_call for the C API'),
 0x53d0: ('io_getint', 'liolib', 'liolib.c helper: numeric argument through lua2C'),
 0x53f0: ('io_pushresult', 'liolib', 'Pushes userdata/nil plus strerror(errno) like Lua 3.1 pushresult'),
 0x5430: ('io_setfile', 'liolib', 'Stores a file handle in a global (_INPUT/_OUTPUT) with the file tag'),
 0x5480: ('io_getfilebyname', 'liolib', "errors '%s is not a file'"),
 0x54c0: ('io_gethandle', 'liolib', "checks the userdata tag and errors 'a closed file'"),
 0x5520: ('io_setreturn', 'liolib', ''),
 0x5550: ('io_setfilebyname', 'liolib', ''),
 0x5780: ('io_getfileparam', 'liolib', ''),
 0x5b20: ('lua_iolibopen', 'liolib', 'Registers readfrom/writeto/... and the _INPUT/_OUTPUT globals'),
 0x95b0: ('str_sub', 'lstrlib', 'lstrlib.c strsub'),
 0x9650: ('str_addnchar', 'lstrlib', ''),
 0x9680: ('str_closeandpush', 'lstrlib', ''),
 0x9760: ('str_addstr', 'lstrlib', ''),
 0x97f0: ('str_singlematch', 'lstrlib', 'luaI_singlematch: one pattern item against one char'),
 0x99e0: ('str_bracket_end', 'lstrlib', ''),
 0x9a10: ('str_matchclass', 'lstrlib', '%a %d %s ... character classes'),
 0x9e40: ('str_push_captures', 'lstrlib', "errors 'unfinished capture'"),
 0x9ea0: ('str_match', 'lstrlib', "recursive pattern matcher; errors 'too many captures'"),
 0xa030: ('str_capture_to_close', 'lstrlib', ''),
 0xa060: ('str_matchbalance', 'lstrlib', "errors 'unbalanced pattern'"),
 0xa150: ('str_check_capture', 'lstrlib', "errors 'invalid capture index'"),
 0xa180: ('str_expand', 'lstrlib', 'max/min expansion of a repeated pattern item'),
 0xa2e0: ('str_add_value', 'lstrlib', 'gsub replacement: string or function result'),
 0xa680: ('str_add_s', 'lstrlib', 'gsub replacement string with %n captures'),
 # C runtime
 0xf930: ('strtoul', 'crt', CRT), 0xf960: ('strchr', 'crt', CRT), 0xfec0: ('strerror', 'crt', CRT),
 0xffd0: ('system', 'crt', CRT), 0x10090: ('remove', 'crt', CRT), 0x100c0: ('rename', 'crt', CRT),
 0x10100: ('tmpnam', 'crt', CRT), 0x10220: ('tmpnam_genfname', 'crt', CRT), 0x10310: ('getenv', 'crt', CRT),
 0x10340: ('_getenv_lk', 'crt', CRT), 0x103d0: ('strftime', 'crt', CRT), 0x103f0: ('_Strftime', 'crt', CRT),
 0x10540: ('_expandtime', 'crt', CRT), 0x10ae0: ('_store_str', 'crt', CRT), 0x10b10: ('_store_num', 'crt', CRT),
 0x10bb0: ('_store_number', 'crt', CRT), 0x10c20: ('_store_winword', 'crt', CRT), 0x10f70: ('localtime', 'crt', CRT),
 0x11160: ('time', 'crt', CRT), 0x11290: ('setlocale', 'crt', CRT), 0x11560: ('_setlocale_set_cat', 'crt', CRT),
 0x116c0: ('_setlocale_get_all', 'crt', CRT), 0x117e0: ('_expandlocale', 'crt', CRT),
 0x11a40: ('__lc_strtolc', 'crt', CRT), 0x11b50: ('__lc_lctostr', 'crt', CRT),
 0x11d50: ('_CIsqrt', 'crt', CRT), 0x11d6d: ('_sqrt', 'crt', CRT), 0x11ef0: ('floor', 'crt', CRT + '; floor/ceil pair, order not verified'),
 0x11ff0: ('ceil', 'crt', CRT + '; floor/ceil pair, order not verified'), 0x12130: ('_CIpow', 'crt', CRT),
 0x12152: ('_pow', 'crt', CRT + '; Ghidra cannot decompile it (overlapping varnodes)'), 0x12325: ('_ftol', 'crt', CRT),
 0x12770: ('toupper', 'crt', CRT), 0x12800: ('_toupper_lk', 'crt', CRT), 0x12a20: ('strcmp', 'crt', CRT),
 0x12a60: ('strncmp', 'crt', CRT), 0x12cb0: ('_CRT_INIT', 'crt', CRT + ' (DLL entry work: heap, mt, io, locale)'),
 0x130b0: ('_cftoe', 'crt', CRT), 0x13130: ('_cftoe2', 'crt', CRT), 0x13230: ('_cftof', 'crt', CRT),
 0x132a0: ('_cftof2', 'crt', CRT), 0x13360: ('_cftog', 'crt', CRT), 0x13490: ('_shift', 'crt', CRT),
 0x13f40: ('_mtinit', 'crt', CRT), 0x13fa0: ('_mtterm', 'crt', CRT), 0x14070: ('_freeptd', 'crt', CRT),
 0x14e30: ('_mtinitlocks', 'crt', CRT), 0x14e60: ('_mtdeletelocks', 'crt', CRT), 0x151d0: ('_ioinit', 'crt', CRT),
 0x153e0: ('_ioterm', 'crt', CRT), 0x15590: ('_cinit', 'crt', CRT), 0x155e0: ('_cexit', 'crt', CRT),
 0x15940: ('_spawnvpe_search', 'crt', CRT), 0x15b30: ('_spawnvpe', 'crt', CRT), 0x15d30: ('_spawnve', 'crt', CRT),
 0x15da0: ('_access', 'crt', CRT), 0x15ef0: ('_strdup', 'crt', CRT), 0x16020: ('_mbschr', 'crt', CRT),
 0x16130: ('_strnicoll', 'crt', CRT), 0x16170: ('__crtsetenv_from_wenviron', 'crt', CRT), 0x161f0: ('__tzset', 'crt', CRT),
 0x16230: ('_tzset_lk', 'crt', CRT), 0x16510: ('_isindst', 'crt', CRT), 0x16540: ('_isindst_lk', 'crt', CRT),
 0x167b0: ('_cvtdate', 'crt', CRT), 0x16950: ('_stricmp', 'crt', CRT), 0x16a20: ('gmtime', 'crt', CRT),
 0x16b90: ('__loctotime_t', 'crt', CRT), 0x17c50: ('__get_qualified_locale', 'crt', CRT),
 0x17e50: ('GetLcidFromLangCountry', 'crt', CRT), 0x181c0: ('GetLcidFromLanguage', 'crt', CRT),
 0x18300: ('GetLcidFromCountryOnly', 'crt', CRT), 0x183e0: ('GetLcidFromDefault', 'crt', CRT),
 0x18400: ('TranslateName', 'crt', CRT), 0x18fd0: ('_frnd', 'crt', CRT), 0x19100: ('_raise_exc', 'crt', CRT),
 0x19440: ('_handle_exc', 'crt', CRT), 0x1ad40: ('_pow_special_cases', 'crt', CRT), 0x1af70: ('_is_integer_double', 'crt', CRT),
 0x1c860: ('_setenvp', 'crt', CRT), 0x1c950: ('_setargv', 'crt', CRT), 0x1c9f0: ('parse_cmdline', 'crt', CRT),
 0x1cc00: ('_setmbcp', 'crt', CRT), 0x1ce30: ('getSystemCP', 'crt', CRT), 0x1cee0: ('setSBCS', 'crt', CRT),
 0x1cf20: ('setSBUpLow', 'crt', CRT), 0x1d100: ('__initmbctable', 'crt', CRT),
 0x1d110: ('__crtGetEnvironmentStringsA', 'crt', CRT), 0x1d270: ('_heap_init', 'crt', CRT), 0x1d2b0: ('_heap_term', 'crt', CRT),
 0x1d940: ('_ld12tocvt', 'crt', CRT), 0x1db10: ('_ld12tod', 'crt', CRT), 0x1db30: ('_ld12tof', 'crt', CRT),
 0x1db50: ('_atodbl', 'crt', CRT), 0x1db90: ('_atoflt', 'crt', CRT), 0x1dbd0: ('_fptostr', 'crt', CRT),
 0x1ed00: ('__sbh_resize_block', 'crt', CRT), 0x1efc0: ('_mbschr_lk', 'crt', CRT), 0x1f090: ('_dospawn', 'crt', CRT),
 0x1f320: ('_cenvarg', 'crt', CRT), 0x1fa10: ('strrchr', 'crt', CRT), 0x1fa40: ('__crtsetenv', 'crt', CRT),
 0x1fc50: ('findenv', 'crt', CRT), 0x1fcd0: ('copy_environ', 'crt', CRT), 0x1fd40: ('atol', 'crt', CRT),
 0x1fde0: ('wcstombs', 'crt', CRT), 0x1fe60: ('_wcstombs_lk', 'crt', CRT), 0x20050: ('wcsncnt', 'crt', CRT),
 0x20240: ('_strnicmp', 'crt', CRT), 0x20350: ('_except1', 'crt', CRT), 0x209f0: ('wcslen', 'crt', CRT),
 0x20cf0: ('__addl', 'crt', CRT), 0x20d20: ('__add_12', 'crt', CRT), 0x20d90: ('__shl_12', 'crt', CRT),
 0x20dc0: ('__shr_12', 'crt', CRT), 0x20df0: ('__mtold12', 'crt', CRT), 0x20ef0: ('__strgtold12', 'crt', CRT),
 0x21680: ('_I10_OUTPUT', 'crt', CRT), 0x21a80: ('realloc', 'crt', CRT), 0x21c30: ('__ld12mul', 'crt', CRT),
 0x21ef0: ('__multtenpow12', 'crt', CRT),
}
entries = [{'program': '/LUA.DLL', 'addr': '%08x' % (0x10000000 + a), 'name': n, 'comment': c or None, 'tags': tag}
           for a, (n, tag, c) in sorted(T.items())]
for e in entries:
    if e['comment'] is None:
        del e['comment']
json.dump(entries, open(os.path.join(ROOT, 'names', 'lua_new.json'), 'w'), indent=0)
print('lua_new.json', len(entries))
