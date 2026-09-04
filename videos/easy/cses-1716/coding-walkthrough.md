# C++ coding walkthrough

1. Read `children` and `apples`.
2. Set `slots = children + apples - 1`.
3. Fill `factorial[i] = factorial[i-1] * i mod MOD` through `slots`.
4. Multiply `factorial[children-1]` and `factorial[apples]` to form the denominator.
5. Raise the denominator to `MOD-2` with binary exponentiation to get its modular inverse.
6. Multiply the inverse by `factorial[slots]`, reduce modulo `MOD`, and print.
