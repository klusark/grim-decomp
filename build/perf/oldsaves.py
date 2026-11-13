r"""Regression test: saves written by the ORIGINAL game load in the rebuilt engine.

usage: python -I oldsaves.py <exe-dir> [--saves DIR] [--data DIR] [--tag TAG] [--only NN,NN,..] [--keep]

  <exe-dir>  folder with the rebuilt grimfandango.exe + the three DLLs (build/run)
  --saves    folder with the original saves grimNN.gsv (default: <data>/saves_old_numbering)
  --data     the game's data folder = working directory (default C:\GOG Games\GRIMDATA)
  --tag      GRIM_MULTI tag, window title, prefix of the private copies of the saves (default oldsaves)
  --only     comma separated save numbers (default: all grim*.gsv of the folder)

Per save (a fresh game each time, Lua test hook, no OS input): copy the save to a private name, `Load` it, wait for
the hook to answer, then check
  * the process is alive and no grim_crash_<tag>.txt was written;
  * the scene state (current set, Manny's position, setup) can be read;
  * every sound the save lists (iMUSE sound table at the end of the file) is playing (ImGetParam(id, 256) > 0), reported
    only (a one-shot sfx may have ended);
  * a Lua task keeps running (sleep_for -> TICK);
  * Manny walks (manny:walkto 0.5 m in up to four directions, reported only: some saves stand in a cutscene);
  * the game's set switcher works (switch_to_set of mo.set, or ha.set when already there, changes the current set);
  * the rebuilt engine can `Save` this state, a Lua marker and the scene state survive a `Load` of that save
    (original save -> rebuilt save -> reload), and the game keeps running afterwards.
The private copies are removed at the end unless --keep. Exit code 1 if any save fails a hard check."""
import subprocess, time, os, sys, re, gzip, struct, shutil, argparse

ap = argparse.ArgumentParser()
ap.add_argument('exe'); ap.add_argument('--saves'); ap.add_argument('--data', default=r'C:\GOG Games\GRIMDATA')
ap.add_argument('--tag', default='oldsaves'); ap.add_argument('--only'); ap.add_argument('--keep', action='store_true')
a = ap.parse_args()
data = a.data; saves = a.saves or os.path.join(data, 'saves_old_numbering'); tag = a.tag
tmp = os.environ.get('TEMP', r'C:\Windows\Temp')
cmdf = os.path.join(tmp, 'grim_%s_cmd.lua' % tag); logf = os.path.join(tmp, 'grim_%s_log.txt' % tag)
crashf = os.path.join(data, 'grim_crash_%s.txt' % tag)
priv_old = '%s_old.gsv' % tag; priv_re = '%s_re.gsv' % tag

DEFS = ('function agk_state() local s=system.currentSet local x,y,z=GetActorPos(manny.hActor) '
        'grimlog("ST".."ATE "..tostring(s and s.setFile).." "..format("%.3f %.3f %.3f",x,y,z).." "..tostring(s and GetCurrentSetup(s.setFile))) end')


def im_sounds(path):
    """(name, id) of the sounds in the iMUSE tail of an (uncompressed) save; the tail is
    40 + 4 + 38564 + 4 + 984 + 4 + 60 n bytes (see BUILD_NOTES 'Saves of the original game')."""
    d = gzip.open(path).read()
    for n in range(0, 80):
        p = len(d) - 60 * n - 4 - 984 - 4 - 38564 - 4 - 40
        if p > 0 and struct.unpack_from('<I', d, p + 40)[0] == 38564 and struct.unpack_from('<I', d, p + 44 + 38564)[0] == 984 \
                and struct.unpack_from('<I', d, p + 44 + 38564 + 4 + 984)[0] == n:
            q = p + 44 + 38564 + 4 + 984 + 4
            return [(d[q + i * 40:q + i * 40 + 32].split(b'\0')[0].decode('latin1'), struct.unpack_from('<I', d, q + i * 40 + 32)[0])
                    for i in range(n)]
    return None


