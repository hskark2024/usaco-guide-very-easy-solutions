# Algorithm derivation

1. Start from `C(a,b) = a! / (b!(a-b)!)`.
2. Read the queries and let `A` be the largest `a`.
3. Precompute `fact[i] = i! mod P` for `0 <= i <= A`.
4. Use Fermat's little theorem and binary exponentiation to find `inv_fact[A] = fact[A]^(P-2) mod P`.
5. For `i` from `A` down to `1`, set `inv_fact[i-1] = inv_fact[i] * i mod P`.
6. Answer each query with `fact[a] * inv_fact[b] * inv_fact[a-b] mod P`.
