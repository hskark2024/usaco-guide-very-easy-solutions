# Edge-case checklist

- One element, both positive and negative.
- All-negative interval returns zero through the empty prefix.
- The best prefix is the entire queried interval.
- The best prefix ends in the left tree child.
- The best prefix crosses into the right tree child.
- Query begins or ends inside a segment-tree node.
- Replacing a value changes its sign.
- Merge results strictly left to right; the operation is not commutative.
- Values and accumulated sums beyond 32-bit range.
- `N=Q=200,000`.
