# C++ coding walkthrough

1. Define the prime modulus as a 64-bit constant.
2. Write `mod_pow(base, exponent)` and reduce the initial base.
3. Initialize `result` to `1`.
4. Use `exponent & 1` to detect the current set bit.
5. Multiply the selected base power into `result` modulo `MOD`.
6. Square the base and shift the exponent right.
7. Read every independent query and print the helper's return value.
