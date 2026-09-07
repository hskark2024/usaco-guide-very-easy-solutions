# Edge-case checklist

- [x] `N=1` produces zero operations.
- [x] A prime `N` is recognized by the leftover-factor check.
- [x] A high prime power uses triangular exponent costs.
- [x] Unused exponent copies do not incorrectly create a repeated power.
- [x] Different prime factors are counted independently.
- [x] Candidate squares use signed 64-bit arithmetic.
- [x] Trial division stops against the shrinking remaining number.
- [x] `N=10^12` stays within the input and arithmetic bounds.
