# Edge-case checklist

- `N=2`: shift is one and creates the required swap.
- Odd `N`: the two circular directions are `floor(N/2)` and `ceil(N/2)`; subtree intervals still do not overlap their shifted copies.
- Two possible centroids: either one works.
- Star: many one-node centroid components.
- Chain of 100,000 nodes: iterative traversals avoid stack overflow.
- Output is a permutation with no fixed points.
- Total distance requires 64-bit storage.
