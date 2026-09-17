# C++ Coding Walkthrough

1. Read `Q` and `K`, then allocate `ways` with exactly `K+1` entries.
2. Set `ways[0] = 1` for the empty subset.
3. On `+ x`, scan from `K` down to `x`, add `ways[s-x]`, and reduce modulo `998244353`.
4. On `- x`, scan from `x` up to `K`, subtract the already recovered `ways[s-x]`, and normalize negative values.
5. Skip both loops when `x > K`; positive values above the target cannot help reach it.
6. Print `ways[K]` after the query. The code comments explain the generating-function identity and both scan directions.
