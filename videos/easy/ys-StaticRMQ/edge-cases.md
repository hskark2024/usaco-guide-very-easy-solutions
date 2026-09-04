# Edge-case checklist

- [x] `N = 1` creates exactly one sparse-table level.
- [x] Every official query is nonempty, so `r - l >= 1`.
- [x] The right endpoint is excluded.
- [x] Blocks are built only when their full length fits in the array.
- [x] Query blocks never extend outside `[l, r)`.
- [x] Duplicate minimum values do not affect the answer.
- [x] Values up to `10^9` fit in `int`.
- [x] Integer logs avoid floating-point rounding.
