# Algorithm derivation

1. Convert positive groups into nonnegative groups by reserving one marble per color.
2. Apply stars and bars to obtain `C(N-1,K-1)`.
3. In the binomial helper, replace `k` with `min(k,n-k)`.
4. Initialize `result=1`.
5. For `i` from 1 through `k`, compute `result *= n-k+i`, then divide by `i`.
6. Use `__int128` for the product and return the 64-bit quotient.
