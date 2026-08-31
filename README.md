# USACO Guide Very Easy Solutions

This repository contains study notes and C++ solutions for every problem currently returned by the USACO Guide problems page with `difficulty=Very Easy`.

Each problem folder includes:

- a paraphrased problem summary
- a visualization description
- a Mermaid diagram where it helps explain the idea
- an approach analysis
- correctness and verification notes
- a linked C++ solution

The official statements remain at their original judge links. These notes intentionally avoid copying full problem statements.

## Problem Index

| ID | Source | Problem | Tags | Solution |
| --- | --- | --- | --- | --- |
| `ys-ZAlgorithm` | YS | [Z Algorithm](problems/ys-ZAlgorithm/README.md) | [Strings, Z Algorithm] | [C++](solutions/ys-ZAlgorithm.cpp) |
| `ys-StaticRangeSum` | YS | [Static Range Sum](problems/ys-StaticRangeSum/README.md) | [Prefix Sums] | [C++](solutions/ys-StaticRangeSum.cpp) |
| `usaco-807` | Bronze | [Teleportation](problems/usaco-807/README.md) | [Math] | [C++](solutions/usaco-807.cpp) |
| `usaco-715` | Silver | [Why Did the Cow Cross the Road II](problems/usaco-715/README.md) | [Prefix Sums, Sliding Window] | [C++](solutions/usaco-715.cpp) |
| `usaco-691` | Silver | [Hoof Paper Scissors](problems/usaco-691/README.md) | [Prefix Sums] | [C++](solutions/usaco-691.cpp) |
| `usaco-572` | Silver | [Breed Counting](problems/usaco-572/README.md) | [Prefix Sums] | [C++](solutions/usaco-572.cpp) |
| `spoj-DynamicConnectivity` | SPOJ | [Dynamic Connectivity](problems/spoj-DynamicConnectivity/README.md) | [LCT, Tree] | [C++](solutions/spoj-DynamicConnectivity.cpp) |
| `lc-FindPivotIndex` | LC | [Find Pivot Index](problems/lc-FindPivotIndex/README.md) | [Prefix Sums] | [C++](solutions/lc-FindPivotIndex.cpp) |
| `kattis-BasketballOneOnOne` | Kattis | [Basketball One on One](problems/kattis-BasketballOneOnOne/README.md) | [Strings] | [C++](solutions/kattis-BasketballOneOnOne.cpp) |
| `ioi-08-TypePrinter` | IOI | [Type Printer](problems/ioi-08-TypePrinter/README.md) | [Trie, Strings] | [C++](solutions/ioi-08-TypePrinter.cpp) |
| `hr-BubbleSort` | HR | [Bubble Sort](problems/hr-BubbleSort/README.md) | [Sorting] | [C++](solutions/hr-BubbleSort.cpp) |
| `hdu-5306` | HDU | [Gorgeous Sequence](problems/hdu-5306/README.md) | [SegTree Beats] | [C++](solutions/hdu-5306.cpp) |
| `cses-2079` | CSES | [Finding a Centroid](problems/cses-2079/README.md) | [Tree] | [C++](solutions/cses-2079.cpp) |
| `cses-1753` | CSES | [String Matching](problems/cses-1753/README.md) | [Strings, KMP] | [C++](solutions/cses-1753.cpp) |
| `cses-1733` | CSES | [Finding Periods](problems/cses-1733/README.md) | [Strings, Z Algorithm] | [C++](solutions/cses-1733.cpp) |
| `cses-1660` | CSES | [Subarray Sums I](problems/cses-1660/README.md) | [Two Pointers] | [C++](solutions/cses-1660.cpp) |
| `cses-1647` | CSES | [Static Range Minimum Queries](problems/cses-1647/README.md) | [Sparse Table] | [C++](solutions/cses-1647.cpp) |
| `cses-1634` | CSES | [Minimizing Coins](problems/cses-1634/README.md) | [DP, Knapsack] | [C++](solutions/cses-1634.cpp) |
| `cses-1633` | CSES | [Dice Combinations](problems/cses-1633/README.md) | [DP] | [C++](solutions/cses-1633.cpp) |
| `cses-1631` | CSES | [Reading Books](problems/cses-1631/README.md) | [Greedy] | [C++](solutions/cses-1631.cpp) |
| `coci-21-vlak` | COCI | [Vlak](problems/coci-21-vlak/README.md) | [Trie, DP, Game Theory] | [C++](solutions/coci-21-vlak.cpp) |
| `cfgym-102951B` | CF | [Studying Algorithms](problems/cfgym-102951B/README.md) | [Greedy, Sorting] | [C++](solutions/cfgym-102951B.cpp) |
| `cf-546A` | CF | [Soldier and Bananas](problems/cf-546A/README.md) | [Math] | [C++](solutions/cf-546A.cpp) |
| `cf-4A` | CF | [Watermelon](problems/cf-4A/README.md) | [Math] | [C++](solutions/cf-4A.cpp) |
| `cf-279B` | CF | [Books](problems/cf-279B/README.md) | [Two Pointers] | [C++](solutions/cf-279B.cpp) |
| `cf-231A` | CF | [Team](problems/cf-231A/README.md) | [Math] | [C++](solutions/cf-231A.cpp) |
| `cf-2257C` | CF | [Spying On The Beaver](problems/cf-2257C/README.md) | [Tree, Greedy] | [C++](solutions/cf-2257C.cpp) |
| `cf-20C` | CF | [Dijkstra](problems/cf-20C/README.md) | [Shortest Path] | [C++](solutions/cf-20C.cpp) |
| `cf-1593A` | CF | [Election](problems/cf-1593A/README.md) | [Math] | [C++](solutions/cf-1593A.cpp) |
| `cf-1560B` | CF | [Who's Opposite?](problems/cf-1560B/README.md) | [Math] | [C++](solutions/cf-1560B.cpp) |
| `cf-1020B` | CF | [Div 2 B - Badge](problems/cf-1020B/README.md) | [Functional Graph] | [C++](solutions/cf-1020B.cpp) |

## Local Verification

Compile all solutions:

```bash
python3 tests/compile_all.py
```

Run the small smoke tests:

```bash
python3 tests/smoke_tests.py
```

The smoke tests are not a replacement for judge submission, but they catch syntax errors and check representative sample-style cases.
