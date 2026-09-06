# C++ coding walkthrough

1. Write `mod_pow(base, exponent, modulus)` so one function supports both layers.
2. Initialize the result to `1`, matching every zero exponent.
3. Multiply the result when the current exponent bit is set.
4. Square the base, reduce modulo the chosen modulus, and shift the exponent.
5. Read each `(a,b,c)` query.
6. Compute `reduced_exponent = mod_pow(b,c,MOD-1)`.
7. Detect the true-zero exponent with `b==0 && c>0`.
8. Handle a zero base explicitly; otherwise call `mod_pow(a,reduced_exponent,MOD)`.
