/* Readable C for GRIMFANDANGO.EXE functions of slice 5, second pass (agent asm_o2; see docs/notes/asm_o2.md).
 *
 * Every function here was written by hand from the original machine code (src/GRIMFANDANGO.EXE/asm_funcs.s) and checked
 * against it with a differential test in build/difftest/asm_s5/ unless its block header says "unverified".
 * tools/build_src.py puts the decompiled text of every function defined here under `#if 0`.
 *
 * Several Ghidra prototypes in functions.h are wrong (a varargs function declared `(void)`, a cdecl memset declared
 * `__fastcall` with five arguments, callbacks declared without parameters).  Those names are renamed while functions.h is
 * included (`#define name name__ghidra`) so the definition below can carry the real prototype; the symbol stays the one the
 * assembled callers use (an `__asm__` label where the decoration differs).  Each such function has an OVERRIDES line. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#define FUN_004d5fd0 FUN_004d5fd0__ghidra
#define msc_MemSet msc_MemSet__ghidra
#define MaterialInstanceSaveLoad FUN_004965b0__ghidra
#define D3D_CreateViewport D3D_CreateViewport__ghidra
#define DDraw_CreateSurfaces DDraw_CreateSurfaces__ghidra
#include "functions.h"
#undef DDraw_CreateSurfaces
#undef D3D_CreateViewport
#undef FUN_004d5fd0
#undef msc_MemSet
#undef MaterialInstanceSaveLoad

#define W16(sym) (*(ushort *)&(sym))
#define S16(sym) (*(short *)&(sym))
#define D32(sym) (*(uint *)&(sym))

/* ==== FUN_004d5fd0 (0x004d5fd0): memset ====
 * Hand-written assembly of the original: fills `count` bytes at `dst` with the byte `value`, in blocks of 20000 bytes,
 * then the count % 4 single bytes, then the rest as dwords.  It is cdecl (the caller pops 12 bytes) although Ghidra
 * declared it __fastcall; the symbol keeps Ghidra's decoration.  A negative count crashes the original (`shr` of a
 * negative count gives a huge dword count); the C does the same unsigned arithmetic. */
/* OVERRIDES: FUN_004d5fd0 */
void FUN_004d5fd0(byte *dst, int value, int count) __asm__("@FUN_004d5fd0@20");
void FUN_004d5fd0(byte *dst, int value, int count)
{
    uint fill = (byte)value * 0x01010101u;
    uint n;

    if (count >= 20000) {
        do {
            for (n = 0; n < 5000; n++) {
                *(uint *)dst = fill;
                dst += 4;
            }
            count -= 20000;
        } while (count > 20000);
    }
    for (n = (uint)count & 3; n != 0; n--)
        *dst++ = (byte)fill;
    for (n = (uint)count >> 2; n != 0; n--) {
        *(uint *)dst = fill;
        dst += 4;
    }
}

/* ==== msc_MemSet (0x004d5e50): memset wrapper ====
 * Calls FUN_004d5fd0(dst, value, count).  The original loads the count into EAX before the call, and the callee's
 * pushad / popad keeps it there, so it returns the count. */
/* OVERRIDES: msc_MemSet */
int msc_MemSet(byte *dst, int value, int count)
{
    FUN_004d5fd0(dst, value, count);
    return count;
}

/* ==== msc_rle_DecompressBlock (0x004d5e70) ====
 * Decodes `count` bytes of the run-length stream at `src` into `dst`.  The original passes a stale ECX to the __fastcall
 * msc_rle_DecompressGetbyte; the argument is only read in a state (not 0, 1 or 2) that msc_rle_DecompressInitialize never leaves, so 0 is passed.  Ends
 * with a jump to the empty Mem_DumpLog (its return value is not used by any caller). */
void msc_rle_DecompressBlock(undefined1 *dst, undefined4 src, int count)
{
    msc_rle_DecompressInitialize((int *)src);
    for (; count != 0; count--)
        *dst++ = (undefined1)msc_rle_DecompressGetbyte(0);
    Mem_DumpLog();
}

/* ==== MaterialInstanceSaveLoad (0x004965b0): colormap component callback ====
 * Stored in a component handler table (sputcostume.c); called with five arguments, it calls the fifth with the fourth
 * plus 8 and 4 (a cdecl reader callback: address, size) and returns 1. */
/* OVERRIDES: MaterialInstanceSaveLoad */
undefined4 MaterialInstanceSaveLoad(undefined4 a1, undefined4 a2, undefined4 a3, int data, code *read)
{
    ((void (*)(int, int))read)(data + 8, 4);
    return 1;
}

/* ==== stdGif_LzwInitEncoder (0x0047e7f0) ====
 * Starts the GIF LZW encoder for `bits` bits per pixel: clear code 1 << bits, end code clear + 1, first free code
 * clear + 2, code size bits + 1, hash table (5003 dwords at 0x0080ccf8) set to -1, "first pixel" flag set.  Writes the
 * minimum code size byte (the low byte of `bits`, through the service table's fwrite) and the clear code.  Returns 1 if
 * the byte was not written, else the error flag DAT_008155f8 (16 bit results: callers keep a short). */
uint stdGif_LzwInitEncoder(undefined4 file, undefined4 bits)
{
    int clear;
    int i;
    uint *hash;

    D32(DAT_008155f8) = 0;
    W16(DAT_00812ed0) = 0;
    UINT_00812ecc = 0;
    W16(UINT_0080cbe4) = (ushort)(bits + 1);
    W16(DAT_00812ec4) = (ushort)(bits + 1);
    clear = 1 << (bits & 0x1f);
    D32(DAT_00811b2c) = clear;
    D32(DAT_00812ebc) = clear + 1;
    D32(DAT_0080cbe8) = clear + 2;
    W16(DAT_0080cbec) = (ushort)(clear + 2);
    W16(DAT_008155f4) = (ushort)((1 << ((byte)UINT_0080cbe4 & 0x1f)) - 1);
    hash = &UINT_0080ccf8;
    for (i = 0x138b; i != 0; i--)
        *hash++ = 0xffffffff;
    W16(DAT_0080cbf0) = 1;
    if ((*g_pStd_HS->pFwrite)(file, &bits, 1) != 1)
        return 1;
    putcode(file, S16(DAT_00811b2c));
    return W16(DAT_008155f8);
}

/* ==== stdGif_LzwEncodePixel (0x0047ea30) ====
 * Feeds one pixel to the LZW encoder.  The first pixel only becomes the current prefix (DAT_00811b24) and sets the hash
 * shift (DAT_00815608: 8 - 4 = 4).  Later pixels look up (pixel << 12) + prefix in the open-addressing hash table
 * (5003 entries; the probe step is 5003 - h, or 1 for h = 0; a negative entry is empty, the probe loop also stops on 0):
 * found, the stored code (0x00812ed8, shorts) becomes the prefix; not found, the prefix code is written, the pixel is the
 * new prefix and the string gets the next free code, or the table is cleared when the free code reaches DAT_004e7800.
 * Returns 0 or the error flag DAT_008155f8 (16 bit). */
