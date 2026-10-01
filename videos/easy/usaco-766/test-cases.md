# Test-case walkthroughs

In the official sample, barn `4` is fixed to color `3` and is a leaf of the center. The center has two colors available. Each of the other two leaves then has two choices, producing `2 * 2 * 2 = 8` valid paintings.

A single unfixed barn has `3` paintings; a fixed one has `1`. If two adjacent barns are fixed to the same color, the answer is `0`. With no fixed barns, any `N`-vertex tree has `3 * 2^(N-1)` colorings.
