# Edge-case checklist

- One field and one-field intervals.
- Full-array addition and full-array queries.
- Minimum query across only the left or right boundary.
- Sum query after several accumulated lazy additions.
- Nested and partially overlapping updates.
- A field that begins with zero haybales.
- Distinguish positive infinity for disjoint minimum from zero for disjoint sum.
- Results larger than 32-bit signed integers.
- Official maximum `N=200,000` and `Q=100,000`.
