# Algorithm derivation

1. Root the tree and record `parent` and `depth` iteratively.
2. Build `up[j][v]`, the ancestor `2^j` edges above `v`.
3. For each query, find `lca(start, finish)`.
4. Let `A` and `B` be the start-to-LCA and LCA-to-finish lengths.
5. Return the finish if energy is at least `A+B`.
6. If energy is at most `A`, climb from the start by energy.
7. Otherwise climb from the finish by `A+B-energy`.
