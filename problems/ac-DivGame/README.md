# Div Game

- Source: AtCoder
- USACO Guide ID: `ac-DivGame`
- Difficulty at selection: Easy
- Original problem: [https://atcoder.jp/contests/abc169/tasks/abc169_d](https://atcoder.jp/contests/abc169/tasks/abc169_d)
- Tags: Prime Factorization, Greedy
- Solution: [`../../solutions/ac-DivGame.cpp`](../../solutions/ac-DivGame.cpp)

## Problem Summary

Starting with `N`, repeatedly divide it by a prime power that currently divides it. The same numeric prime power may not be selected twice. Find the largest possible number of operations for `N` up to `10^12`.

This is a paraphrase for study notes. Use the original link for the official statement and constraints.

## Visualization Description

For one prime factor with exponent `e`, draw `e` identical tokens. Group one token for `p^1`, then two tokens for `p^2`, then three for `p^3`, continuing while enough tokens remain. Each completed staircase step is one legal, distinct operation.

```mermaid
flowchart LR
  A[Factor N] --> B[Take exponent e of one prime]
  B --> C[Spend 1 for p to the 1]
  C --> D[Spend 2 for p to the 2]
  D --> E[Spend 3 for p to the 3]
  E --> F[Stop when the next cost does not fit]
  F --> G[Add steps over all primes]
```

## Approach

Factor `N`. Consider one prime whose exponent is `e`. Distinct powers chosen for this prime have distinct positive exponents, and their total exponent cannot exceed `e`. To maximize how many fit, choose the cheapest possible exponent costs: `1,2,3,...`. Repeatedly subtract the next cost until it no longer fits, then repeat independently for every prime factor.

Trial division through the shrinking square root is fast enough for `N <= 10^12`. Any factor left afterward is a prime with exponent one and contributes one final operation.

## Correctness

For one prime, any `k` distinct positive powers have `k` distinct positive exponents. Their sum is at least `1+2+...+k`, so `k` operations are impossible if this triangular number exceeds the available exponent `e`. Conversely, when the triangular number fits, choosing `p^1,p^2,...,p^k` is legal and achieves `k` operations. The greedy loop finds exactly the largest such `k`. Prime factorizations use disjoint exponent supplies, so choices for different primes do not interfere; summing their optimal counts is globally optimal.

## Complexity

- Time: `O(sqrt(N))` in the worst case for factorization
- Extra space: `O(1)`

## Verification

The smoke test covers the official examples `24`, `1`, `64`, a large prime, and a large composite. A separate exhaustive verifier explores every legal sequence of distinct prime-power moves for small `N` and compares its optimum with the C++ result.
