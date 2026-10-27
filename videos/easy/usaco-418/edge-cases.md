# Edge-case checklist

- One grass patch.
- Several patches at distance exactly `K` from the chosen center.
- Two transformed `u` coordinates differing by exactly `2K`.
- Negative `v=x-y` values.
- Duplicate transformed coordinates from distinct original points.
- A best square whose center has non-integer original coordinates.
- Several points entering or leaving at the same sweep coordinate.
- The maximum grass total near one billion.
- Official limits `N=100,000` and `K=2,000,000`.
