# Edge-case checklist

- [x] Value `1` has an empty signature.
- [x] A value already equal to a perfect `k`-th power has an empty signature.
- [x] Two empty signatures correctly form a valid pair.
- [x] Exponents larger than `k` are reduced modulo `k`.
- [x] Missing primes cannot accidentally match because the whole vector is the key.
- [x] Equal array values at different indices are counted separately.
- [x] Only earlier values are counted, preventing double counting.
- [x] The answer uses 64-bit arithmetic for up to roughly five billion pairs.
