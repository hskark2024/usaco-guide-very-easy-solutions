# Algorithm derivation

1. Define `D[k]` as the number of permutations of `k` items with no fixed point.
2. Fix item `k`; it has `k-1` legal destinations.
3. For a chosen destination, partition arrangements by whether that destination's original item moves to position `k`.
4. These cases reduce to `D[k-2]` and `D[k-1]` respectively.
5. Therefore `D[k] = (k-1)(D[k-1] + D[k-2])`.
6. Keep only the two preceding values and apply modulo `M` at each step.
