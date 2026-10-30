r"""Behaviour battery for the "system libraries instead of the bundled CRT/zlib" work (BUILD_NOTES: System libraries).

usage: python -I libcheck.py <exe-dir> <tag> [--data DIR] [--out DIR] [--movie] [--sets N]
       python -I libcheck.py --diff <outA> <outB>

Runs ONE fresh game from <exe-dir> (movies off, fixed 17 ms frame time, Lua test hook, no OS input, own GRIM_MULTI tag) and
writes into <out>/<tag>/:
  probe.txt   Lua-level probes: number->string / format() of 23 values, floor/ceil/sqrt/mod/pow/trig, string library,
              tonumber, sort, Save/Load round trip, the engine's debug log text
  idle.png.raw, walk.png.raw, setNN.png.raw   PrintWindow shots (raw BGRA) of Manny's office, after a walk, N sets
  summary.txt PASS/FAIL lines, boot time, ms/frame (GRIM_PERFLOG), crash report if any
With --movie a second game is started with movies on: plays funny.snm to the end (time measured) and checks the
process survives. `--diff A B` compares two runs: probe.txt must be identical, shots are compared pixel-wise.
Only the game it started is killed (by PID). --data is the working directory of the game (a private hard-linked copy
of GRIMDATA is recommended when other sessions use the shared one)."""
import subprocess, time, os, sys, re, gzip, shutil, argparse, hashlib

here = os.path.dirname(os.path.abspath(__file__))


def shotdiff(a, b):
    if not (os.path.exists(a) and os.path.exists(b)):
        return 'missing'
    A = open(a, 'rb').read(); B = open(b, 'rb').read()
    if len(A) != len(B):
        return 'size differs'
    n = len(A) // 4
    bad = big = 0
    for i in range(0, len(A), 4):
        d = max(abs(A[i] - B[i]), abs(A[i + 1] - B[i + 1]), abs(A[i + 2] - B[i + 2]))
        if d:
            bad += 1
            if d > 24:
                big += 1
    return '%.3f%% differ, %.3f%% differ by more than 24' % (100 * bad / n, 100 * big / n)


def diff(oa, ob):
    rc = 0
    la = open(os.path.join(oa, 'probe.txt'), errors='replace').read().splitlines()
    lb = open(os.path.join(ob, 'probe.txt'), errors='replace').read().splitlines()
    skip = os.environ.get('LIBCHECK_SKIP')   # e.g. A,RU: line prefixes expected to differ (A = asin/acos, which returned 0 in the old builds;
    if skip:                                  # RU = random() before any randomseed: the old builds started rand() at seed 0, the original at 1)
        pat = re.compile(r'^(%s)\d* ' % '|'.join(skip.split(',')))
        la = [l for l in la if not pat.match(l)]; lb = [l for l in lb if not pat.match(l)]
    if la == lb:
        print('probe.txt: identical (%d lines)' % len(la))
    else:
        rc = 1
        print('probe.txt: DIFFERENT')
        shown = 0
        for x, y in zip(la, lb):
            if x != y and shown < 12:
                shown += 1
                print('  A:', x[:220]); print('  B:', y[:220])
        if len(la) != len(lb):
            print('  line counts', len(la), len(lb))
    for f in sorted(os.listdir(oa)):
        if f.endswith('.raw') and os.path.exists(os.path.join(ob, f)):
            print('%s: %s' % (f, shotdiff(os.path.join(oa, f), os.path.join(ob, f))))
    return rc


