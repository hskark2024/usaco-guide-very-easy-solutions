# C++ coding walkthrough

1. Define the prime modulus and a binary `mod_pow` helper.
2. Read each `(a,b)` pair into a vector while updating `largest_a`.
3. Initialize both factorial arrays with ones so index zero represents `0!`.
4. Fill `factorial` forward with modular multiplication.
5. Compute the last inverse factorial once, then fill the inverse array backward.
6. For each saved query, multiply the three required table entries and print.

The saved queries let the arrays match the actual maximum input instead of always allocating for the full limit.
