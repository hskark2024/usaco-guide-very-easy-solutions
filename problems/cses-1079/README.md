# Binomial Coefficients

- Source: CSES
- USACO Guide ID: `cses-1079`
- Difficulty at selection: Easy
- Original problem: [https://cses.fi/problemset/task/1079](https://cses.fi/problemset/task/1079)
- Tags: Combinatorics, Modular Arithmetic
- Solution: [`../../solutions/cses-1079.cpp`](../../solutions/cses-1079.cpp)

## Problem Summary

Answer up to `100,000` queries asking for the number of ways to choose `b` objects from `a` objects. Every answer is needed modulo `1,000,000,007`, and `a` can be as large as one million.

This is a paraphrase for study notes. Use the original link for the official statement and constraints.

## Visualization Description

Imagine `a` labeled cards in a row. A query asks how many different groups of exactly `b` cards can be circled. The factorial formula counts all orderings, then divides away the order inside the chosen and unchosen groups. Under modular arithmetic, division becomes multiplication by modular inverses.

```mermaid
flowchart LR
  A[Read all queries] --> B[Find largest a]
  B --> C[Precompute factorials]
  C --> D[Build inverse factorials backward]
  D --> E[For each a b query]
  E --> F[a factorial times inverse b factorial times inverse a minus b factorial]
```

## Approach

For prime modulus `P = 1,000,000,007`, Fermat's little theorem gives `x^(-1) = x^(P-2) mod P` for nonzero `x`. Precompute `fact[i] = i! mod P` through the largest `a` in the input. Compute `inv_fact[max]` with binary exponentiation and recover every smaller inverse factorial with:

`inv_fact[i - 1] = inv_fact[i] * i mod P`.

Then each query is answered in constant time:

`C(a,b) = fact[a] * inv_fact[b] * inv_fact[a-b] mod P`.

## Correctness

The ordinary combination identity is `C(a,b) = a! / (b!(a-b)!)`. All factorial arguments are below `P`, so their residues are nonzero and have modular inverses. `inv_fact[max]` is the inverse of `max!` by Fermat's little theorem. If `inv_fact[i]` is the inverse of `i!`, multiplying it by `i` gives the inverse of `(i-1)!`; therefore the backward pass computes every inverse factorial correctly. Substituting those inverses into the combination identity proves every reported answer.

## Complexity

- Precomputation: `O(A + log P)`, where `A` is the largest queried `a`
- Each query: `O(1)`
- Extra space: `O(A + Q)`

## Verification

The smoke test uses the official three-query example. Random verification compares all `C(a,b)` for small `a` against Pascal's triangle, including `b = 0`, `b = a`, and repeated queries.
