# Algorithm derivation

1. Store `ways[s]`, the number of subsets of current physical balls totaling `s`, for `0 <= s <= K`.
2. Initialize `ways[0] = 1` for the empty subset.
3. For `+ x`, scan `s` from `K` down to `x` and add `ways[s-x]` into `ways[s]`.
4. For `- x`, scan `s` from `x` up to `K` and subtract `ways[s-x]` from `ways[s]`.
5. Normalize every update modulo `998244353`.
6. Ignore table updates when `x > K`, then print `ways[K]` after every query.

Addition multiplies the subset generating function by `1 + z^x`; removal divides out the same factor. Time is `O(QK)` and space is `O(K)`.