uint stdGif_LzwEncodePixel(undefined4 file, byte pixel)
{
    short *codes = (short *)&UINT_00812ed8;
    int *hash = (int *)&UINT_0080ccf8;
    uint key;
    uint h;
    uint step;
    int entry;
    short next;

    D32(DAT_008155f8) = 0;
    if (W16(DAT_0080cbf0) != 0) {
        short shift = 0;

        W16(DAT_00811b24) = pixel;
        key = 0x138b;
        do {
            key += key;
            shift++;
        } while ((int)key < 0x10000);
        UINT_0081560c = key;
        W16(DAT_00815608) = shift;
        W16(DAT_0080cbf0) = 0;
        W16(DAT_00815608) = (ushort)(8 - D32(DAT_00815608));
        return 0;
    }
    key = ((uint)pixel << 12) + W16(DAT_00811b24);
    UINT_0081560c = key;
    h = ((uint)pixel << (DAT_00815608 & 0x1f)) ^ D32(DAT_00811b24);
    entry = hash[(short)h];
    if ((uint)entry == key) {
        W16(DAT_00811b24) = codes[(short)h];
        return 0;
    }
    if (entry >= 0) {
        step = 0x138b - h;
        if ((short)h == 0)
            step = 1;
        for (;;) {
            h -= step;
            if ((short)h < 0)
                h += 0x138b;
            entry = hash[(short)h];
            if ((uint)entry == key) {
                W16(DAT_00811b24) = codes[(short)h];
                return 0;
            }
            if (entry <= 0)
                break;
        }
    }
    putcode(file, S16(DAT_00811b24));
    next = S16(DAT_0080cbec);
    W16(DAT_00811b24) = pixel;
    if (next >= S16(DAT_004e7800)) {
        stdGif_LzwClearTable(file);
        return W16(DAT_008155f8);
    }
    codes[(short)h] = next;
    hash[(short)h] = UINT_0081560c;
    S16(DAT_0080cbec) = next + 1;
    return W16(DAT_008155f8);
}


/* ==== DirectInput polling (0x00477730, 0x00477c20, 0x00477dc0) ====
 * Every key and mouse button has a record of 7 dwords; `e` points at its third dword (the table at 0x00804020, key k at
 * k * 7 dwords, mouse buttons at 0x110 + 0xc .. 0x110 + 0xf, i.e. 0x00805f30):
 *   e[-2] last value that went down, e[-1] frame time at the start of the poll, e[0] state (0 up, else the DirectInput
 *   value), e[1] time of the last change, e[2] time it was last seen down, e[3] number of presses this frame,
 *   e[4] double press (down again within 200 ms of the last time it was seen down).
 * DirectInput methods: GetDeviceState is vtable offset 0x24, GetDeviceData 0x28 (DIDEVICEOBJECTDATA, 16 bytes:
 * dwOfs, dwData, dwTimeStamp, dwSequence). */
#define INPUT_KEYS ((uint *)&UINT_00804020)
#define INPUT_MOUSE_BUTTONS ((uint *)&UINT_00805f30)

static void input_key_event(uint *e, uint value, uint time)
{
    if (value == e[0]) {
        if (value != 0)
            e[2] = time;
        return;
    }
    if (value != 0 && time - e[2] < 200)
        e[4] = 1;
    e[0] = value;
    e[1] = time;
    if (value != 0) {
        e[3] = e[3] + 1;
        e[-2] = value;
        e[2] = time;
    }
}

/* ==== Input_PollKeyboard (0x00477730) ====
 * Starts a new frame for all 288 records (previous state into e[-2], frame time into e[-1], press count and double
 * flag cleared), then applies up to 32 buffered keyboard events with their own time stamps.  Only on a buffer overflow
 * (GetDeviceData returned DI_BUFFEROVERFLOW = 1) the immediate state of the 256 keys is applied with the frame time.
 * The build's patch (names/asm_patches.json, 0x00477794) is kept: when GetDeviceData fails the event count is 0. */
void Input_PollKeyboard(void)
{
    uint count;
    byte keys[0x100];
    uint events[0x20][4];
    void *dev = g_pDInputKeyboard;
    uint now = g_dwCurReadTime;
    uint *e;
    uint i;
    int ret;

    count = 0x20;
    if (dev == 0 || UINT_00805fa0 != 0)
        return;
    for (e = INPUT_KEYS; e < (uint *)&UINT_00805fa0; e += 7) {
        e[-1] = now;
        e[-2] = e[0];
        e[4] = 0;
        e[3] = 0;
    }
    ret = (**(code_std **)(*(int *)dev + 0x28))(dev, 0x10, events, &count, 0);
    if (ret < 0)
        count = 0;    /* build patch */
    for (i = 0; i < count; i++)
        input_key_event(INPUT_KEYS + events[i][0] * 7, events[i][1], events[i][2]);
    if (ret != 1)
        return;
    if ((**(code_std **)(*(int *)g_pDInputKeyboard + 0x24))(g_pDInputKeyboard, 0x100, keys) < 0)
        return;
    now = g_dwCurReadTime;
    for (i = 0, e = INPUT_KEYS; e < (uint *)&UINT_00805c20; i++, e += 7)
        input_key_event(e, keys[i], now);
}

/* ==== Input_PollMouse (0x00477c20) ====
 * Reads the mouse state (DIMOUSESTATE: lX, lY, lZ, 4 button bytes).  The movement is stored at 0x00804000 (x, y, wheel);
 * while UINT_00805fc8 < 25 x and y are averaged with the previous movement (0x00805fcc / 0x00805fd0).  Then the buffered
 * button events (offsets 0xc .. 0xf, DIMOFS_BUTTON0..3) are applied; on a buffer overflow the immediate button state. */
void Input_PollMouse(void)
{
    uint count;
    int state[4];
    uint events[0x20][4];
    uint now;
    uint i;
    int ret;
    uint *e;

    count = 0x20;
    if (UINT_004dea40 == 0)
        return;
    if ((**(code_std **)(*(int *)g_pDInputMouse + 0x24))(g_pDInputMouse, 0x10, state) != 0)
        return;
    _DAT_00804008 = state[2];
    _DAT_00804000 = state[0];
    _DAT_00804004 = state[1];
    if (UINT_00805fc8 < 0x19) {
        _DAT_00804000 = (int)(UINT_00805fcc + state[0]) >> 1;
        _DAT_00804004 = (int)(UINT_00805fd0 + state[1]) >> 1;
    }
    UINT_00805fcc = state[0];
    UINT_00805fd0 = state[1];
    ret = (**(code_std **)(*(int *)g_pDInputMouse + 0x28))(g_pDInputMouse, 0x10, events, &count, 0);
    for (i = 0; i < count; i++) {
        uint ofs = events[i][0];

        if (ofs >= 0xc && ofs <= 0xf)
            input_key_event(INPUT_KEYS + (ofs + 0x110) * 7, events[i][1], events[i][2]);
    }
    if (ret != 1)
        return;
    now = g_dwCurReadTime;
    for (i = 0, e = INPUT_MOUSE_BUTTONS; e < (uint *)&UINT_00805fa0; i++, e += 7)
        input_key_event(e, ((byte *)state)[0xc + i], now);
}

/* ==== Input_FlushJoystick (0x00477dc0) ====
 * Despite the name it works on the mouse: reads the immediate state, flushes the event buffer (GetDeviceData with no
 * buffer and an INFINITE count) and applies the 4 button bytes with the frame time. */
void Input_FlushJoystick(void)
{
    uint count;
    int state[4];
    uint now;
    uint i;
    uint *e;

    count = 0xffffffff;
    if (UINT_004dea40 == 0)
        return;
    (**(code_std **)(*(int *)g_pDInputMouse + 0x24))(g_pDInputMouse, 0x10, state);
    (**(code_std **)(*(int *)g_pDInputMouse + 0x28))(g_pDInputMouse, 0x10, 0, &count, 0);
    now = g_dwCurReadTime;
    for (i = 0, e = INPUT_MOUSE_BUTTONS; e < (uint *)&UINT_00805fa0; i++, e += 7)
        input_key_event(e, ((byte *)state)[0xc + i], now);
}

/* ==== std3D_DrawRenderList (0x00478b40) ====
 * Appends D3DOP_EXIT (opcode 0xb, size 0, count 0) to the instruction stream at PTR_00806918, unlocks the execute
 * buffer (IDirect3DExecuteBuffer::Unlock, 0x14), sets the D3DEXECUTEDATA (0x30 bytes: vertex count UINT_0080695c,
 * instruction offset UINT_0080691c - UINT_008063ec, length PTR_00806918 - UINT_0080691c; SetExecuteData, 0x18) and
 * executes it on the device (IDirect3DDevice::Execute, 0x20) with the viewport PTR_0080660c, D3DEXECUTE_UNCLIPPED.
 * Returns 1 on success, 0 if the unlock or the execute failed. */