PN = '{0,1,-1,0.1,0.5,0.3333333333333333,123456789,1e15,1e16,1e100,-1e-5,3.14159265358979,2147483648,4294967296,9007199254740992,255,0.000123456789,1e-300,123456.789,-7.5,100,1e21,5e-324}'
PROBES = [
    'PN=' + PN,
    'function S1(f,a,b) if type(f)=="function" then return tostring(f(a,b)) else return "nofn" end end',
    'function PR() local i=1 while PN[i] do local n=PN[i] grimlog("P"..i.." "..tostring(n).." "..format("%.14g|%f|%e|%5.2f|%g|%.3g|%10.4f|%-8.1f|%.0f|%.20g|",n,n,n,n,n,n,n,n,n,n)..S1(floor,n).." "..S1(ceil,n).." "..S1(abs,n)) i=i+1 end end',
    'function PM() local i=1 while PN[i] do local n=PN[i] local a=abs(n) grimlog("M"..i.." "..S1(sqrt,a).." "..S1(mod,n,7).." "..S1(mod,n,0.3).." "..tostring(a^0.5).." "..tostring(a^2.5).." "..S1(sin,n).." "..S1(cos,n).." "..S1(tan,n).." "..S1(atan,n).." "..S1(atan2,n,3).." "..S1(log,a+1).." "..S1(log10,a+1).." "..S1(exp,mod(a,40)).." "..S1(min,n,2).." "..S1(max,n,2)) i=i+1 end end',
    'function PA() local i=1 while PN[i] do local n=PN[i] grimlog("A"..i.." "..S1(asin,n/100000).." "..S1(acos,n/100000).." "..S1(asin,mod(n,1)).." "..S1(acos,mod(n,1))) i=i+1 end end',
    'function PRn() local s="" local i=1 while i<=8 do s=s..tostring(random(1000)).."," i=i+1 end grimlog("RU "..s) randomseed(7) s="" i=1 while i<=8 do s=s..tostring(random(1000)).."," i=i+1 end grimlog("R2 "..s) s="" i=1 while i<=4 do s=s..format("%.6f",random()).."," i=i+1 end grimlog("R3 "..s) end',
    'function PI() grimlog("I "..format("%d|%5d|%-5d|%05d|%x|%X|%o|%c|%s|%5s|%-5s|%i|%u",42,-7,7,12,255,255,8,65,"abc","ab","cd",5,3)) grimlog("I2 "..format("%d %d %d",2147483647,-2147483648,1e9)) grimlog("I3 "..format("%s %s","q",tostring(nil))) end',
    'function PS() local s="Hello, World! hello" grimlog("S "..strlen(s).." "..strsub(s,3,7).." "..strlower(s).." "..strupper(s).." "..strrep("ab",3).." "..tostring(strfind(s,"o, W")).." "..tostring(strfind(s,"(l+)o")).." "..gsub(s,"l","L").." "..strlen(strrep(s,2))) grimlog("T "..tostring(tonumber("0x1F")).." "..tostring(tonumber("  12  ")).." "..tostring(tonumber("1e3")).." "..tostring(tonumber("abc")).." "..tostring(tonumber("10",2)).." "..tostring(tonumber("1.5e-3")).." "..tostring(tonumber(".5")).." "..tostring(tonumber("-0")).." "..tostring(tonumber("12abc"))) end',
    'PR() PM() PA() PRn() PI() PS() grimlog("PROBESDONE")',
]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('exe'); ap.add_argument('tag')
    ap.add_argument('--data', default=r'C:\Users\Joel\grimM_data')
    ap.add_argument('--out', default=r'C:\Users\Joel\grimM_tmp\out')
    ap.add_argument('--movie', action='store_true'); ap.add_argument('--sets', type=int, default=5)
    a = ap.parse_args()
    exe, tag, data = a.exe, a.tag, a.data
    out = os.path.join(a.out, tag); shutil.rmtree(out, ignore_errors=True); os.makedirs(out)
    tmp = os.environ.get('TEMP', r'C:\Windows\Temp')
    cmdf = os.path.join(tmp, 'grim_%s_cmd.lua' % tag); logf = os.path.join(tmp, 'grim_%s_log.txt' % tag)
    dbg = os.path.join(tmp, 'grim_%s_debug.log' % tag)
    crashf = os.path.join(data, 'grim_crash_%s.txt' % tag)
    for f in (logf, dbg, crashf):
        try: os.remove(f)
        except OSError: pass
    open(cmdf, 'w').close()
    summ = []
    fail = [False]

    def start(movies):
        env = dict(os.environ, GRIM_MULTI=tag, GRIM_ACTIVE='1', GRIM_LUA_FILE=cmdf, GRIM_LUA_LOG=logf, GRIM_PERFLOG='1',
                   GRIM_SIMTIME='17', GRIM_DEBUGLOG=dbg, _NO_DEBUG_HEAP='1')
        if not movies:
            env['GRIM_NOMOVIE'] = '1'
        return subprocess.Popen([os.path.join(exe, 'grimfandango.exe')], cwd=data, env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

    def log():
        try: return open(logf, errors='replace').read()
        except OSError: return ''

    def cmd(s): open(cmdf, 'a').write(s + '\n')

    def wait(p, pat, timeout):
        t = time.time()
        while time.time() - t < timeout:
            if pat in log(): return True
            if p.poll() is not None: return False
            time.sleep(0.2)
        return False

    def shot(name):
        o = os.path.join(out, name + '.png')
        subprocess.run([sys.executable, '-I', os.path.join(here, 'shot.py'), o, 'Grim Fandango (%s)' % tag], capture_output=True)

    def check(cond, msg):
        summ.append(('PASS ' if cond else 'FAIL ') + msg)
        if not cond: fail[0] = True

    # ---------------- phase A: movies off
    t0 = time.time()
    p = start(False)
    check(wait(p, 'lua hook active', 90), 'lua hook active')
    t_hook = time.time() - t0
    while 'OFFICE' not in log() and p.poll() is None and time.time() - t0 < 180:
        cmd('if manny and GetCurrentSet and GetCurrentSet() then grimlog("OFFICE "..tostring(system.currentSet.setFile)) end')
        time.sleep(0.3)
    check('OFFICE' in log(), 'boot to Manny office (hook %.1fs, office %.1fs)' % (t_hook, time.time() - t0))
    if p.poll() is None:
        time.sleep(2)
        shot('idle')
        for l in PROBES: cmd(l)
        check(wait(p, 'PROBESDONE', 60), 'Lua probes ran')
        cmd('function ST() local p=manny:getpos() grimlog("POS "..format("%.3f %.3f %.3f",p.x,p.y,p.z).." "..tostring(system.currentSet.setFile)) end')
        cmd('ST()')
        cmd('manny:walkto(0.2,2.2,0)')
        time.sleep(4)
        cmd('ST()'); shot('walk')
        # a few sets
        sets = ["mo.set", "ha.set", "ga.set", "bi.set", "lr.set", "mx.set", "ce.set", "do.set"][:a.sets]
        cmd('function T(n) local s=system.setTable[n] s:switch_to_set() grimlog("SW "..n) end')
        cmd('soak_list = {' + ','.join('"%s"' % s for s in sets) + '}')
        cmd('function SoakRun() local i=1 while soak_list[i] do T(soak_list[i]) sleep_for(2500) i=i+1 end grimlog("SOAKDONE") end')
        cmd('start_script(SoakRun)')
        for i, s in enumerate(sets):
            if not wait(p, 'SW ' + s, 30):
                check(False, 'set %s reached' % s); break
            time.sleep(2.0)
            if p.poll() is not None: break
            shot('set%02d' % i)
        # Save / Load round trip
        cmd('zz=5 ww="five"')
        cmd('Save("%s_rt.gsv")' % tag); time.sleep(5)
        cmd('zz=7 ww="seven"'); time.sleep(0.5)
        cmd('Load("%s_rt.gsv")' % tag); time.sleep(6)
        cmd('grimlog("ZZ="..tostring(zz).." WW="..tostring(ww))'); time.sleep(1.5)
        z = [l for l in log().splitlines() if l.startswith('ZZ=')]
        check(bool(z) and z[-1] == 'ZZ=5 WW=five', 'save/load round trip (%s)' % (z[-1] if z else 'no answer'))
        sv = os.path.join(data, '%s_rt.gsv' % tag)
        try:
            raw = gzip.open(sv).read()
            summ.append('INFO save: %d bytes gz, %d uncompressed' % (os.path.getsize(sv), len(raw)))
            open(os.path.join(out, 'save.size'), 'w').write(str(len(raw)))
        except Exception as e:
            summ.append('FAIL save is not readable as gzip: %s' % e); fail[0] = True
        try: os.remove(sv)
        except OSError: pass
        errs = [l for l in log().splitlines() if l.startswith('rc=') and not l.startswith('rc=0')]
        check(not errs, 'no Lua errors %s' % errs[:2])
        perf = [l for l in log().splitlines() if l.startswith('perf:')]
        if perf: summ.append('INFO ' + perf[-1])
    check(p.poll() is None, 'process alive after phase A')
    lines = [l for l in log().splitlines() if re.match(r'^(P\d+|M\d+|A\d+|RU|R\d|I\d?|S|T|SORT|POS|ZZ=)\b', l)]
    try:
        dl = open(dbg, errors='replace').read().splitlines()
        lines += ['DBG ' + re.sub(r'^\[\s*\d+\]', '[T]', re.sub(r'\d+\.\d+ ?(ms|s)\b', 'T', l)) for l in dl[:next((i for i, x in enumerate(dl) if 'c u r r e n t' in x), 400)] if 'FREEING' not in l]
    except OSError:
        pass
    open(os.path.join(out, 'probe.txt'), 'w').write('\n'.join(lines) + '\n')
    if os.path.exists(crashf):
        summ.append('CRASH REPORT: ' + open(crashf, errors='replace').read()[:300].replace('\n', ' | ')); fail[0] = True
    if p.poll() is None: p.kill()
    p.wait()
    time.sleep(1)
    # ---------------- phase B: movie
    if a.movie:
        try: os.remove(logf)
        except OSError: pass
        open(cmdf, 'w').close()
        p = start(True)
        wait(p, 'lua hook active', 90)
        cmd('function T(n) local s=system.setTable[n] s:switch_to_set() grimlog("SW "..n) end')
        cmd('T("mo.set")'); time.sleep(3)
        cmd('function SoakMov() StartFullscreenMovie("funny.snm") while IsMoviePlaying() do break_here() end grimlog("MOVIEDONE") end')
        cmd('start_script(SoakMov)')
        tm = time.time(); time.sleep(4); shot('movie1')
        ok = wait(p, 'MOVIEDONE', 180)
        check(ok, 'movie funny.snm played to the end in %.1fs' % (time.time() - tm))
        check(p.poll() is None, 'process alive after the movie')
        if p.poll() is None: p.kill()
        p.wait()
    open(os.path.join(out, 'summary.txt'), 'w').write('\n'.join(summ) + '\n')
    print(('FAIL ' if fail[0] else 'OK ') + tag)
    print('\n'.join(summ))
    return 1 if fail[0] else 0


if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == '--diff':
        sys.exit(diff(sys.argv[2], sys.argv[3]))
    sys.exit(main())
