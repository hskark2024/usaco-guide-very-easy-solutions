# Storyboard

1. **Hook — one billion multiplications**: Contrast the direct loop with roughly 30 binary steps.
2. **Break apart the exponent**: Show `13 = 8+4+1` and highlight three selected powers.
3. **Repeated squaring**: Animate `a^1 -> a^2 -> a^4 -> a^8`.
4. **Bit-by-bit walkthrough**: Trace `3^13` with result, base, and exponent columns.
5. **Loop invariant**: Keep `result * base^remaining` unchanged modulo `MOD`.
6. **Corner cases**: Show exponent zero, `0^0`, and zero to a positive power.
7. **C++ and complexity**: Map each idea to the short helper and conclude `O(log b)`.
