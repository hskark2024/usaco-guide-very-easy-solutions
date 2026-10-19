# Edge-case checklist

- One function and one query.
- A range containing exactly one function.
- Array size is not a power of two.
- Identity functions `(1,0)` appear in the input.
- Constant functions have multiplier zero.
- Coefficients and `x` are close to the modulus.
- The same position is updated repeatedly.
- Composition order is tested with non-commuting functions.
