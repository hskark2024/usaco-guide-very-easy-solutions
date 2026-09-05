# Edge-case checklist

- [x] A one-character string has exactly one arrangement.
- [x] All-equal letters divide `n!` by the same `n!` and return one.
- [x] All-distinct letters have a denominator of one and return `n!`.
- [x] Letters with zero frequency contribute `0! = 1`.
- [x] The maximum length of one million stays below the prime modulus.
- [x] Every modular multiplication uses a 64-bit integer.
- [x] The solution never performs ordinary integer division after reducing modulo `P`.
