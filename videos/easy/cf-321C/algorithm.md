# Algorithm derivation

1. The desired labels need higher-ranked separators between equal-ranked vertices.
2. A centroid is a separator whose remaining components are all at most half as large.
3. Choose the current component's centroid and label it with the current decomposition level.
4. Remove that centroid and independently process every resulting component at the next level.
5. Convert level `0` to `A`, level `1` to `B`, and so on.

Each vertex can appear in one active component per level, and component sizes halve between levels, giving `O(N log N)` total work.
