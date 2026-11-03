# C++ coding walkthrough

1. Store jump powers with one-based indices.
2. Choose block size `floor(sqrt(N)) + 1`.
3. Maintain `next_outside`, `jump_count`, and `last_inside` arrays.
4. Rebuild a block from its right edge toward its left edge.
5. Splice a same-block jump onto its destination's summary.
6. After an update, rebuild only the containing block.
7. For a query, follow summaries until the destination exceeds `N`.