def crash_info():
    try:
        shutil.copy(crashf, os.path.join(tmp, 'grim_%s_lastcrash.txt' % tag))    # the full report (registers + stack)
        l = open(crashf, errors='replace').read().splitlines()
        return ' [crash: %s | %s]' % (l[0].strip(), l[1].strip()[:90])
    except OSError:
        return ''


class Game:
    def __init__(self):
        env = dict(os.environ, GRIM_MULTI=tag, GRIM_NOMOVIE='1', GRIM_LUA_FILE=cmdf, GRIM_LUA_LOG=logf)
        open(cmdf, 'w').close()
        try: os.remove(logf)
        except OSError: pass
        try: os.remove(crashf)
        except OSError: pass
        self.p = subprocess.Popen([os.path.join(a.exe, 'grimfandango.exe')], cwd=data, env=env,
                                  stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        self.mark = 0

    def log(self):
        try: return open(logf, errors='replace').read()
        except OSError: return ''

    def cmd(self, s): open(cmdf, 'a').write(s + '\n')

    def alive(self): return self.p.poll() is None and not os.path.exists(crashf)

    def wait(self, pat, timeout=30, start=0):
        t = time.time()
        while time.time() - t < timeout:
            l = self.log()
            i = l.find(pat, start)
            if i >= 0: return l[i:i + 200].split('\n')[0]
            if not self.alive(): return None
            time.sleep(0.15)
        return None

    def sync(self, timeout=30):
        """run a marker through the hook: everything sent before has been executed once it answers"""
        self.mark += 1
        m = 'MK%d' % self.mark
        l0 = len(self.log())
        self.cmd('grimlog("MK".."%d")' % self.mark)
        return self.wait(m, timeout, l0) is not None

    def state(self):
        l0 = len(self.log())
        self.cmd(DEFS); self.cmd('agk_state()')
        r = self.wait('STATE ', 15, l0)
        return r.strip() if r else None

    def stop(self):
        try: self.p.kill()
        except OSError: pass
        self.p.wait()


def boot():
    for attempt in (1, 2, 3):
        g = Game()
        if g.wait('lua hook active', 90):
            return g, attempt
        g.stop()
    return None, 3


def one(nn):
    src = os.path.join(saves, 'grim%s.gsv' % nn)
    shutil.copy(src, os.path.join(data, priv_old))
    sounds = im_sounds(src) or []
    res = []; fail = False
    g, attempt = boot()
    if g is None:
        return False, ['no boot (3 attempts)' + crash_info()]
    if attempt > 1: res.append('boot needed %d attempts' % attempt)
    try:
        time.sleep(3)   # let the opening scene settle
        g.cmd('Load("%s")' % priv_old)
        if not g.sync(40):
            return False, ['load: no answer (crash or hang)' + crash_info()]
        st = g.state()
        res.append('state: %s' % st)
        if not st: fail = True
        snd = []
        for name, sid in sounds:
            l0 = len(g.log()); g.cmd('grimlog("SN".."D %d="..tostring(ImGetParam(%d,256)))' % (sid, sid))
            r = g.wait('SND %d=' % sid, 10, l0); snd.append('%s#%d:%s' % (name, sid, r.split('=')[1].strip() if r else '?'))
        if snd: res.append('sounds ' + ' '.join(snd))
        l0 = len(g.log())
        g.cmd('start_script(function() sleep_for(700) grimlog("TI".."CK") end)')
        tick = g.wait('TICK', 10, l0) is not None
        res.append('tick %s' % ('ok' if tick else 'MISSING')); fail |= not tick
        # walk a little
        l0 = len(g.log()); g.cmd(DEFS)
        g.cmd('agk_d={{0.5,0},{-0.5,0},{0,0.5},{0,-0.5}}')
        g.cmd('function agk_w() local x,y,z=GetActorPos(manny.hActor) local i=1 local best=0 '
              'while agk_d[i] and best<0.1 do manny:walkto(x+agk_d[i][1],y+agk_d[i][2],z) sleep_for(1000) '
              'local a,b=GetActorPos(manny.hActor) local m=sqrt((a-x)*(a-x)+(b-y)*(b-y)) if m>best then best=m end i=i+1 end '
              'manny:stop_walk() grimlog("WA".."LK "..format("%.2f",best)) end')
        g.cmd('start_script(agk_w)')
        r = g.wait('WALK ', 30, l0); res.append('walk moved ' + (r.split()[1] if r else '?') + ' m')
        # let Manny stop (a walk in progress is restored as a walk in progress, which makes the state comparison moot)
        l0 = len(g.log())
        g.cmd('start_script(function() local n=0 while IsActorMoving(manny.hActor) and n<60 do sleep_for(100) n=n+1 end '
              'sleep_for(300) grimlog("ID".."LE") end)')
        g.wait('IDLE', 20, l0)
        # original save -> rebuilt save -> reload
        g.cmd(DEFS)
        l0 = len(g.log())
        g.cmd('agk_marker=424242')
        g.cmd('agk_state() Save("%s")' % priv_re)       # state and Save in the same frame (Manny may still be walking)
        r1 = g.wait('STATE ', 15, l0); st1 = r1.strip() if r1 else None
        ok = g.sync(40)
        g.cmd('agk_marker=7'); g.cmd('Load("%s")' % priv_re); ok &= g.sync(40)
        if not ok:
            return False, res + ['re-save/re-load: no answer' + crash_info()]
        l0 = len(g.log()); g.cmd('grimlog("MARK".."ER="..tostring(agk_marker))')
        mk = g.wait('MARKER=', 10, l0)
        st2 = g.state()
        same = False
        if st1 and st2:
            f1, f2 = st1.split(), st2.split()
            same = f1[1] == f2[1] and f1[-1] == f2[-1] and max(abs(float(f1[i]) - float(f2[i])) for i in (2, 3, 4)) < 0.1
        res.append('resave: marker %s, state %s' % (mk.split('=')[1].strip() if mk else '?', 'same' if same else 'DIFFERENT %s / %s' % (st1, st2)))
        fail |= not (mk and mk.strip().endswith('424242') and same)
        l0 = len(g.log()); g.cmd('start_script(function() sleep_for(500) grimlog("TO".."CK2") end)')
        t2 = g.wait('TOCK2', 10, l0) is not None
        res.append('tick after reload %s' % ('ok' if t2 else 'MISSING')); fail |= not t2
        # change sets: the game's own set switcher
        l0 = len(g.log())
        target = 'ha.set' if st2 and st2.split()[1] == 'mo.set' else 'mo.set'
        g.cmd('start_script(function() system.setTable["%s"]:switch_to_set() sleep_for(800) grimlog("SW".."ITCHED") end)' % target)
        sw = g.wait('SWITCHED', 40, l0) is not None
        st3 = g.state()
        res.append('switch set: %s' % (st3 if sw else 'NO ANSWER' + crash_info()))
        fail |= not (sw and st3 and st2 and st3.split()[1] != st2.split()[1])
        if not g.alive():
            res.append('PROCESS DIED' + crash_info()); fail = True
        return not fail, res
    finally:
        g.stop()


nums = sorted(re.findall(r'grim(\d+)\.gsv$', f)[0] for f in os.listdir(saves) if re.match(r'grim\d+\.gsv$', f))
if a.only: nums = [n for n in nums if n in a.only.split(',')]
bad = []
flaky = []
for nn in nums:
    ok, res = one(nn)
    if not ok and any('[crash:' in r for r in res):
        # an intermittent crash in the background / z-buffer decompressor after a load was seen a few times (BUILD_NOTES): once more
        first = ' | '.join(res)
        ok, res = one(nn)
        if ok:
            flaky.append(nn); res = res + ['FLAKY: first attempt crashed: ' + first[-260:]]
    print('%s grim%s: %s' % ('OK  ' if ok else 'FAIL', nn, ' | '.join(res)), flush=True)
    if not ok: bad.append(nn)
if not a.keep:
    for f in (priv_old, priv_re):
        try: os.remove(os.path.join(data, f))
        except OSError: pass
print('%d saves, %d failed %s%s' % (len(nums), len(bad), bad, ('; crashed once and passed on retry: %s' % flaky) if flaky else ''))
sys.exit(1 if bad else 0)
