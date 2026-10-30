r"""Audio behaviour check for the Smush movie sound (the EXE's own DirectSound stream driver and sound module) and iMUSE.

usage: python -I audiocheck.py <exe-dir> <tag> [--data DIR] [--movie funny.snm] [--peakmeter PATH] [--simtime]

Starts ONE game (real time unless --simtime, movies on, Lua test hook), goes to Manny's office, plays a movie to the end
and meters the audio sessions of the game process with peakmeter.exe (build/perf/peakmeter.c) while it plays:
  MOVIE peak P audible_polls A polls N  movie_seconds S
then plays the iMUSE sound effect me_tank3.wav / a sound of the office and meters it (IMUSE peak ...).
Only the game it started is killed (by PID).  Compare two builds by their output: the peaks of the same movie are close
(the movie audio is the same data), a silent build prints peak 0.0000."""
import subprocess, time, os, sys, argparse

here = os.path.dirname(os.path.abspath(__file__))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('exe'); ap.add_argument('tag')
    ap.add_argument('--data', default=r'C:\Users\Joel\grimO_data')
    ap.add_argument('--movie', default='funny.snm')
    ap.add_argument('--peakmeter', default=os.path.join(here, 'peakmeter.exe'))
    ap.add_argument('--simtime', action='store_true')
    a = ap.parse_args()
    tmp = os.environ.get('TEMP', r'C:\Windows\Temp')
    cmdf = os.path.join(tmp, 'grim_%s_acmd.lua' % a.tag); logf = os.path.join(tmp, 'grim_%s_alog.txt' % a.tag)
    for f in (logf,):
        try: os.remove(f)
        except OSError: pass
    open(cmdf, 'w').close()
    env = dict(os.environ, GRIM_MULTI=a.tag, GRIM_ACTIVE='1', GRIM_LUA_FILE=cmdf, GRIM_LUA_LOG=logf, _NO_DEBUG_HEAP='1')
    if a.simtime:
        env['GRIM_SIMTIME'] = '17'
    p = subprocess.Popen([os.path.join(a.exe, 'grimfandango.exe')], cwd=a.data, env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

    def log():
        try: return open(logf, errors='replace').read()
        except OSError: return ''

    def cmd(s): open(cmdf, 'a').write(s + '\n')

    def wait(pat, timeout):
        t = time.time()
        while time.time() - t < timeout:
            if pat in log(): return True
            if p.poll() is not None: return False
            time.sleep(0.2)
        return False

    ok = True
    try:
        if not wait('lua hook active', 90):
            print('FAIL no hook'); return 1
        t0 = time.time()
        while 'OFFICE' not in log() and p.poll() is None and time.time() - t0 < 120:
            cmd('if manny and GetCurrentSet and GetCurrentSet() then grimlog("OFFICE "..tostring(system.currentSet.setFile)) end')
            time.sleep(0.3)
        time.sleep(2)
        # the movie
        cmd('function AMov() StartFullscreenMovie("%s") while IsMoviePlaying() do break_here() end grimlog("MOV".."IEDONE") end' % a.movie)
        cmd('start_script(AMov)')
        tm = time.time()
        stopf = os.path.join(tmp, 'grim_%s_stop' % a.tag)
        try: os.remove(stopf)
        except OSError: pass
        mp = subprocess.Popen([a.peakmeter, str(p.pid), '120', '15', stopf], stdout=subprocess.PIPE, text=True)
        done = wait('MOVIEDONE', 120)
        secs = time.time() - tm
        time.sleep(1.0)
        open(stopf, 'w').close()
        try:
            out, _ = mp.communicate(timeout=60)
        except Exception:
            out = ''
        print('MOVIE %s %s' % (a.movie, 'done' if done else 'NOT DONE'), out.strip() or '(no meter output)', 'movie_seconds %.1f' % secs)
        ok = ok and done
        # the process must still run
        print('alive after the movie:', p.poll() is None)
        ok = ok and p.poll() is None
    finally:
        if p.poll() is None:
            p.kill()
        p.wait()
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
