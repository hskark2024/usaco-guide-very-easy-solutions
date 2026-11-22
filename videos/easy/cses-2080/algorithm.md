# Algorithm derivation

For every active component:

1. Find a centroid using component collection and reverse subtree-size accumulation.
2. For each active centroid neighbor, collect a histogram of depths up to `K`.
3. Merge those histograms with one centroid count at depth zero.
4. Count unordered pairs `d + e = K` in the merged histogram.
5. Subtract the same count for every individual neighbor histogram.
6. Mark the centroid removed and decompose every remaining component.

Depth pairs use multiplication for `d < e` and `count[d] choose 2` for `d=e`.
