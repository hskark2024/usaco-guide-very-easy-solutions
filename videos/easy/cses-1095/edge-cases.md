# Edge-case checklist

- [x] `0^0` returns the problem-defined value `1`.
- [x] Any base to exponent zero returns `1`.
- [x] Zero to a positive exponent returns `0`.
- [x] Base and exponent at `10^9` fit in signed 64-bit integers.
- [x] Products use 64-bit integers before reduction.
- [x] Every multiplication is reduced modulo `1,000,000,007`.
- [x] Up to 200,000 queries remain logarithmic per query.
