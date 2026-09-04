# Edge-case checklist

- [x] `k = 1` always returns exactly one.
- [x] `n = 1` matches the average `(k+1)/2`.
- [x] Threshold `x = 1` has reach probability one.
- [x] The ratio is formed in floating point, not integer division.
- [x] `long double` limits accumulated rounding error.
- [x] Output is fixed to exactly six digits after the decimal point.
