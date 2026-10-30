# Save a PrintWindow screenshot of the running game window (works while the window is behind others).
#   powershell -ExecutionPolicy Bypass -File tools/grim_shot.ps1 -Out shot.png [-Tag dev]
param([string]$Out = "grim_shot.png", [string]$Tag = "dev")
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System; using System.Runtime.InteropServices;
public class GrimShot { [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr hdc, uint f);
 [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
 [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; } }
"@
$p = Get-Process | Where-Object { $_.MainWindowTitle -eq "Grim Fandango ($Tag)" } | Select-Object -First 1
if (-not $p) { "no window titled 'Grim Fandango ($Tag)'"; exit 1 }
$r = New-Object GrimShot+RECT
[GrimShot]::GetWindowRect($p.MainWindowHandle, [ref]$r) | Out-Null
$bmp = New-Object System.Drawing.Bitmap ($r.R - $r.L), ($r.B - $r.T)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$hdc = $g.GetHdc(); [GrimShot]::PrintWindow($p.MainWindowHandle, $hdc, 2) | Out-Null; $g.ReleaseHdc($hdc)
$full = if ([IO.Path]::IsPathRooted($Out)) { $Out } else { Join-Path (Get-Location) $Out }
$bmp.Save($full); "saved $full (pid $($p.Id))"
