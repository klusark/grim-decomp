"""Writes the PR comment of the clean-room tests (markdown) from run.py's output: the tests that fail, each with the
first lines of what differs, and the tests that crashed or hung the rebuilt exe.

    python cleanroom_comment.py <cleanroom.txt> <outcome of the tests step: success|failure|...> <run URL> <out.md>
"""
import re
import sys

MARKER = "<!-- grim-decomp cleanroom -->"
DETAIL_LINES = 8     # (of each failing test, in the comment; the step summary and the logs artifact have the rest)
MAX_TESTS = 60       # (a comment is at most 65536 characters)


def parse(lines):
    """(the failing tests as [(name, status, detail lines)], the tests that crashed or hung, the count line or None)"""
    failed, crashed, total = [], [], None
    cur = None
    for l in lines:
        m = re.match(r"^(\S+)\s+(DIFF|REGRESSION) \((\d+)\)\s*$", l) or re.match(r"^(\S+)\s+(MISSING)\s*$", l)
        if m:
            cur = (m.group(1), m.group(2), [])
            failed.append(cur)
            continue
        if cur and l.startswith("  "):
            cur[2].append(l)
            continue
        cur = None
        if l.startswith("crashed or hung the rebuilt exe: "):
            crashed = [n.strip() for n in l.split(": ", 1)[1].split(",") if n.strip()]
        elif re.match(r"^\d+ of \d+ tests differ", l):
            total = l.strip()
    return failed, crashed, total


def main(path, outcome, url, out):
    try:
        lines = open(path, encoding="utf-8-sig", errors="replace").read().splitlines()
    except OSError:
        lines = []
    failed, crashed, total = parse(lines)
    md = [MARKER]
    if outcome == "success":
        md.append("### :white_check_mark: Clean-room tests pass")
        if total:
            md.append(total)
    else:
        md.append("### :x: Clean-room tests fail")
        if total:
            md.append(total)
        if crashed:
            md.append("\n**Crashed or hung the rebuilt exe (%d):** %s" % (len(crashed), ", ".join("`%s`" % n for n in crashed)))
        if failed:
            md.append("\n**Differ from the original (%d):** %s" %
                      (len(failed), ", ".join("`%s`" % n for n, _, _ in failed[:MAX_TESTS]) +
                       (" and %d more" % (len(failed) - MAX_TESTS) if len(failed) > MAX_TESTS else "")))
            md.append("")
            for name, status, detail in failed[:MAX_TESTS]:
                body = detail[:DETAIL_LINES] + (["  ... %d more" % (len(detail) - DETAIL_LINES)] if len(detail) > DETAIL_LINES else [])
                md.append("<details><summary><code>%s</code> %s%s</summary>\n\n```\n%s\n```\n</details>" %
                          (name, status, " (%d differences)" % len(detail) if status != "MISSING" else "",
                           "\n".join(l[:300] for l in body) or "(missing from the decomp's log)"))
        if not failed and not crashed:
            # (run.py stopped before the comparison, or failed some other way: the end of its output)
            md.append("\nNo failing test was found in the output; its last lines:\n\n```\n%s\n```" %
                      ("\n".join(l[:300] for l in lines[-30:]) or "(no output)"))
    md.append("\n[Run, step summary and logs](%s)" % url)
    open(out, "w", encoding="utf-8").write("\n".join(md) + "\n")


if __name__ == "__main__":
    main(*sys.argv[1:5])
