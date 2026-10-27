# Edge-case checklist

- `N=1` and a singleton query.
- Query entirely in the left recursion half.
- Query entirely in the right recursion half.
- Query crossing the top-level midpoint.
- Query with one endpoint equal to a midpoint.
- Full-array query.
- Preserve order for a noncommutative operation.
- Values and results equal to zero.
- Public operation saturating at one billion.
- Official maximum `N=1000` and `Q=10,000`.