int std3D_DrawRenderList(void)
{
    uint data[12];
    int i;

    *(byte *)PTR_00806918 = 0xb;
    *((byte *)PTR_00806918 + 1) = 0;
    *(ushort *)((byte *)PTR_00806918 + 2) = 0;
    PTR_00806918 = (int *)((byte *)PTR_00806918 + 4);
    if ((**(code_std **)(*(int *)g_pD3dExecuteBuffer + 0x14))(g_pD3dExecuteBuffer) != 0)
        return 0;
    for (i = 0; i < 12; i++)
        data[i] = 0;
    data[2] = UINT_0080695c;
    data[3] = UINT_0080691c - UINT_008063ec;
    data[4] = (uint)PTR_00806918 - UINT_0080691c;
    data[0] = 0x30;
    (**(code_std **)(*(int *)g_pD3dExecuteBuffer + 0x18))(g_pD3dExecuteBuffer, data);
    return (**(code_std **)(*(int *)g_pD3dDevice + 0x20))(g_pD3dDevice, g_pD3dExecuteBuffer, PTR_0080660c, 2) == 0;
}

/* ==== D3D_CreateViewport (0x0047a130) ====
 * Called with the width and height of the video mode (Ghidra lost both parameters; the caller in std3d.c passes them).
 * Creates the viewport (IDirect3D::CreateViewport, 0x1c, into PTR_0080660c), adds it to the device (AddViewport, 0x24)
 * and sets a D3DVIEWPORT (0x2c bytes: size, x 0, y 0, width, height, scale w/2 and h/2, max x and y, min / max z 0;
 * SetViewport, 0x14), then D3D_SetViewportRect({0, 0, width, height}).  The x87 code converts the sizes as unsigned
 * 64 bit integers and keeps them in extended precision: max x = (float)w / (w/2 + w/2), max y = h / (h/2 + h/2)
 * (1.0, or NaN for 0).  The original also stores (float)width into its own first argument slot (not visible to C
 * callers).  Returns 1, or 0 if a call failed. */
/* OVERRIDES: D3D_CreateViewport */
undefined4 D3D_CreateViewport(uint width, uint height)
{
    uint vp[11];
    uint rect[4];
    long double w = (long double)(unsigned long long)width;
    long double h = (long double)(unsigned long long)height;
    long double half_w, half_h;
    float wf;
    int i;

    if ((**(code_std **)(*(int *)g_pDirect3D + 0x1c))(g_pDirect3D, &PTR_0080660c, 0) != 0)
        return 0;
    if ((**(code_std **)(*(int *)g_pD3dDevice + 0x24))(g_pD3dDevice, PTR_0080660c) != 0)
        return 0;
    wf = (float)w;
    half_w = w * 0.5f;
    half_h = h * 0.5f;
    for (i = 0; i < 11; i++)
        vp[i] = 0;
    ((float *)vp)[5] = (float)half_w;
    ((float *)vp)[6] = (float)half_h;
    vp[0] = 0x2c;
    vp[2] = 0;
    vp[1] = 0;
    vp[3] = width;
    vp[4] = height;
    ((float *)vp)[7] = (float)((long double)wf / (half_w + half_w));
    ((float *)vp)[8] = (float)(h / (half_h + half_h));
    if ((**(code_std **)(*PTR_0080660c + 0x14))(PTR_0080660c, vp) != 0)
        return 0;
    rect[0] = 0;
    rect[1] = 0;
    rect[2] = width;
    rect[3] = height;
    D3D_SetViewportRect(rect);
    return 1;
}


/* ==== ThingInstancer (0x00496950) ====
 * Instance data of a model component (0x194 bytes: +0x34 .., +0x38 is root, +0x3c colormap, +0x40 rdThing,
 * +0x44 / +0x48 parent instance data, +0x50 reference count).  create == 0 releases one reference (on the last one the
 * ResRef, the rdThing and the block are freed) and returns 0.  Otherwise Cos_InstComponentInfo(cosInst, idx, &tag,
 * &record, &parent) gives the component's tag, its record (the old text had the address of the parameter slot here:
 * the slot is both an argument and a result) and parent index, and returns its name.  A component of the instance's
 * user-data costume (the previous costume) with the same tag and name (_stricmp) is shared: its reference count goes
 * up and it is returned.  Else a new block: model = record[1] (assert "Bad model Reference" if record[0] is 0), ResRef,
 * rdThing with the model and a puppet, colormap = record[0x34]; the parent's instance data gives +0x44 / +0x48, no
 * parent makes it a root (+0x48 = -1). */
void * __cdecl ThingInstancer(void *cosInst, int componentIdx, int create)
{
    int tag = 0;
    char *name;
    int *record = (int *)componentIdx;
    int parent = 0;
    int user;
    int count;
    int i;
    int *inst;
    void *model;
    int *ref;
    int *thing;

    if (create == 0) {
        inst = (int *)Cos_InstGetInstanceData(cosInst, componentIdx, 0);
        inst[0x50 / 4] = inst[0x50 / 4] - 1;
        if (inst[0x50 / 4] == 0) {
            Res_RemoveReference(inst);
            rdThing_Free(inst[0x40 / 4]);
            (*g_pSputCosHS->pFree)(inst);
        }
        return 0;
    }
    name = (char *)Cos_InstComponentInfo(cosInst, componentIdx, &tag, &record, &parent);
    user = Cos_InstGetUserData(cosInst);
    if (user != 0) {
        count = Cos_InstCountComponents(user);
        for (i = 0; i < count; i++) {
            char *other = (char *)Cos_InstComponentInfo(user, i, &create, 0, 0);

            if (create == tag && _stricmp((byte *)other, (byte *)name) == 0) {
                inst = (int *)Cos_InstGetInstanceData(user, i, 0);
                inst[0x50 / 4] = inst[0x50 / 4] + 1;
                return inst;
            }
        }
    }
    if (record[0] == 0)
        (*g_pStd_HS->pAssertFail)(s_Bad_model_Reference_004e9e08, s_main_sputResource_h_004e80a8, 0xae);
    model = (void *)record[1];
    ref = (int *)(*g_pSputCosHS->pAlloc)(0x194, s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0, 0xa8d);
    for (i = 0; i < 0x65; i++)
        ref[i] = 0;
    Res_SetReference(ref, model, s_C__grimsrc_libs_grimlib_Engine_s_004ea1b0, 0xa91);
    thing = (int *)rdThing_New(0);
    rdThing_SetModel3(thing, model);
    thing[0x14 / 4] = (int)rdPuppet_New(thing);
    ref[0x40 / 4] = (int)thing;
    ref[0x3c / 4] = record[0x34 / 4];
    if (parent >= 0) {
        int *p = (int *)Cos_InstGetInstanceData(cosInst, parent, 0);

        ref[0x44 / 4] = p[0];
        ref[0x48 / 4] = p[1];
        ref[0x38 / 4] = 0;
    } else {
        ref[0x44 / 4] = 0;
        ref[0x48 / 4] = -1;
        ref[0x38 / 4] = 1;
    }
    ref[0x50 / 4] = ref[0x50 / 4] + 1;
    return ref;
}

/* ==== sputLua_Startup (0x0049de00) ====
 * Once (UINT_008cab80 set means done: returns 1): calls the hook in UINT_008cab58, reads the registry value
 * "TextAllowed" (default DAT_004f5a98) and sets lua_assume_binary unless it equals DAT_004ec554 (_stricmp), opens the
 * io / string / math libraries and the engine's function table (PTR_s_EnginePause_004ea8b0, UINT_004eb168 entries),
 * registers the userdata tag table at 0x004ea890 (4 entries) for save / restore, creates the system table, keeps a
 * reference to the old global DAT_004ec54c ("type") and replaces it by sputLua_TypeOverride, sets five number globals
 * (0, 4096, 8192 CAMERA, 16384 SPECIAL, 32768), installs the "concat" fallback (keeping a reference to the old one),
 * the save / restore userdata hooks and the shutdown hook.  Returns 0.
 * The two calls of the build's mod API (names/asm_patches.json, after 0x0049de35 and 0x0049de7c) are kept. */
