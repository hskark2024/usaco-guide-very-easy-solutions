# Distributing Apples

- Source: CSES
- USACO Guide ID: `cses-1716`
- Difficulty at selection: Easy
- Original problem: [https://cses.fi/problemset/task/1716](https://cses.fi/problemset/task/1716)
- Tags: Combinatorics, Stars and Bars
- Solution: [`../../solutions/cses-1716.cpp`](../../solutions/cses-1716.cpp)

## Problem Summary

Count how many ways `m` identical apples can be shared among `n` distinct children. A child may receive no apples. Return the count modulo `1,000,000,007`.

This is a paraphrase for study notes. Use the original link for the official statement and constraints.

## Visualization Description

Draw every apple as a star and place `n - 1` divider bars among them. The number of stars before the first bar is child one's share, the number between bars is each middle share, and the number after the last bar is the final share. Adjacent bars represent a child receiving zero apples.

```mermaid
flowchart LR
  A[m apple stars] --> B[Add n minus 1 divider bars]
  B --> C[m plus n minus 1 total positions]
  C --> D[Choose the divider positions]
  D --> E[Combination m plus n minus 1 choose n minus 1]
```

For `n = 3` and `m = 4`, the arrangement `**| |**` represents shares `(2, 0, 2)`.

## Approach

The stars-and-bars bijection turns every distribution into a sequence of `m` stars and `n - 1` bars. Choose which `n - 1` of the `m + n - 1` positions hold bars:

`answer = C(m + n - 1, n - 1)`.

Precompute factorials through `m + n - 1`. Because the modulus is prime and the maximum factorial argument is below it, divide by the two factorials using a modular inverse found with binary exponentiation.

## Correctness

Given a distribution, writing each child's apples as stars and separating consecutive children with one bar creates exactly one stars-and-bars sequence. Conversely, counting the stars in each section of any such sequence creates exactly one valid distribution; empty sections allow zero apples. These operations undo each other, so the mapping is a bijection. There are `C(m+n-1, n-1)` choices for the bar positions, and the modular factorial calculation evaluates that combination correctly.

## Complexity

- Time: `O(n + m + log MOD)`
- Extra space: `O(n + m)`

## Verification

The smoke test uses the official `3 2` example. An exhaustive verifier enumerates small nonnegative distributions and compares their count with the solution for several values, including one child and one apple.
