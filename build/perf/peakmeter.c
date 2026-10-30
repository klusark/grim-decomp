/* Per-process audio peak meter (Windows core audio): polls IAudioMeterInformation of the audio sessions of one process
 * and prints the maximum peak seen, the number of polls with a peak above 0.001 and the number of polls.
 *   peakmeter.exe <pid> <seconds> [interval ms] [stop file]      (build: gcc peakmeter.c -o peakmeter.exe -lole32 -loleaut32 -luuid)
 * Used to compare the sound output of two builds of the game without listening to it: the peak of a sound that
 * plays is a deterministic number only if the same sound plays at the same time, so tests compare "silent / audible"
 * and the ratio of the peaks of the same sound. */
#define INITGUID
#define COBJMACROS
#include <windows.h>
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#include <endpointvolume.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct MyMeter MyMeter;
typedef struct MyMeterVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(MyMeter *, REFIID, void **);
    ULONG (STDMETHODCALLTYPE *AddRef)(MyMeter *);
    ULONG (STDMETHODCALLTYPE *Release)(MyMeter *);
    HRESULT (STDMETHODCALLTYPE *GetPeakValue)(MyMeter *, float *);
} MyMeterVtbl;
struct MyMeter { const MyMeterVtbl *lpVtbl; };   /* IAudioMeterInformation */
static const GUID IID_AMI = {0xC02216F6, 0x8C67, 0x4B5B, {0x9D, 0x00, 0xD0, 0x08, 0xE7, 0x3E, 0x00, 0x64}};

int main(int argc, char **argv)
{
    DWORD pid = argc > 1 ? (DWORD)atol(argv[1]) : 0;
    int seconds = argc > 2 ? atoi(argv[2]) : 5;
    int interval = argc > 3 ? atoi(argv[3]) : 20;
    const char *stopfile = argc > 4 ? argv[4] : NULL;   /* the meter stops (and prints) as soon as this file exists */
    IMMDeviceEnumerator *en = NULL;
    IMMDevice *dev = NULL;
    IAudioSessionManager2 *mgr = NULL;
    float maxpeak = 0.0f;
    long polls = 0, audible = 0;
    ULONGLONG t0;

    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (void **)&en))) { printf("no enumerator\n"); return 2; }
    if (FAILED(IMMDeviceEnumerator_GetDefaultAudioEndpoint(en, eRender, eConsole, &dev))) { printf("no audio device\n"); return 3; }
    if (FAILED(IMMDevice_Activate(dev, &IID_IAudioSessionManager2, CLSCTX_ALL, NULL, (void **)&mgr))) { printf("no session manager\n"); return 4; }
    t0 = GetTickCount64();
    while (GetTickCount64() - t0 < (ULONGLONG)seconds * 1000 && !(stopfile && GetFileAttributesA(stopfile) != INVALID_FILE_ATTRIBUTES)) {
        IAudioSessionEnumerator *se = NULL;
        int n = 0, i;
        if (SUCCEEDED(IAudioSessionManager2_GetSessionEnumerator(mgr, &se))) {
            IAudioSessionEnumerator_GetCount(se, &n);
            for (i = 0; i < n; i++) {
                IAudioSessionControl *ctl = NULL;
                IAudioSessionControl2 *ctl2 = NULL;
                if (FAILED(IAudioSessionEnumerator_GetSession(se, i, &ctl))) continue;
                if (SUCCEEDED(IAudioSessionControl_QueryInterface(ctl, &IID_IAudioSessionControl2, (void **)&ctl2))) {
                    DWORD p = 0;
                    IAudioSessionControl2_GetProcessId(ctl2, &p);
                    if (p == pid) {
                        MyMeter *meter = NULL;
                        if (SUCCEEDED(IAudioSessionControl_QueryInterface(ctl, &IID_AMI, (void **)&meter))) {
                            float pk = 0.0f;
                            meter->lpVtbl->GetPeakValue(meter, &pk);
                            if (pk > maxpeak) maxpeak = pk;
                            if (pk > 0.001f) audible++;
                            polls++;
                            meter->lpVtbl->Release(meter);
                        }
                    }
                    IAudioSessionControl2_Release(ctl2);
                }
                IAudioSessionControl_Release(ctl);
            }
            IAudioSessionEnumerator_Release(se);
        }
        Sleep(interval);
    }
    printf("peak %.4f audible_polls %ld polls %ld\n", maxpeak, audible, polls);
    return 0;
}
