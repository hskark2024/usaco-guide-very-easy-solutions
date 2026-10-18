# Edge-case checklist

- `k=n`, so every possible value already satisfies the limit.
- Values equal to `k` cost zero.
- Prime values above `k` can split directly into ones in one operation.
- Prime powers create the deepest branching recurrence.
- Numbers with several distinct prime divisors require taking a true minimum.
- Duplicate original values add duplicate costs.
- The final sum requires 64-bit arithmetic.
- Repeated prime factors must not cause incorrect extra choices.
