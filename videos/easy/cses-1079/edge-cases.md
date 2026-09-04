# Edge-case checklist

- [x] `a = b = 0` uses `0! = 1`.
- [x] `b = 0` returns one.
- [x] `b = a` returns one.
- [x] The precomputation stops at the largest observed `a`.
- [x] Products use 64-bit integers before taking the modulus.
- [x] Up to `100,000` queries are buffered without recomputing tables.
- [x] Every answer is printed on its own line.
