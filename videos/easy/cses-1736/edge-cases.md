# Edge-case checklist

- A one-position update adds exactly one.
- An update that begins after index one still restarts its progression at one.
- Full-array and suffix updates.
- Many overlapping progressions with different starting positions.
- Queries that exactly match a lazily tagged node.
- Queries that force tags into both children.
- Initial values and accumulated sums near 64-bit ranges.
- `N=Q=200,000` for recursion depth, memory, and speed.
