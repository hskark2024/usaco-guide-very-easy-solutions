# Candy Lottery

- Source: CSES
- USACO Guide ID: `cses-1727`
- Difficulty at selection: Easy
- Original problem: [https://cses.fi/problemset/task/1727](https://cses.fi/problemset/task/1727)
- Tags: Probability, Expected Value
- Solution: [`../../solutions/cses-1727.cpp`](../../solutions/cses-1727.cpp)

## Problem Summary

Each of `n` children independently receives a uniformly random whole-number candy count from `1` through `k`. Compute the expected largest count among the children and print it to six decimal places.

This is a paraphrase for study notes. Use the original link for the official statement and constraints.

## Visualization Description

Instead of trying to list every possible group of rolls, stack `k` horizontal threshold lines. The maximum contributes one unit for every threshold it reaches. At threshold `x`, it contributes exactly when at least one child has `x` or more candies.

```mermaid
flowchart TD
  A[Threshold x] --> B[All children are below x?]
  B -->|yes| C[Probability is ((x minus 1) divided by k) to power n]
  B -->|no| D[Maximum reaches x]
  C --> E[Reach probability is one minus that value]
  D --> E
  E --> F[Sum over x equals 1 through k]
```

## Approach

For an integer-valued random variable between `1` and `k`, the tail-sum identity says:

`E[max] = sum from x=1 to k of P(max >= x)`.

One child is below `x` with probability `(x-1)/k`. Independence makes the probability that all `n` children are below `x` equal to `((x-1)/k)^n`. Therefore:

`E[max] = sum from x=1 to k of (1 - ((x-1)/k)^n)`.

Evaluate this directly with `long double`.

## Correctness

For any outcome whose maximum is `M`, the indicators `[M >= 1]` through `[M >= k]` contain exactly `M` ones. Thus `M` equals their sum. Linearity of expectation converts that sum into the sum of the probabilities `P(M >= x)`. The complement event has every child below `x`; independence gives probability `((x-1)/k)^n`. Substituting its complement into the tail sum proves the algorithm returns the expected maximum.

## Complexity

- Time: `O(k log n)` with the library power routine
- Extra space: `O(1)`

## Verification

The smoke test uses the official `2 3` example. A deterministic verifier enumerates every outcome for small `n` and `k`, calculates its exact average maximum, and compares it with the program within the printed precision. It also checks `n = 1` and `k = 1`.
