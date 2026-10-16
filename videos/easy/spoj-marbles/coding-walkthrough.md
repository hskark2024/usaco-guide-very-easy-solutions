# C++ coding walkthrough

1. Write a reusable `binomial(n,k)` helper.
2. Shorten the loop with `k=min(k,n-k)`.
3. Keep the accumulated answer in `long long`.
4. Cast before multiplying so the operation happens in `__int128`.
5. Divide the wide temporary by the current step.
6. Convert the exact quotient back to `long long`.
7. For each case, call the helper with `N-1` and `K-1`.
8. Print each result on its own line.