void GRIM_RegisterModApiLib(void);
void GRIM_RegisterModApi(void);

undefined4 sputLua_Startup(void)
{
    char text[0x20];

    if (UINT_008cab80 != 0)
        return 1;
    (*(code *)UINT_008cab58)();
    wuRegistry_GetStr(s_TextAllowed_004ec55c, text, 0x20, (char *)&DAT_004f5a98);
    GRIM_RegisterModApiLib();    /* build patch */
    if (_stricmp((byte *)text, (byte *)&DAT_004ec554) != 0)
        *(undefined4 *)lua_assume_binary_exref = 1;
    lua_iolibopen();
    lua_strlibopen();
    lua_mathlibopen();
    sputLua_RegisterFunctions((int *)&PTR_s_EnginePause_004ea8b0, UINT_004eb168);
    GRIM_RegisterModApi();       /* build patch */
    lua_recognizelib(IMG_ADDR(0x004ea890), 4);
    g_nLrSystemTable = Lua_CreateSystemTable();
    lua_pushobject(lua_getglobal(&DAT_004ec54c));
    g_dwLrTypeFunction = lua_ref(1);
    lua_pushCclosure(sputLua_TypeOverride, 0);
    lua_setglobal(&DAT_004ec54c);
    lua_pushnumber(0.0f);
    lua_setglobal(&DAT_004ec544);
    lua_pushnumber(4096.0f);
    lua_setglobal(&DAT_004ec53c);
    lua_pushnumber(8192.0f);
    lua_setglobal(s_CAMERA_004ec534);
    lua_pushnumber(16384.0f);
    lua_setglobal(s_SPECIAL_004ec52c);
    lua_pushnumber(32768.0f);
    lua_setglobal(&DAT_004ec528);
    lua_pushobject(lua_setfallback(s_concat_004ec520, sputLua_ConcatFallback));
    g_dwLrOldConcatFallback = lua_ref(1);
    *(void **)lua_savehook_exref = (void *)sputLua_SaveIndirector;
    *(void **)lua_restorehook_exref = (void *)sputLua_RestoreIndirector;
    sputControl_AddCallback((void *)sputLua_NotifyControlHandlers);
    return 0;
}


/* ==== FUN_004761b0 (0x004761b0): DirectDrawEnumerate callback ====
 * (guid, description, driver name, context): fills display device record g_dwStdDisplay_numDevices (at most 16, 0x298
 * bytes each at 0x00902c60): name at +0, description at +0x80 (127 characters each), +0x100 = 1, +0x104 has a GUID,
 * +0x10c primary (no GUID), +0x110 = 1, GUID at +0x288.  Creates the DirectDraw object, sets the cooperative level twice
 * (SetCooperativeLevel, vtable 0x50) and reads the driver and HEL caps (GetCaps, 0x2c; two DDCAPS of 0x16c bytes):
 * +0x108 = hardware 3D (dwCaps bit 0), +0x114 / +0x118 = driver caps dwords at 0x3c / 0x40.  The first
 * SetCooperativeLevel passes 8 (DDSCL_NORMAL) instead of the original 0x11: the build's patch (names/asm_patches.json,
 * 0x00476297) is kept.  Returns 1 (DDENUMRET_OK) when DirectDrawCreate or GetCaps fail or the device was added (only
 * then the count goes up and the object is released), 0 (cancel) when there is no room or a cooperative level fails. */
undefined * __stdcall FUN_004761b0(int a1, int a2, int a3, int a4)
{
    uint n = g_dwStdDisplay_numDevices;
    byte *rec;
    void *dd = 0;
    uint caps[0x5b];
    uint hel[0x5b];
    int i;

    if (n >= 0x10)
        return 0;
    rec = &DAT_00902c60 + n * 0x298;
    *(uint *)(rec + 0x100) = 1;
    *(uint *)(rec + 0x110) = 1;
    if (a1 != 0) {
        Mem_Copy(rec + 0x288, (void *)a1, 0x10);
        *(uint *)(rec + 0x10c) = 0;
    } else {
        *(uint *)(rec + 0x288) = 0;
        *(uint *)(rec + 0x28c) = 0;
        *(uint *)(rec + 0x290) = 0;
        *(uint *)(rec + 0x294) = 0;
        *(uint *)(rec + 0x10c) = 1;
    }
    strncpy((uint *)(rec + 0x80), (uint *)a2, 0x7f);
    rec[0xff] = 0;
    strncpy((uint *)rec, (uint *)a3, 0x7f);
    rec[0x7f] = 0;
    *(uint *)(rec + 0x104) = a1 != 0;
    if (DirectDrawCreate(a1, &dd, 0) != 0)
        return (undefined *)1;
    if ((**(code_std **)(*(int *)dd + 0x50))(dd, Win_GetMainHwnd(), 8) != 0)    /* 8: build patch, was 0x11 */
        return 0;
    for (i = 0; i < 0x5b; i++)
        caps[i] = 0;
    for (i = 0; i < 0x5b; i++)
        hel[i] = 0;
    caps[0] = 0x16c;
    hel[0] = 0x16c;
    if ((**(code_std **)(*(int *)dd + 0x2c))(dd, caps, hel) != 0) {
        (**(code_std **)(*(int *)dd + 8))(dd);
        return (undefined *)1;
    }
    *(uint *)(rec + 0x108) = (caps[1] & 1) != 0;
    *(uint *)(rec + 0x114) = caps[0x3c / 4];
    *(uint *)(rec + 0x118) = caps[0x40 / 4];
    if ((**(code_std **)(*(int *)dd + 0x50))(dd, Win_GetMainHwnd(), 8) != 0)
        return 0;
    (**(code_std **)(*(int *)dd + 8))(dd);
    g_dwStdDisplay_numDevices = g_dwStdDisplay_numDevices + 1;
    return (undefined *)1;
}


/* ==== stdDisplay_TextOut (0x00474e40) ====
 * Debug text in yellow-green (0x00ffff), transparent background, with the debug font.  Display type 0 (+0x100 of the
 * display device): onto the DIB's DC UINT_007f6498, the old font selected back afterwards.  Type 1: onto the DC of the
 * back buffer (UINT_00803f9c set) or of the primary surface (IDirectDrawSurface GetDC 0x44 / ReleaseDC 0x68; the old
 * font is not restored and SetBkMode comes before SelectObject here).  Returns 1, or 0 for another type or when GetDC
 * fails. */
int __cdecl stdDisplay_TextOut(char *text, int x, int y)
{
    int type = *(int *)((byte *)g_pDisplayDevice + 0x100);
    int *surf;
    int hdc;
    int old;
    int back;
    uint len;

    if (type == 0) {
        old = SelectObject(UINT_007f6498, g_pDebugFont);
        SetBkMode(UINT_007f6498, 1);
        SetTextColor(UINT_007f6498, 0xffff);
        for (len = 0; text[len] != 0; len++)
            ;
        TextOutA(UINT_007f6498, x, y, text, len);
        SelectObject(UINT_007f6498, old);
        return 1;
    }
    if (type != 1)
        return 0;
    back = UINT_00803f9c != 0;
    surf = back ? *(int **)g_pDDrawBack : *(int **)g_pDDrawPrimary;
    if ((**(code_std **)(*surf + 0x44))(surf, &hdc) != 0)
        return 0;
    SetBkMode(hdc, 1);
    SelectObject(hdc, g_pDebugFont);
    SetTextColor(hdc, 0xffff);
    for (len = 0; text[len] != 0; len++)
        ;
    TextOutA(hdc, x, y, text, len);
    surf = back ? *(int **)g_pDDrawBack : *(int **)g_pDDrawPrimary;
    (**(code_std **)(*surf + 0x68))(surf, hdc);
    return 1;
}


