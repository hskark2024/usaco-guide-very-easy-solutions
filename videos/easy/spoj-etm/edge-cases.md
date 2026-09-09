# Edge-case checklist

- `n = 1`: output is the explicitly defined value `1`.
- Prime `n`: only `n` itself fails the coprime test, so the answer is `n - 1`.
- Prime power: the prime factor must update the entry once, not once per exponent.
- Many distinct prime factors: each distinct prime applies one multiplicative correction.
- Repeated queries: precomputation is shared and results remain identical.
- Maximum query: table bounds include the endpoint.
