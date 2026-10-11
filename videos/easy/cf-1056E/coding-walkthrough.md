# C++ coding walkthrough

1. Count pattern symbols and normalize the more frequent one to `0`.
2. Construct the `DoubleHash` prefix and power vectors.
3. Enumerate `length_zero` while leaving room for all one blocks.
4. Check divisibility before computing `length_one`.
5. Store one learned hash pair per symbol.
6. Advance the target position by the current symbol's block length.
7. Reject mismatched repeats and identical replacements.
8. Print the 64-bit answer.
