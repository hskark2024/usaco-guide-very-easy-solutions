from pathlib import Path
import subprocess
import sys

root = Path(__file__).resolve().parents[1]
build = root / "tests" / "build"

tests = {
    "ys-montmort": ("10 100\n", "0 1 2 9 44 65 54 33 96 61\n"),
    "ys-UnionFind": ("5 9\n1 0 1\n0 0 1\n1 0 1\n0 1 2\n1 0 2\n0 0 2\n1 3 4\n0 3 4\n1 3 4\n", "0\n1\n1\n0\n1\n"),
    "ys-AssociativeArray": ("9\n1 8\n0 8 12\n1 8\n0 8 99\n1 8\n0 1000000000000000000 7\n1 1000000000000000000\n0 3 0\n1 3\n", "0\n12\n99\n7\n0\n"),
    "ys-StaticRMQ": ("6 5\n7 2 5 1 9 3\n0 1\n0 3\n2 5\n3 6\n0 6\n", "7\n2\n1\n1\n1\n"),
    "ys-SortPointsByArgument": ("5\n-1 0\n0 1\n1 0\n0 -1\n0 0\n", "0 -1\n1 0\n0 0\n0 1\n-1 0\n"),
    "ys-DEPQ": ("4 10\n-3 0 1 3\n0 3\n2\n2\n0 -2\n0 1\n1\n1\n2\n1\n2\n", "3\n3\n-3\n-2\n1\n0\n1\n"),
    "cses-1079": ("3\n5 3\n8 1\n9 5\n", "10\n8\n126\n"),
    "cses-1716": ("3 2\n", "6\n"),
    "cses-1727": ("2 3\n", "2.444444\n"),
    "cses-1715": ("aabac\n", "20\n"),
    "cf-888D": ("5 4\n", "76\n"),
    "cf-1462E2": ("4\n4 3 2\n1 2 4 3\n4 2 1\n1 1 1 1\n1 1 1\n1\n10 4 3\n5 6 1 3 2 9 8 1 2 4\n", "2\n6\n1\n20\n"),
    "cses-1712": ("3\n3 7 1\n15 2 2\n3 4 5\n", "2187\n50625\n763327764\n"),
    "cf-1279D": ("2\n2 2 1\n1 1\n", "124780545\n"),
    "cf-2211D": ("3\n3\n0 0 0\n5\n22 24 10 1 0\n10\n130 585 1560 2730 3276 2730 1560 585 130 13\n", "0 0 0\n7 7 7 1 0\n13 13 13 13 13 13 13 13 13 13\n"),
    "cses-1095": ("6\n3 4\n2 8\n123 123\n0 0\n0 9\n7 0\n", "81\n256\n921450052\n1\n0\n1\n"),
    "cses-1713": ("7\n16\n17\n18\n1\n36\n999983\n1000000\n", "5\n2\n6\n1\n9\n2\n49\n"),
    "ac-DivGame": ("997764507000\n", "7\n"),
    "cf-1514C": ("5\n", "3\n1 2 3\n"),
    "cf-1225D": ("6 3\n1 3 9 8 24 1\n", "5\n"),
    "cf-1536C": ("5\n3\nDDK\n6\nDDDDDD\n4\nDKDK\n1\nD\n9\nDKDKDDDDK\n", "1 2 1\n1 2 3 4 5 6\n1 1 1 2\n1\n1 1 1 2 1 2 1 1 3\n"),
    "spoj-etm": ("7\n1\n2\n5\n8\n12\n36\n1000000\n", "1\n1\n4\n4\n4\n12\n400000\n"),
    "cses-3398": ("8\n5 3 2 6 4 1 8 7\n", "4\n"),
    "spoj-najpwg": ("6\n0\n1\n2\n4\n5\n10\n", "Case 1: 0\nCase 2: 0\nCase 3: 1\nCase 4: 4\nCase 5: 5\nCase 6: 23\n"),
    "ac-frog1": ("4\n10 30 40 20\n", "30\n"),
    "cf-1418C": ("6\n8\n1 0 1 1 0 1 1 1\n5\n1 1 1 1 0\n7\n1 1 1 1 0 0 1\n6\n1 1 1 1 1 1\n1\n1\n1\n0\n", "2\n2\n2\n2\n1\n0\n"),
    "cf-1082E": ("3 2\n6 2 6\n", "2\n"),
    "usaco-694": ("5 1\nP\nP\nH\nP\nS\n", "4\n"),
    "usaco-993": ("3 3 1\n0 10 20\n1 2\n2 3\n3 1\n", "24\n"),
    "cses-1635": ("3 9\n2 3 5\n", "8\n"),
    "cses-1636": ("3 9\n2 3 5\n", "3\n"),
    "ac-subsetSumQueries": ("15 10\n+ 5\n+ 2\n+ 3\n- 2\n+ 5\n+ 10\n- 3\n+ 1\n+ 3\n+ 3\n- 5\n+ 1\n+ 7\n+ 4\n- 3\n", "0\n0\n1\n0\n1\n2\n2\n2\n2\n2\n1\n3\n5\n8\n5\n"),
    "cses-1158": ("4 10\n4 8 5 3\n5 12 8 1\n", "13\n"),
    "cses-1745": ("4\n4 2 5 2\n", "9\n2 4 5 6 7 8 9 11 13\n"),
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
