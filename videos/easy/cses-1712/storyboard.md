# Storyboard

1. **Hook — an impossible tower**: Show `a^(b^c)` expanding beyond any integer type.
2. **Binary exponentiation**: Break exponent `13` into `8+4+1` and square through powers of two.
3. **The exponent cycle**: Animate positive powers repeating every `MOD-1` steps.
4. **Two moduli**: Put `b^c mod (MOD-1)` in the inner box and `a^e mod MOD` in the outer box.
5. **Official example**: Trace `(3,7,1)` to reduced exponent `7` and answer `2187`.
6. **Zero corner cases**: Compare true exponent zero with a positive exponent whose residue is zero.
7. **C++ and complexity**: Walk through the reusable `mod_pow` loop and `O(log c + log MOD)` cost.
