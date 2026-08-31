from pathlib import Path
import subprocess
import sys

root = Path(__file__).resolve().parents[1]
build = root / "tests" / "build"

tests = {
    "cf-4A": ("8\n", "YES\n"),
    "cf-546A": ("3 17 4\n", "13\n"),
    "cfgym-102951B": ("6 15\n4 3 8 4 7 3\n", "4\n"),
    "ys-StaticRangeSum": ("5 3\n1 2 3 4 5\n0 5\n1 3\n2 2\n", "15\n5\n0\n"),
    "ys-ZAlgorithm": ("ababa\n", "5 0 3 0 1\n"),
    "cf-1593A": ("3\n0 0 0\n10 75 15\n13 13 17\n", "1 1 1\n66 0 61\n5 5 0\n"),
    "cf-1560B": ("4\n2 6 4\n4 3 2\n6 2 4\n2 4 10\n", "8\n-1\n8\n-1\n"),
    "cf-231A": ("3\n1 1 0\n1 1 1\n1 0 0\n", "2\n"),
    "cf-279B": ("4 5\n3 1 2 1\n", "3\n"),
    "cses-1633": ("3\n", "4\n"),
    "cses-1634": ("3 11\n1 5 7\n", "3\n"),
    "cses-1660": ("5 7\n2 4 1 2 7\n", "3\n"),
    "cses-1733": ("ababab\n", "2 4 6\n"),
    "cses-1753": ("aaaaa\naa\n", "4\n"),
    "cses-1631": ("3\n2 8 3\n", "16\n"),
    "kattis-BasketballOneOnOne": ("A2B1A2B2A1B2A2B1A2B2A1\n", "A\n"),
    "lc-FindPivotIndex": ("6\n1 7 3 6 5 6\n", "3\n"),
    "usaco-807": ("3 10 8 2\n", "3\n"),
    "cf-1020B": ("5\n2 3 4 5 3\n", "3 3 3 4 5\n"),
    "spoj-DynamicConnectivity": ("5 11\nconn 1 5\nadd 1 2\nadd 1 3\nadd 3 4\nadd 5 4\nconn 1 5\nrem 4 5\nconn 1 5\nrem 3 4\nadd 3 5\nconn 1 5\n", "NO\nYES\nNO\nYES\n"),
    "usaco-715": ("5 3 2\n2\n4\n", "1\n"),
    "usaco-691": ("5\nH\nP\nS\nH\nP\n", "3\n"),
    "usaco-572": ("5 3\n1\n2\n3\n2\n1\n1 5\n2 4\n3 3\n", "2 2 1\n0 2 1\n0 0 1\n"),
    "cses-1647": ("5 3\n5 2 4 1 3\n1 5\n2 3\n4 4\n", "1\n2\n1\n"),
    "cses-2079": ("4\n1 2\n1 3\n1 4\n", "1\n"),
    "hr-BubbleSort": ("3\n3 2 1\n", "Array is sorted in 3 swaps.\nFirst Element: 1\nLast Element: 3\n"),
    "hdu-5306": ("1\n5 5\n1 5 3 4 2\n2 1 5\n1 2 4\n0 2 4 3\n1 1 5\n2 2 4\n", "15\n5\n3\n9\n"),
    "cf-20C": ("5 6\n1 2 2\n2 5 5\n1 3 4\n3 4 1\n4 5 1\n2 3 1\n", "1 2 3 4 5\n"),
    "cf-2257C": ("1\n3\n1 1\n3\n1 2 3\n", "2 2 3\n"),
    "coci-21-vlak": ("1\na\n1\nb\n", "Nina\n"),
    "ioi-08-TypePrinter": ("1\nab\n", "3\na\nb\nP\n"),
}

failed = []
for stem, (inp, expected) in tests.items():
    exe = build / stem
    if not exe.exists():
        failed.append((stem, "missing executable; run compile_all.py first"))
        continue
    res = subprocess.run([str(exe)], input=inp, capture_output=True, text=True)
    if res.stdout != expected:
        failed.append((stem, f"expected {expected!r}, got {res.stdout!r}, stderr {res.stderr!r}"))
    else:
        print(f"passed {stem}")

if failed:
    for stem, err in failed:
        print(f"\nFAILED {stem}: {err}", file=sys.stderr)
    sys.exit(1)