/* ==== D3D_InitRenderState (0x00479db0) ====
 * Creates a 4 KB execute buffer (IDirect3DDevice::CreateExecuteBuffer 0x18, D3DEXECUTEBUFFERDESC with D3DDEB_BUFSIZE),
 * locks it (0x10), clears it and writes one D3DOP_STATERENDER instruction (opcode 8, size 8, 25 states) with the initial
 * render states, chosen from g_dwD3dRenderFlags, the driver (+0x14), UINT_004dee60 and the texture filter
 * (D3D_FilterBitsToEnum(UINT_00900534)), then D3DOP_EXIT.  Unlocks it (0x14), sets the execute data (0x18; instruction
 * offset 0, length), and executes it unclipped inside BeginScene / EndScene (0x4c, 0x20, 0x50), releases the buffer,
 * remembers the flags in UINT_00806924 and returns 1.  The results of the COM calls are not checked. */
undefined4 D3D_InitRenderState(void)
{
    int *eb = 0;
    uint desc[5];
    uint exec[12];
    byte *start;
    uint *p;
    int i;

    desc[0] = 0x14;
    desc[1] = 1;
    desc[2] = 0;
    desc[3] = 0x1000;
    desc[4] = 0;
    (**(code_std **)(*(int *)g_pD3dDevice + 0x18))(g_pD3dDevice, desc, &eb, 0);
    (**(code_std **)(*eb + 0x10))(eb, desc);
    start = (byte *)desc[4];
    for (i = 0; i < 0x400; i++)
        ((uint *)start)[i] = 0;
    start[0] = 8;
    start[1] = 8;
    *(ushort *)(start + 2) = 0x19;
    p = (uint *)(start + 4);
#define RS(state, value) (p[0] = (state), p[1] = (value), p += 2)
    RS(4, g_dwD3dRenderFlags & 1);
    RS(0x11, (g_dwD3dRenderFlags & 0x80) != 0 ? 2 : 1);
    RS(0x12, (g_dwD3dRenderFlags & 0x100) != 0 ? 2 : 1);
    RS(0x1f, g_dwD3dRenderFlags >> 4 & 1);
    RS(0x20, g_dwD3dRenderFlags >> 5 & 1);
    RS(5, 0);
    RS(6, 0);
    RS(0x1b, (g_dwD3dRenderFlags & 0x600) != 0);
    if ((g_dwD3dRenderFlags & 0x600) != 0) {
        RS(0x15, (g_dwD3dRenderFlags & 0x400) != 0 ? 4 : 2);
        RS(0x13, 5);
        RS(0x14, 6);
    } else {
        RS(0x15, 2);
        RS(0x13, 2);
        RS(0x14, 1);
    }
    RS(0xf, 1);
    RS(0x19, D3D_FilterBitsToEnum(UINT_00900534));
    RS(0x21, *(int *)((byte *)g_pStd3D_CurDevice + 0x14) != 0);
    RS(9, 2);
    RS(0xb, ~g_dwD3dRenderFlags >> 0xf & 1);
    RS(0x1d, g_dwD3dRenderFlags >> 2 & 1);
    RS(0x1c, g_dwD3dRenderFlags >> 6 & 1);
    RS(8, 3);
    RS(0x1a, g_dwD3dRenderFlags >> 1 & 1);
    RS(2, g_dwD3dRenderFlags >> 3 & 1);
    RS(7, UINT_004dee60 != 0);
    RS(0xe, UINT_004dee60 != 0);
    RS(0x17, D3D_FilterBitsToEnum(UINT_00900534));
    RS(0x16, 1);
#undef RS
    ((byte *)p)[0] = 0xb;     /* D3DOP_EXIT */
    ((byte *)p)[1] = 0;
    *(ushort *)((byte *)p + 2) = 0;
    p = (uint *)((byte *)p + 4);
    (**(code_std **)(*eb + 0x14))(eb);
    for (i = 0; i < 12; i++)
        exec[i] = 0;
    exec[0] = 0x30;
    exec[3] = 0;
    exec[4] = (byte *)p - start;
    (**(code_std **)(*eb + 0x18))(eb, exec);
    (**(code_std **)(*(int *)g_pD3dDevice + 0x4c))(g_pD3dDevice);
    (**(code_std **)(*(int *)g_pD3dDevice + 0x20))(g_pD3dDevice, eb, PTR_0080660c, 2);
    (**(code_std **)(*(int *)g_pD3dDevice + 0x50))(g_pD3dDevice);
    (**(code_std **)(*eb + 8))(eb);
    UINT_00806924 = g_dwD3dRenderFlags;
    return 1;
}


/* ==== DDraw_CreateSurfaces (0x004767d0) ====
 * (hwnd, video mode record, palette of 256 RGB triples); Ghidra lost the third parameter.  Sets the cooperative level
 * (0x11 exclusive + fullscreen, 0x51 with DDSCL_ALLOWMODEX when a back buffer is wanted (UINT_00803f9c) and mode[0] is
 * set; kept in UINT_00803fb0) and the display mode (SetDisplayMode 0x54: width mode[2], height mode[3], bpp mode[8]).
 * The primary surface record g_dwStdDisplay_frontBuffer (0x00901680, 0xd8 bytes: +0 1, +4 0, +8 in video memory, +0xc copy of
 * mode[2..20], +0x18 pitch, +0x1c pitch in pixels, +0x58 palette, +0x5c 0, +0x64 surface, +0x68 DirectDraw palette,
 * +0x6c DDSURFACEDESC) is created (CreateSurface 0x18: primary, flipping with one back buffer for 3D, else plain
 * primary) and described (GetSurfaceDesc 0x58); g_dwStdDisplay_numDrawBuffers = back buffer count + 1.  With a back buffer the
 * attached surface (GetAttachedSurface 0x30) gets the record g_dwStdDisplay_backBuffer (0x009055e0) the same way.  For a paletted
 * mode (mode[7] == 0) the 256 palette entries (flag PC_RESERVED) start from the system palette (GetDC /
 * GetSystemPaletteEntries / ReleaseDC) and take the given colours; the DirectDraw palette (CreatePalette 0x14, caps
 * 0x4c) is set on the surfaces (SetPalette 0x7c).  Without a back buffer the primary record is copied to g_dwStdDisplay_backBuffer.
 * Returns 1, or 0 when a DirectDraw call fails. */
