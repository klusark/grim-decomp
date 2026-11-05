# stdPic_LoadInto (0x0047d2d0) to C

Port: `build/overrides_big_stdpic_loadinto.c` (one function plus a static byte-swap helper, `/* OVERRIDES: stdPic_LoadInto */`).
Test: `build/difftest/big_stdpic_loadinto/run.sh [cases]` (`pic_test.c`). Nothing was regenerated: the function is still
in `src/GRIMFANDANGO.EXE/asm_funcs.s` until the next build_src / gen_asm run. After that, run the test with
`BASE_ASM=<copy of today's asm_funcs.s>` (`git show HEAD:src/GRIMFANDANGO.EXE/asm_funcs.s`).

## What the function does

`stdPic_LoadInto(path, bm, videoMem, sysMem)` is the `.pic` loader that `stdPic_Load` (0x0047d280) calls. It reads Softimage PIC
files. The format:

* A 0x68 byte big-endian header: magic 0x5380f634, version (float), comment[80], id "PICT", width, height, ratio (float),
  fields, pad. Only the magic and the id are checked.
* 4 byte channel packets: chained, size, type, channel mask (R 0x80, G 0x40, B 0x20, A 0x10). Every packet must have size 8.
  The list ends at chained == 0.
* For each row, for each packet: `width` pixels of that packet's channels. Type 0 is uncompressed. Any other type is mixed RLE:
  * n < 0x80: n+1 literal pixels;
  * n == 0x80: a 16 bit big-endian count, then one pixel;
  * n > 0x80: n-0x7f copies of one pixel.
* The picture goes into a 24 bit RGB surface (`Surface_Create` with the colour format {1, 24, 8,8,8, 16,8,0, 0...}). R, G and
  B sit at +0, +1 and +2 of each 3-byte pixel, and rows are `surface+0x18` (pitch) apart. Alpha is read into a scratch slot
  and dropped.
* `bm` (0x7c bytes) gets:
  * the zeroed record;
  * the file name (`strncpy` of 0x1f bytes);
  * +0x64 = 1;
  * the colour format at +0x28;
  * at +0x78, a 4 byte block allocated with `pAlloc` (stdPic.c, line base + 0x6d) that holds the surface pointer.
* Return value: 1 when the image loads, 0 otherwise.

Behaviour of the original that the C keeps:

* **Early returns.** An early return (open, header read, magic, id, a packet read or a packet size other than 8) does not
  close the file.
* **Unchecked reads and writes.** Pixel freads are not checked. x can run past the row end, so writes continue into the next
  row or past the buffer. When an assert fails, the function continues.
* **Packet types overwrite the frame.** Packet types are stored, with no bound, at ESP+0x60+4*i. The C models the frame
  from ESP+0x60 to ESP+0x15c as one array (`fr`):
  * packet 27 overwrites width and height (width becomes the type, height becomes 0);
  * packets 30-43 overwrite the colour format block that `bm` and Surface_Create receive;
  * packets 44-62 overwrite the Surface_Create description;
  * the pixel loop then reads those slots back as packet types.
* **The lost `_ftol` operand.** The two `_ftol` calls swap the version and ratio floats. Each takes the float as read (wrong
  byte order), truncates it to an integer, byte-swaps the integer and converts it back through `fild qword`. Ghidra lost the
  operand, which is that float. The results are dead (nothing reads them), but the C does the same arithmetic.
* **Scratch bytes that persist between runs.** These matter only for truncated files, because a failed fread leaves them as
  they were:
  * the RLE count byte: 0xff after a literal run;
  * the 16 bit count: 0xffff after a repeat run;
  * the R and G run colours: before the first run they hold the 0x20 and 0x40 bits of the last packet's mask, which the
    packet loop parks in the same bytes;
  * the B run colour.

## Verification

The original instructions (sliced with their `_ftol`, renamed `orig_*`) and the C (compiled with the build's flags, at -O0 and
at -O2) are linked with the original data image (`data_s.o`). Both run on the same start state.

**Fakes.** `g_pSvcMain` points to fake services (fopen, fread, fclose, alloc, assert). Surface_Create, Surface_Lock,
Surface_Unlock, Str_FileNameFromPath and strncpy are also fakes. Every call, with its arguments and return value, goes into a
log hash. Pointers are logged as an offset into the pixel buffer or `bm`, or as "local".

**Compared:**
* the return value;
* the call log (count and hash);
* `bm`, plus 0x40 bytes after it;
* the surface block;
* all 19 dwords of the Surface_Create description;
* the whole reachable pixel buffer, prefilled with random bytes.

Before each call 16 KB of stack are zeroed, so bytes the original never initialises are 0, as in the C.

**Inputs.** Generated files of eight kinds, about equally often:
* valid images: sizes 0-300 x 0-80, 1-8 packets, any channel masks (also odd ones), types 0 / 2 / random, all three run kinds;
* runs that overrun the row (long counts up to 65535);
* random bit flips;
* truncation at any byte;
* random data after the packets;
* 5-62 packets (the frame overwrites);
* damaged magic, id or packet bytes.

Other variations: fread failing at a random call, fopen failing (1/40), Surface_Lock failing (1/10, assert path), random
pitches (exact, larger, smaller than 3*width) and path names longer than 31 characters.

**Result:** 200000 cases (160172 loaded images), 0 differences, and 100000 more with the C at -O2, also 0.

**Sensitivity.** 13 deliberately wrong versions were run. 12 were detected: the 0xffff count-slot state, the bound of the
type array, the n-0x7f count, the B colour's initial value, the width/height swap, the line number, the dropped alpha read,
the stale R/G colours (two variants), the count-byte state, the strncpy length, the literal-run stop and an fclose on the
error path. The 13th (skipping RLE when height is 0) is equivalent to the original, so no test could catch it.

No game data contains a .pic file (the LAB directories of the GOG data list none), so only generated images were used.

## Not covered or different

* **63 or more packets.** The original writes types over its own return address and then its arguments (`path`, `bm`). It
  crashes, at the latest when it returns. The C drops those stores (`FR_N`) and reads such types as 0. The test skips these
  files and those that need too much work (width*height*packets > 400000).
* **Allocation or Surface_Create failure.** Both crash the original right after the assert, on a NULL write or read. The C
  does the same, so these paths are not run.
* **Uninitialised stack.** On truncated files, the original reads stack bytes it never wrote: the first RLE count byte, the
  16 bit count and the B colour. In the game these are whatever earlier calls left on the stack. The C uses 0, which matches
  the test's zeroed stack but not necessarily the real game.
* **FPU status flags.** The test does not compare them. An invalid-operation flag can be raised by `_ftol` of a NaN or
  out-of-range version or ratio.
