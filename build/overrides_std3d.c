/* Direct3D start-up functions whose decompilation lost their COM calls' arguments (tools/audit_call_args.py: the
 * pushes before `CALL dword ptr [ECX + n]` became stack locals and the calls were printed without arguments), written
 * out from the machine code. Reached only with the Direct3D renderer (GRIM_3D=1, Display_InitFromConfig).
 * tools/build_src.py puts the decompiled text of every function defined here under `#if 0`. */
#include "ghidra_types.h"

#ifdef GRIM_EXE
#include "globals.h"
#include "functions.h"

#define COMX(obj, off, ...) ((int (__stdcall *)())(*(void ***)(obj))[(off) / 4])((obj), ##__VA_ARGS__)

/* ==== D3D_SelectDriver (0x004782e0) ====
 * Makes driver `driverIdx` of D3D_Enumerate's table (g_aStd3DDevices, 0x22c bytes each) the current device: a z-buffer
 * when wanted and the driver has one and the render flags allow it (its fill depth 16 or 2, UINT_00900534), the
 * Direct3D device from the back buffer surface (QueryInterface with the driver GUID), its texture formats
 * (EnumTextureFormats into g_abD3D_TextureFormats, 0xa4 bytes each, UINT_00806930 of them), the viewport, the render state, an
 * execute buffer (D3DEXECUTEBUFFERDESC at DAT_008063f0: the driver's size, else 0x10000), the vertex limit (the
 * driver's, at most 0x200), the texture size limits, and the texture formats the renderer uses: the display's own
 * (UINT_00806934), and with paletted textures the 5:5:5 one with 1-bit alpha (UINT_00806938) and, unless the driver
 * forbids it, the 4:4:4:4 one (UINT_0080693c, with a 32 x 32 scratch buffer UINT_00806950). Last the texture memory
 * (D3D_SetVertexLimit). Returns 1, or 0 when a step fails or a device is already selected.
 * The format requests are ColorFormat records on the stack; the original sets only the fields D3D_FindTextureFormat
 * compares and leaves the rest of the record as the stack had it; here the rest is zero. */
int __cdecl D3D_SelectDriver(uint driverIdx, int useZBuffer)
{
    Std3DDevice *dev;
    uint want[14];
    VBufferFormat scratch;
    uint size;

    if (UINT_00806970 != 0 || driverIdx >= g_dwD3dDriverCount)
        return 0;
    UINT_00900530 = driverIdx;
    dev = (Std3DDevice *)((byte *)&g_aStd3DDevices + driverIdx * 0x22c);
    g_pStd3D_CurDevice = dev;
    if (useZBuffer != 0 && dev->nHasZBuffer != 0 && (g_dwD3dRenderFlags & 0x1800) != 0) {
        UINT_004dee60 = 1;
        if (D3D_CreateZBuffer(g_pVideoMode->format.nWidth, g_pVideoMode->format.nHeight) == 0)
            return 0;
        UINT_00900534 = (dev->dwCaps & 0x10) != 0 ? 0x10 : 2;
    } else {
        UINT_004dee60 = 0;
    }
    if (COMX(PTR_00905644, 0, dev->aGuid, &g_pD3dDevice) != 0)      /* the back buffer's QueryInterface */
        return 0;
    UINT_00806930 = 0;
    if (COMX(g_pD3dDevice, 0x38, D3D_EnumTextureFormatsCallback, 0) != 0)
        return 0;
    if (UINT_00806930 == 0)
        return 0;
    if (D3D_CreateViewport(g_pVideoMode->format.nWidth, g_pVideoMode->format.nHeight) == 0)
        return 0;
    if (D3D_InitRenderState() == 0)
        return 0;
    size = dev->dwMaxBufferSize != 0 ? dev->dwMaxBufferSize : 0x10000;
    _DAT_00806958 = size;
    _DAT_008063f0 = 0x14;                                              /* dwSize */
    _DAT_008063f4 = 1;                                                 /* D3DDEB_BUFSIZE */
    _DAT_008063f8 = 0;
    _DAT_008063fc = size;
    UINT_00806400 = 0;
    g_dwStd3D_maxVertices = (dev->dwMaxVertexCount == 0 || dev->dwMaxVertexCount >= 0x200) ? 0x200
                                                                                          : dev->dwMaxVertexCount;
    COMX(g_pD3dDevice, 0x18, &DAT_008063f0, &g_pD3dExecuteBuffer, 0);  /* CreateExecuteBuffer */
    UINT_004dee58 = 1;
    UINT_00806944 = 0;
    D3D_SetTextureLimits(dev->nMinTexWidth, dev->nMinTexHeight, dev->nMaxTexWidth, dev->nMaxTexHeight);
    g_pD3dTextureList = (Std3DTexture *)0;
    PTR_0080694c = (Std3DTexture *)0;
    _DAT_00900568 = D3D_FindTextureFormat(&g_pVideoMode->format.colorFormat.nColorMode, (int)g_abD3D_TextureFormats,
                                          UINT_00806930);
    UINT_00806934 = (uint)(g_abD3D_TextureFormats + _DAT_00900568 * 0xa4);
    if (dev->nPalettedTextures != 0) {
        memset(want, 0, sizeof want);
        want[0] = 2;
        want[1] = 0x10;
        want[2] = want[3] = want[4] = 5;
        want[11] = 1;
        _DAT_009014d8 = D3D_FindTextureFormat((int *)want, (int)g_abD3D_TextureFormats, UINT_00806930);
        UINT_00806938 = (uint)(g_abD3D_TextureFormats + _DAT_009014d8 * 0xa4);
        if (dev->nUnknown18 == 0) {
            memset(want, 0, sizeof want);
            want[0] = 2;
            want[1] = 0x10;
            want[2] = want[3] = want[4] = 4;
            want[11] = 4;
            _DAT_0090052c = D3D_FindTextureFormat((int *)want, (int)g_abD3D_TextureFormats, UINT_00806930);
            UINT_0080693c = (uint)(g_abD3D_TextureFormats + _DAT_0090052c * 0xa4);
            memset(&scratch, 0, sizeof scratch);
            scratch.nWidth = 0x20;
            scratch.nHeight = 0x20;
            Mem_Copy(&scratch.colorFormat, (void *)UINT_0080693c, 0x38);
            UINT_00806950 = (uint)stdDisplay_VBufferNew(&scratch, 1, 0, 0);
        }
    }
    D3D_SetVertexLimit(&dev->dwTextureMemTotal, &dev->nTextureMemFree);
    UINT_00806970 = 1;
    return 1;
}

/* ==== D3D_SetVertexLimit (0x00479a00) ====
 * The texture memory of the display: IDirectDraw2 (QueryInterface of the DirectDraw object, IID at 0x004d8460),
 * GetAvailableVidMem(DDSCAPS_TEXTURE) into *total and *free. Returns 1, or 0 when either call fails. */
uint __cdecl D3D_SetVertexLimit(uint *total, int *free)
{
    void *dd2 = 0;
    uint caps[1];

    if (COMX(PTR_00806968, 0, &DAT_004d8460, &dd2) != 0)
        return 0;
    caps[0] = 0x1000;
    if (COMX(dd2, 0x5c, caps, total, free) != 0)
        return 0;
    COMX(dd2, 8);
    return 1;
}

#endif /* GRIM_EXE */
