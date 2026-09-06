# Algorithm derivation

1. Set `MOD = 1,000,000,007`, which is prime.
2. For every query, compute `e = b^c mod (MOD-1)` with binary exponentiation.
3. Recognize that the true exponent is zero exactly when `b=0` and `c>0`.
4. If `a=0` and the true exponent is positive, output `0` directly.
5. Otherwise compute `a^e mod MOD` with the same binary-exponentiation routine.
6. This works for positive `a` because Fermat's little theorem makes exponents periodic modulo `MOD-1`.
7. It works for zero cases because they are decided from the true exponent rather than only its residue.
