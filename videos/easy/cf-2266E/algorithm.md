# Algorithm derivation

For a single value `x`, define `dp[x]=0` when `x<=k`. Otherwise every legal solution begins with a prime divisor `p` of `x`. The first move costs one and produces `p` independent copies of `x/p`, so its complete cost is `1+p*dp[x/p]`. Minimizing this expression over distinct prime divisors is both necessary and sufficient.

All dependencies point to smaller numbers, which makes increasing `x` a topological order. Precompute smallest prime factors once up to 200000, factor each state, and skip repeated copies of a prime. The answer is `sum(dp[a[i]])`.
