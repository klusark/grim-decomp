// watch.exe <seconds> <outprefix> <titlesubstr>
// samples the desktop thumbnail + state of windows (class wKernel / title substring) as fast as possible
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TW 192
#define TH 108
typedef struct { double t; unsigned char *pix; double dark; char info[512]; } Frame;
static const char *g_sub; static char g_info[512]; static int g_n;
static BOOL CALLBACK enumw(HWND h, LPARAM l) {
  char cls[64], title[128];
  GetClassNameA(h, cls, sizeof cls); GetWindowTextA(h, title, sizeof title);
  if (!strcmp(cls, "wKernel") || (g_sub[0] && strstr(title, g_sub))) {
    RECT r; GetWindowRect(h, &r);
    LONG st = GetWindowLongA(h, GWL_STYLE), ex = GetWindowLongA(h, GWL_EXSTYLE);
    DWORD pid; GetWindowThreadProcessId(h, &pid);
    int n = strlen(g_info);
    snprintf(g_info + n, sizeof g_info - n, "[%s pid%lu vis%d ico%d %ld,%ld %ldx%ld st%08lx ex%08lx top%d] ", strstr(title,"agent")?strstr(title,"agent"):title, pid,
      IsWindowVisible(h), IsIconic(h), r.left, r.top, r.right-r.left, r.bottom-r.top, st, ex, (ex & WS_EX_TOPMOST)!=0);
  }
  return TRUE;
}
static void bmp(const char *fn, unsigned char *bgr) {
  FILE *f = fopen(fn, "wb"); BITMAPFILEHEADER fh = {0x4d42, 54 + TW*TH*3, 0, 0, 54};
  BITMAPINFOHEADER ih = {40, TW, -TH, 1, 24, 0, TW*TH*3};
  fwrite(&fh, 14, 1, f); fwrite(&ih, 40, 1, f); fwrite(bgr, TW*TH*3, 1, f); fclose(f);
}
int main(int argc, char **argv) {
  double secs = atof(argv[1]); const char *pref = argv[2]; g_sub = argc > 3 ? argv[3] : "";
  int maxf = 4000; Frame *fr = calloc(maxf, sizeof(Frame));
  HDC scr = GetDC(0), mem = CreateCompatibleDC(scr);
  int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
  BITMAPINFO bi = {{40, TW, -TH, 1, 24, 0}}; void *bits;
  HBITMAP bm = CreateDIBSection(scr, &bi, DIB_RGB_COLORS, &bits, 0, 0); SelectObject(mem, bm);
  SetStretchBltMode(mem, COLORONCOLOR);
  LARGE_INTEGER fq, t0, t; QueryPerformanceFrequency(&fq); QueryPerformanceCounter(&t0);
  printf("screen %dx%d\n", sw, sh);
  for (;;) {
    QueryPerformanceCounter(&t); double now = (double)(t.QuadPart - t0.QuadPart) / fq.QuadPart;
    if (now > secs || g_n >= maxf) break;
    g_info[0] = 0; EnumWindows(enumw, 0);
    HWND fg = GetForegroundWindow(); char ft[64] = ""; GetWindowTextA(fg, ft, sizeof ft);
    int n = strlen(g_info); snprintf(g_info + n, sizeof g_info - n, "fg='%.30s'", ft);
    StretchBlt(mem, 0, 0, TW, TH, scr, 0, 0, sw, sh, SRCCOPY);
    Frame *f = &fr[g_n++]; f->t = now; f->pix = malloc(TW*TH*3); memcpy(f->pix, bits, TW*TH*3);
    long dk = 0; for (int i = 0; i < TW*TH; i++) { unsigned char *p = f->pix + i*3; if (p[0] + p[1] + p[2] < 24) dk++; }
    f->dark = (double)dk / (TW*TH); strcpy(f->info, g_info);
  }
  char fn[512]; snprintf(fn, sizeof fn, "%s_log.txt", pref); FILE *lg = fopen(fn, "w");
  char last[512] = ""; double lastdark = -1;
  for (int i = 0; i < g_n; i++) {
    snprintf(fn, sizeof fn, "%s_%04d.bmp", pref, i); bmp(fn, fr[i].pix);
    fprintf(lg, "%04d t=%.3f dark=%.2f %s\n", i, fr[i].t, fr[i].dark, fr[i].info);
  }
  fclose(lg); printf("%d frames, %.1f fps\n", g_n, g_n / secs);
  return 0;
}
