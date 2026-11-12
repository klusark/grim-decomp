#!/bin/sh
# Compiler wrapper for the native Linux build (make -C build linux).
#
# The tree names Win32 imports and stdcall/fastcall functions with their PE decorations
# (`__asm__("_CreateFileA@28")`, `@f@8`). An ELF assembler does not accept `@` in a symbol name, so
# this compiles to assembly, rewrites  _f@N -> _f__atN  and  @f@N -> __fc_f__atN, then assembles.
# Every other argument goes to gcc unchanged.  usage: cc.sh <gcc flags> -c file.c -o file.o
set -e
out= ; args= ; compile=0
while [ $# -gt 0 ]; do
  case "$1" in
    -o) out="$2"; shift 2; continue ;;
    -c) compile=1 ;;
  esac
  args="$args '$(printf %s "$1" | sed "s/'/'\\\\''/g")'"
  shift
done
GCC=${LINUX_GCC:-gcc}
if [ "$compile" = 0 ] || [ -z "$out" ]; then eval exec "$GCC" $args ${out:+-o "'$out'"}; fi
tmp="$out.tmp.s"
args=$(printf %s "$args" | sed "s/ '-c'/ '-S'/")
eval "$GCC" $args -o "'$tmp'"
sed -E -i 's/\.def [^;]*; *\.scl [^;]*; *\.type [^;]*; *\.endef//g; s/@([A-Za-z_][A-Za-z0-9_]*)@([0-9]+)/__fc_\1__at\2/g; s/([A-Za-z_][A-Za-z0-9_]*)@([0-9]+)/\1__at\2/g' "$tmp"
"$GCC" -m32 -c "$tmp" -o "$out"
rm -f "$tmp"
