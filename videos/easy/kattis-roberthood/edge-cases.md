# Edge-case checklist

- Exactly two distinct shots.
- Duplicate coordinates.
- All shots collinear.
- Horizontal or vertical hull edges.
- Several points tied for the same maximum area.
- A farthest pair using either endpoint of an edge.
- Negative coordinates.
- Maximum coordinate magnitude 1,000.
- Maximum 100,000 shots.
- Floating output tolerance of `1e-6`.