/* OVERRIDES: DDraw_CreateSurfaces */
undefined4 DDraw_CreateSurfaces(undefined4 hwnd, int *mode, byte *palette)
{
    byte entries[0x400];
    uint flags = 0x11;
    uint bpp;
    int *dd;
    int *prim;
    int *back;
    int hdc;
    int i;
    byte *src;

    if (UINT_00803f9c != 0 && mode[0] != 0)
        flags = 0x51;
    dd = (int *)g_pDirectDraw;
    if ((**(code_std **)(*dd + 0x50))(dd, hwnd, flags) != 0)
        return 0;
    UINT_00803fb0 = flags;
    dd = (int *)g_pDirectDraw;
    if ((**(code_std **)(*dd + 0x54))(dd, mode[2], mode[3], mode[8]) != 0)
        return 0;
    bpp = (uint)mode[8] >> 3;
    g_dwStdDisplay_frontBuffer = 1;
    _DAT_00901684 = 0;
    _DAT_00901688 = 0;
    Mem_Copy(&DAT_0090168c, mode + 2, 0x4c);
    _DAT_009016d8 = palette;
    UINT_009016dc = 0;
    g_pDDrawPrimary = &UINT_009016e4;
    for (i = 0; i < 0x1b; i++)
        (&UINT_009016ec)[i] = 0;
    prim = (int *)g_pDDrawPrimary;
    prim[0x14 / 4] = mode[2];
    prim[0x10 / 4] = mode[3];
    prim[0x8 / 4] = 0x6c;
    prim[0x4 / 4] = 0;
    if (UINT_00803f9c != 0) {
        prim[0x1c / 4] = 1;
        prim[0xc / 4] = 0x21;
        prim[0x70 / 4] = 0x2218;
    } else {
        prim[0xc / 4] = 1;
        prim[0x70 / 4] = 0x2200;
    }
    dd = (int *)g_pDirectDraw;
    if ((**(code_std **)(*dd + 0x18))(dd, prim + 2, prim, 0) != 0)
        return 0;
    prim = (int *)g_pDDrawPrimary;
    if ((**(code_std **)(*(int *)prim[0] + 0x58))(prim[0], prim + 2) != 0)
        return 0;
    prim = (int *)g_pDDrawPrimary;
    g_dwStdDisplay_numDrawBuffers = prim[0x1c / 4] + 1;
    UINT_00901698 = prim[0x18 / 4];
    _DAT_0090169c = (uint)prim[0x18 / 4] / bpp;
    if ((prim[0x70 / 4] & 0x4000) != 0)
        _DAT_00901688 = 1;
    if (UINT_00803f9c != 0) {
        g_dwStdDisplay_backBuffer = 1;
        _DAT_009055e4 = 0;
        _DAT_009055e8 = 0;
        Mem_Copy(&UINT_009055ec, mode + 2, 0x4c);
        _DAT_00905638 = palette;
        UINT_0090563c = 0;
        g_pDDrawBack = &PTR_00905644;
        for (i = 0; i < 0x1b; i++)
            (&UINT_0090564c)[i] = 0;
        back = (int *)g_pDDrawBack;
        back[0x14 / 4] = mode[2];
        back[0x10 / 4] = mode[3];
        back[0x8 / 4] = 0x6c;
        back[0xc / 4] = 0x21;
        back[0x70 / 4] = 4;
        back[0x1c / 4] = 1;
        prim = *(int **)g_pDDrawPrimary;
        if ((**(code_std **)(*prim + 0x30))(prim, back + 0x70 / 4, back) != 0)
            return 0;
        back = (int *)g_pDDrawBack;
        if ((**(code_std **)(*(int *)back[0] + 0x58))(back[0], back + 2) != 0)
            return 0;
        back = (int *)g_pDDrawBack;
        if ((back[0x70 / 4] & 0x4000) != 0)
            _DAT_009055e8 = 1;
        UINT_009055f8 = back[0x18 / 4];
        _DAT_009055fc = (uint)back[0x18 / 4] / bpp;
        back[0x4 / 4] = 0;
    }
    if (mode[7] == 0) {
        hdc = GetDC(0);
        GetSystemPaletteEntries(hdc, 0, 0x100, entries);
        ReleaseDC(0, hdc);
        src = palette;
        for (i = 0; i < 0x100; i++) {
            entries[i * 4 + 3] = 1;
            entries[i * 4 + 0] = *src++;
            entries[i * 4 + 1] = *src++;
            entries[i * 4 + 2] = *src++;
        }
        dd = (int *)g_pDirectDraw;
        prim = (int *)g_pDDrawPrimary;
        if ((**(code_std **)(*dd + 0x14))(dd, 0x4c, entries, prim + 1, 0) != 0)
            return 0;
        prim = (int *)g_pDDrawPrimary;
        if ((**(code_std **)(*(int *)prim[0] + 0x7c))(prim[0], prim[1]) != 0)
            return 0;
        if (UINT_00803f9c == 0) {
            Mem_Copy(&g_dwStdDisplay_backBuffer, &g_dwStdDisplay_frontBuffer, 0xd8);
            return 1;
        }
        back = *(int **)g_pDDrawBack;
        if ((**(code_std **)(*back + 0x7c))(back, ((int *)g_pDDrawPrimary)[1]) != 0)
            return 0;
    }
    if (UINT_00803f9c == 0)
        Mem_Copy(&g_dwStdDisplay_backBuffer, &g_dwStdDisplay_frontBuffer, 0xd8);
    return 1;
}


/* ==== WalkPlane_Within (0x004a6980) ====
 * __thiscall (sector, point, checkActive).  With checkActive the sector must be visible (+0x2c) and active (+0x28).
 * The point must be within the sector's height tolerance (+0x30) of its plane (normal +0x60, first vertex record
 * +0x3c, coordinates at +4) and on the inner side of every edge in the projection on the axes +0x7c / +0x80 (vertex
 * records at +0x38, +0x34 of them).  All arithmetic is x87 extended precision as in the original: the distance and
 * each edge cross product (+1e-5) are snapped to 0 when their magnitude is at most 1e-5 or NaN (FCOM + TEST AH,0x41
 * treats unordered as "below"), which is why this is written with long double and the inverted `!(a > eps)` tests;
 * an earlier C version with plain float comparisons differed from the original (docs/notes/logic.md). */
static long double sector_snap(long double x)
{
    long double a = x < 0 ? -x : x;

    if (!(a > (long double)1e-5f))
        return 0;
    return x;
}

int __thiscall WalkPlane_Within(WalkPlane *this, float *point, int checkActive)
{
    byte *sec = (byte *)this;
    float *v;
    float *prev;
    float *cur;
    long double d;
    int count;
    int a, b;
    int i;

    if (checkActive != 0) {
        if (*(int *)(sec + 0x2c) == 0 || *(int *)(sec + 0x28) == 0)
            return 0;
    }
    v = *(float **)(sec + 0x3c);
    d = ((long double)point[0] - v[1]) * *(float *)(sec + 0x60) + ((long double)point[2] - v[3]) * *(float *)(sec + 0x68);
    d = d + ((long double)point[1] - v[2]) * *(float *)(sec + 0x64);
    d = sector_snap(d);
    if (d < 0)
        d = -d;
    if (d > *(float *)(sec + 0x30))
        return 0;
    count = *(int *)(sec + 0x34);
    if (count <= 0)
        return 1;
    prev = (float *)(((int *)(sec + 0x38))[count - 1] + 4);
    a = *(int *)(sec + 0x7c);
    b = *(int *)(sec + 0x80);
    for (i = 0; i < count; i++) {
        long double ea, eb, pa, pb, c;

        cur = (float *)(((int *)(sec + 0x38))[i] + 4);
        ea = (long double)cur[a] - prev[a];
        pb = (long double)point[b] - prev[b];
        eb = (long double)cur[b] - prev[b];
        pa = (long double)point[a] - prev[a];
        c = -ea * pb + pa * eb;
        c = c - (long double)-1e-5f;
        if (sector_snap(c) < 0)
            return 0;
        prev = cur;
    }
    return 1;
}


/* ==== rdRaster_Span16_TexLitZw_15 .. _22, _24 .. _30 (0x00466920 .. 0x00467e30, 0x0046c330 .. 0x0046d540) ====
 * One textured, z-buffered (16 bit z, written where the new z is greater), unlit span of the software rasteriser into
 * a 16 bit surface, affine texture mapping with an 8 bit texture through a 16 bit palette.  The edges `left` / `right`
 * are rasteriser vertices: +0 x (16.16), +0x10 z (float), +0x28 u, +0x30 v (16.16, scaled down by the shift
 * 0x008dde54), +0x40 y.  The span covers ceil(left x) .. ceil(right x) - 1; the steps use the reciprocal tables at
 * 0x008fbfc0 (16.16) and 0x008fe000 (float), the z start and step are rounded with the control word at 0x00900526
 * (restored from 0x00900524).  The pixels are drawn from right to left; the state of the span (0x007f4ca4 ..
 * 0x007f4cfc: z buffer and destination pointers, u, v, z and their steps, count) is left one pixel past the end, as
 * the next span routine expects.  The functions differ only in the texture width: 4 (_16), 8 (_17, _25), 16 (_18,
 * _26) ... 256 (_22, _30), or the width in 0x008dde8c / u mask in 0x008dde48 (_15, _24, whose loop keeps u / v / z in
 * memory and gives the same results); _25 .. _30 are copies of _17 .. _22. */
