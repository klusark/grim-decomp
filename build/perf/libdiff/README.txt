Differential tests of single functions: original code vs msvcrt.dll on random inputs (see docs/LIBS_INVENTORY.md section 6).
Build with the i686 toolchain: PATH=/mingw32/bin:$PATH gcc -O1 difftest_math.c -o difftest_math.exe
  difftest_math.exe   <baseline lua.dll>    floor/ceil (Ghidra's names are swapped: orig floor == msvcrt ceil), _CIasin, _ftol
  difftest_fmod.exe   <baseline lua.dll>    the original fprem loop vs msvcrt _CIfmod
  difftest_chore.exe  <baseline chore.dll>  CHORE.DLL's qsort/bsearch/strncpy/strrchr/strchr/_stricmp/memmove vs msvcrt (qsort differs on ties)
  difftest_imuse.exe  <baseline imuse.dll>  IMUSE.DLL's strrchr(Im_StrChr)/strncpy(Im_MemCopy)/_stricmp vs msvcrt (run with the game folder as cwd/PATH: HMIFX*.DLL)
  difftest_strncat.exe <file>               machine code bytes of EXE FUN_004ae410 (raw/GRIMFANDANGO.EXE/sections/text.bin offset 0x4ae410-0x401000, 304 bytes) vs strncat
The baseline DLLs are the rebuilt DLLs of the tree before the library work (they export every function).
