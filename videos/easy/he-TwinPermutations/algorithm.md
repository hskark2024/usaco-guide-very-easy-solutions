# Algorithm derivation

Invert the first permutation so each value maps to its first-permutation position. Replace every value in the second permutation with that mapped position. A query now asks how many transformed entries in second positions `[L2,R2]` have values in `[L1,R1]`.

Create a `+1` event at prefix `R2` and a `-1` event at prefix `L2-1`. Sweep second positions, adding each transformed value to a Fenwick tree. Every event takes a Fenwick range sum on `[L1,R1]`. Subtract the resulting shared count from the common range length. Time is `O((n+q) log n)` and storage is `O(n+q)`.
