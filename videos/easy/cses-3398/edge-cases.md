# Edge-case checklist

- Identity permutation: all cycles have length one; the first positive reset round is one.
- One full cycle: answer is exactly `n`.
- Several equal cycle lengths: LCM includes that length only once.
- Coprime cycle lengths: the LCM multiplies them.
- Cycle lengths sharing prime factors: retain the larger prime exponent, not the sum.
- Huge true LCM: preserve exponents first and apply modulo only while building the final product.
