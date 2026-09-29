# Algorithm derivation

1. Give every cow one bit and allocate all `2^N` subset states.
2. Precompute each subset's height by removing its lowest set bit.
3. Define `safety[mask]` as the maximum stable safety factor for that exact subset.
4. Set `safety[0]` to a large infinity value; all other states start unreachable.
5. For every selected top cow `j`, use `previous = mask without j`.
6. Compute `candidate = min(safety[previous] - weight[j], strength[j])`.
7. Keep the largest nonnegative candidate for the subset.
8. Maximize safety over subsets whose height reaches the target.