/* the globals of the original's .data by address (constants: no img_addr_ call, which -O2 code cannot inline) */
#define SPAN_DATA(a) ((void *)(sect_data + ((a) - 0x004dd000u)))
#define RG32(a) (*(int *)SPAN_DATA(a))
#define RGU32(a) (*(uint *)SPAN_DATA(a))
#define RG16(a) (*(ushort *)SPAN_DATA(a))

/* These spans are what the game's opaque textured drivers call per scan line (Draw_FlatLit_7 .. 9 of
 * build/overrides_asm_q4.c with the z shift 0), so they are compiled at -O2 (build/link.py compiles override files at
 * -O0; agent q6 measured the gain, docs/notes/asm_q6.md).  At -O2 gcc keeps x87 values in registers, so every FSTP m32
 * of the original is a store through a volatile float (span_f), the float the z start reads after the first conversion
 * is a volatile (its arithmetic cannot move before that conversion's control-word loads), and span_fist clobbers
 * memory.  The differential test build/difftest/asm_q6/o2span.sh compiles this file as build/link.py does. */
#pragma GCC push_options
#pragma GCC optimize("O2", "no-strict-aliasing", "no-omit-frame-pointer")

static inline __attribute__((always_inline)) float span_f(long double x)
{
    volatile float f = (float)x;
    return f;
}

static inline __attribute__((always_inline)) int span_fist(float x)
{
    int r;

    __asm__ volatile("fldcw %2\n\tfistpl %0\n\tfldcw %3"
                     : "=m"(r)
                     : "t"(x), "m"(RG16(0x00900526)), "m"(RG16(0x00900524))
                     : "st", "memory");
    return r;
}

static inline __attribute__((always_inline)) int span_mul16(int a, int b)    /* imul + shrd 16: bits 16..47 of the 64 bit product */
{
    return (int)((long long)a * b >> 16);
}

static void span16_tex_zw(int *left, int *right, int vshift, int umask)
{
    int x0, xr, count, frac, recip, t, n1;
    int shift;
    int u, v, z, du, dv, dz;
    volatile float dzf;
    float f;
    int *canvas;
    int *surf;
    ushort *zbuf;
    ushort *dest;
    byte *tex;
    ushort *pal;
    int i;

    x0 = left[0];
    if ((x0 & 0xffff) != 0)
        x0 = (x0 + 0x10000) & 0xffff0000;
    xr = right[0];
    if ((xr & 0xffff) != 0)
        xr = (xr + 0x10000) & 0xffff0000;
    count = (int)((uint)xr >> 16) - (x0 >> 16);
    RG32(0x007f4cac) = count;
    if (count <= 0)
        return;
    frac = x0 - left[0];
    x0 >>= 16;
    recip = ((int *)SPAN_DATA(0x008fbfc0))[count];
    shift = RG32(0x008dde54) & 0x1f;
    t = span_mul16(right[0x28 / 4] - left[0x28 / 4], recip);
    RG32(0x007f4cdc) = t >> shift;
    RG32(0x007f4cf4) = (span_mul16(frac, t) + left[0x28 / 4]) >> (RG32(0x008dde54) & 0x1f);
    t = span_mul16(right[0x30 / 4] - left[0x30 / 4], recip);
    RG32(0x007f4c44) = t >> (RG32(0x008dde54) & 0x1f);
    RG32(0x007f4cf8) = (span_mul16(frac, t) + left[0x30 / 4]) >> (RG32(0x008dde54) & 0x1f);
    {
        long double d = ((long double)*(float *)&right[0x10 / 4] - *(float *)&left[0x10 / 4]) *
                        ((float *)SPAN_DATA(0x008fe000))[RG32(0x007f4cac)];

        dzf = (float)d;
        f = span_f(d * 65536.0f);
    }
    RG32(0x007f4c54) = span_fist(f);
    f = span_f(((long double)frac * 1.52587890625e-05f * dzf + *(float *)&left[0x10 / 4]) * 65536.0f);
    z = span_fist(f);
    u = RG32(0x007f4cf4) + RG32(0x008dde78);
    v = RG32(0x007f4cf8) + RG32(0x008dde50);
    RG32(0x007f4cfc) = z;
    RG32(0x007f4cf4) = u;
    RG32(0x007f4cf8) = v;
    canvas = *(int **)SPAN_DATA(0x007f0fc8);
    surf = *(int **)(canvas[1] + 4);
    RG32(0x007f4cc4) = surf[0x5c / 4] + (((uint)surf[0x18 / 4] >> 1) * left[0x40 / 4] + x0) * 2;
    surf = *(int **)(canvas[1] + 0x10);
    RG32(0x007f4ca4) = surf[0x18 / 4] * left[0x40 / 4] + x0 * 2 + surf[0x5c / 4];
    RG32(0x007f4cb0) = RG32(0x007f4cac);
    n1 = RG32(0x007f4cac) - 1;
    RG32(0x007f4cfc) = RG32(0x007f4c54) * n1 + z;
    RG32(0x007f4cf4) = RG32(0x007f4cdc) * n1 + u;
    RG32(0x007f4cf8) = RG32(0x007f4c44) * n1 + v;
    /* the loop, from the right end */
    u = RG32(0x007f4cf4);
    v = RG32(0x007f4cf8);
    z = RG32(0x007f4cfc);
    du = RG32(0x007f4cdc);
    dv = RG32(0x007f4c44);
    dz = RG32(0x007f4c54);
    zbuf = (ushort *)RG32(0x007f4ca4);
    dest = (ushort *)RG32(0x007f4cc4);
    tex = (byte *)RG32(0x008dde7c);
    pal = (ushort *)RG32(0x008dde5c);
    for (i = RG32(0x007f4cb0) - 1; i >= 0; i--) {
        if ((ushort)z > zbuf[i]) {
            zbuf[i] = (ushort)z;
            dest[i] = pal[tex[((v >> vshift) & RG32(0x008dde58)) | ((u & umask) >> 16)]];
        }
        v -= dv;
        z -= dz;
        u -= du;
    }
    RG32(0x007f4cfc) = RG32(0x007f4cfc) + RG32(0x007f4c54);
    RG32(0x007f4cf4) = RG32(0x007f4cf4) + RG32(0x007f4cdc);
    RG32(0x007f4cf8) = RG32(0x007f4cf8) + RG32(0x007f4c44);
    RG32(0x007f4cc4) = RG32(0x007f4cc4) + RG32(0x007f4cb0) * 2;
    RG32(0x007f4ca4) = RG32(0x007f4ca4) + RG32(0x007f4cb0) * 2;
}

void rdRaster_Span16_TexLitZw_15(uint *left, uint *right)
{
    span16_tex_zw((int *)left, (int *)right, (0x10 - RG32(0x008dde8c)) & 0x1f, RG32(0x008dde48));
}
void rdRaster_Span16_TexLitZw_16(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0xe, 0x30000); }
void rdRaster_Span16_TexLitZw_17(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0xd, 0x70000); }
void rdRaster_Span16_TexLitZw_18(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0xc, 0xf0000); }
void rdRaster_Span16_TexLitZw_19(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0xb, 0x1f0000); }
void rdRaster_Span16_TexLitZw_20(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0xa, 0x3f0000); }
void rdRaster_Span16_TexLitZw_21(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0x9, 0x7f0000); }
void rdRaster_Span16_TexLitZw_22(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0x8, 0xff0000); }
void rdRaster_Span16_TexLitZw_24(uint *left, uint *right)
{
    span16_tex_zw((int *)left, (int *)right, (0x10 - RG32(0x008dde8c)) & 0x1f, RG32(0x008dde48));
}
void rdRaster_Span16_TexLitZw_25(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0xd, 0x70000); }
void rdRaster_Span16_TexLitZw_26(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0xc, 0xf0000); }
void rdRaster_Span16_TexLitZw_27(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0xb, 0x1f0000); }
void rdRaster_Span16_TexLitZw_28(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0xa, 0x3f0000); }
void rdRaster_Span16_TexLitZw_29(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0x9, 0x7f0000); }
void rdRaster_Span16_TexLitZw_30(uint *left, uint *right) { span16_tex_zw((int *)left, (int *)right, 0x8, 0xff0000); }


