# Algorithm derivation

1. Put boundaries at the first and last remaining characters.
2. Grow a prefix candidate and equal-length suffix candidate one character at a time.
3. Update two forward hashes for each candidate without rebuilding strings.
4. At a double-hash match, confirm the two chunks byte for byte.
5. Accept the first equal pair, add two chunks, and move both boundaries inward.
6. Reset the temporary hashes for the new interior.
7. If no pair fits before the center, count the whole remainder as one chunk.
8. Repeat for every test case.

Choosing the shortest available matching border leaves the greatest opportunity for more inner pairs.
