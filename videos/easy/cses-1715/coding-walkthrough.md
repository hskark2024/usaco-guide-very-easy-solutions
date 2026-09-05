# C++ coding walkthrough

1. Read the input string and create a zero-initialized `array<int, 26>`.
2. Increment the slot for each letter to record all multiplicities.
3. Allocate `factorial` through the string length and fill it from left to right.
4. Multiply `factorial[count]` for all 26 letters into `denominator`.
5. Call binary exponentiation with exponent `MOD-2` to invert the denominator.
6. Multiply `factorial[n]` by the inverse, reduce modulo `MOD`, and print.
7. Use comments to preserve the counting meaning of the numerator and denominator instead of treating the formula as magic.