/* ==== rdRaster_Span16_TexLitZw, _2 .. _8 (0x0045ff10 .. 0x004618e0) ====
 * As span16_tex_zw above, lit: the edges also carry a light value at +0x38 (16.16); its step (0x007f4cb4) is set to 0
 * when it is slightly negative (-0x51e < step < 0) and the light (0x007f4cf0) selects the palette row (texel +
 * light >> 8; the fixed width versions mask the light with 0x3f0000 first).  The z start is computed from the float
 * (frac / 65536) instead of the extended product (the same value: frac < 2^16).  TexLitZw reads the texture width and
 * u mask from 0x008dde8c / 0x008dde48, _2 .. _8 have the widths 4 .. 256 built in. */
static void span16_texlit_zw(int *left, int *right, int vshift, int umask, int lmask)
{
    int x0, xr, count, frac, recip, t, n1;
    int u, v, z, l, du, dv, dz, dl;
    volatile float dzf;
    float fracf, f;
    int *canvas;
    int *surf;
    ushort *zbuf;
    ushort *dest;
    byte *tex;
    ushort *pal;
    int i;

    x0 = left[0];
    if ((x0 & 0xffff) != 0)
        x0 = (x0 + 0x10000) & 0xffff0000;
    xr = right[0];
    if ((xr & 0xffff) != 0)
        xr = (xr + 0x10000) & 0xffff0000;
    count = (int)((uint)xr >> 16) - (x0 >> 16);
    RG32(0x007f4cac) = count;
    if (count <= 0)
        return;
    frac = x0 - left[0];
    x0 >>= 16;
    recip = ((int *)SPAN_DATA(0x008fbfc0))[count];
    fracf = span_f((long double)frac * 1.52587890625e-05f);
    t = span_mul16(right[0x28 / 4] - left[0x28 / 4], recip);
    RG32(0x007f4cdc) = t >> (RG32(0x008dde54) & 0x1f);
    RG32(0x007f4cf4) = (span_mul16(frac, t) + left[0x28 / 4]) >> (RG32(0x008dde54) & 0x1f);
    t = span_mul16(right[0x30 / 4] - left[0x30 / 4], recip);
    RG32(0x007f4c44) = t >> (RG32(0x008dde54) & 0x1f);
    RG32(0x007f4cf8) = (span_mul16(frac, t) + left[0x30 / 4]) >> (RG32(0x008dde54) & 0x1f);
    RG32(0x007f4cb4) = span_mul16(right[0x38 / 4] - left[0x38 / 4], recip);
    if (RG32(0x007f4cb4) < 0 && RG32(0x007f4cb4) > -0x51e)
        RG32(0x007f4cb4) = 0;
    RG32(0x007f4cf0) = span_mul16(frac, RG32(0x007f4cb4)) + left[0x38 / 4];
    {
        long double d = ((long double)*(float *)&right[0x10 / 4] - *(float *)&left[0x10 / 4]) *
                        ((float *)SPAN_DATA(0x008fe000))[RG32(0x007f4cac)];

        dzf = (float)d;
        f = span_f(d * 65536.0f);
    }
    RG32(0x007f4c54) = span_fist(f);
    f = span_f(((long double)dzf * fracf + *(float *)&left[0x10 / 4]) * 65536.0f);
    z = span_fist(f);
    u = RG32(0x007f4cf4) + RG32(0x008dde78);
    v = RG32(0x007f4cf8) + RG32(0x008dde50);
    RG32(0x007f4cfc) = z;
    RG32(0x007f4cf4) = u;
    RG32(0x007f4cf8) = v;
    canvas = *(int **)SPAN_DATA(0x007f0fc8);
    surf = *(int **)(canvas[1] + 4);
    RG32(0x007f4cc4) = surf[0x5c / 4] + (((uint)surf[0x18 / 4] >> 1) * left[0x40 / 4] + x0) * 2;
    surf = *(int **)(canvas[1] + 0x10);
    RG32(0x007f4ca4) = surf[0x18 / 4] * left[0x40 / 4] + x0 * 2 + surf[0x5c / 4];
    RG32(0x007f4cb0) = RG32(0x007f4cac);
    n1 = RG32(0x007f4cac) - 1;
    RG32(0x007f4cfc) = RG32(0x007f4c54) * n1 + z;
    RG32(0x007f4cf4) = RG32(0x007f4cdc) * n1 + u;
    RG32(0x007f4cf8) = RG32(0x007f4c44) * n1 + v;
    RG32(0x007f4cf0) = RG32(0x007f4cb4) * n1 + RG32(0x007f4cf0);
    /* the loop, from the right end */
    u = RG32(0x007f4cf4);
    v = RG32(0x007f4cf8);
    z = RG32(0x007f4cfc);
    l = RG32(0x007f4cf0);
    du = RG32(0x007f4cdc);
    dv = RG32(0x007f4c44);
    dz = RG32(0x007f4c54);
    dl = RG32(0x007f4cb4);
    zbuf = (ushort *)RG32(0x007f4ca4);
    dest = (ushort *)RG32(0x007f4cc4);
    tex = (byte *)RG32(0x008dde7c);
    pal = (ushort *)RG32(0x008dde5c);
    for (i = RG32(0x007f4cb0) - 1; i >= 0; i--) {
        if ((ushort)z > zbuf[i]) {
            zbuf[i] = (ushort)z;
            dest[i] = pal[tex[((v >> vshift) & RG32(0x008dde58)) | ((u & umask) >> 16)] + ((l & lmask) >> 8)];
        }
        v -= dv;
        z -= dz;
        u -= du;
        l -= dl;
    }
    RG32(0x007f4cfc) = RG32(0x007f4cfc) + RG32(0x007f4c54);
    RG32(0x007f4cf4) = RG32(0x007f4cf4) + RG32(0x007f4cdc);
    RG32(0x007f4cf8) = RG32(0x007f4cf8) + RG32(0x007f4c44);
    RG32(0x007f4cf0) = l + RG32(0x007f4cb4) * (RG32(0x007f4cb0) + 1);
    RG32(0x007f4cc4) = RG32(0x007f4cc4) + RG32(0x007f4cb0) * 2;
    RG32(0x007f4ca4) = RG32(0x007f4ca4) + RG32(0x007f4cb0) * 2;
}

void rdRaster_Span16_TexLitZw(uint *left, uint *right)
{
    span16_texlit_zw((int *)left, (int *)right, (0x10 - RG32(0x008dde8c)) & 0x1f, RG32(0x008dde48), -1);
}
void rdRaster_Span16_TexLitZw_2(uint *left, uint *right) { span16_texlit_zw((int *)left, (int *)right, 0xe, 0x30000, 0x3f0000); }
void rdRaster_Span16_TexLitZw_3(uint *left, uint *right) { span16_texlit_zw((int *)left, (int *)right, 0xd, 0x70000, 0x3f0000); }
void rdRaster_Span16_TexLitZw_4(uint *left, uint *right) { span16_texlit_zw((int *)left, (int *)right, 0xc, 0xf0000, 0x3f0000); }
void rdRaster_Span16_TexLitZw_5(uint *left, uint *right) { span16_texlit_zw((int *)left, (int *)right, 0xb, 0x1f0000, 0x3f0000); }
void rdRaster_Span16_TexLitZw_6(uint *left, uint *right) { span16_texlit_zw((int *)left, (int *)right, 0xa, 0x3f0000, 0x3f0000); }
void rdRaster_Span16_TexLitZw_7(uint *left, uint *right) { span16_texlit_zw((int *)left, (int *)right, 0x9, 0x7f0000, 0x3f0000); }
void rdRaster_Span16_TexLitZw_8(uint *left, uint *right) { span16_texlit_zw((int *)left, (int *)right, 0x8, 0xff0000, 0x3f0000); }

#pragma GCC pop_options

#endif /* GRIM_EXE */
