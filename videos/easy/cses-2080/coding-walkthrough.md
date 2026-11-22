# C++ coding walkthrough

1. `find_centroid` collects the active component and computes subtree sizes in reverse order.
2. `collect_depth_counts` uses tuples `(vertex,parent,depth)` on a vector stack.
3. It prunes when `depth > K` and grows the histogram only as needed.
4. `pairs_with_exact_sum` loops through depths only while `2*depth <= K`.
5. `decompose` subtracts each group count, merges groups, and adds the combined count.
6. Only after counting do we mark the centroid removed and recurse into each active neighbor.

Stale parent values are harmless because every component collection overwrites parents for exactly its active vertices.
