# Edge-case checklist

- [x] `b=0, c>0` makes the true outer exponent zero.
- [x] `b=0, c=0` uses the stated inner `0^0=1` convention.
- [x] `a=0` with a positive exponent returns zero directly.
- [x] `a=0` with a zero exponent returns one.
- [x] `c=0` makes the inner exponent equal to one for every `b`.
- [x] Multiplication uses 64-bit integers before taking the modulus.
- [x] The inner and outer powers use `MOD-1` and `MOD`, respectively.
- [x] Up to 100,000 queries remain logarithmic per query.
