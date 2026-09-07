# Edge-case checklist

- [x] Value `1` has one divisor and an empty factorization.
- [x] A prime value has exponent one and two divisors.
- [x] A perfect square has an odd divisor count.
- [x] Repeated prime factors are consumed as one exponent group.
- [x] The table includes the maximum value itself.
- [x] Candidate squares use 64-bit multiplication.
- [x] `1,000,000` produces `49` divisors.
- [x] 100,000 queries reuse one sieve.
