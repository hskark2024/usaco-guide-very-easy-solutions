# Edge-case checklist

- Assignment to zero conceptually, even though official update values are positive.
- Assignment after one or many additions must erase their previous values.
- Addition after assignment must affect the assigned value.
- Nested updates where parent and child nodes hold different pending tags.
- One-element intervals.
- Full-array updates followed by small queries.
- Overlapping left and right halves around a segment-tree boundary.
- Maximum `N=Q=200,000` and sums beyond 32-bit range.
