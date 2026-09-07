# C++ coding walkthrough

1. Store all queries and compute `maximum_value`.
2. Allocate a zero-filled smallest-prime-factor vector.
3. Treat an unmarked candidate as prime and label it with itself.
4. Mark still-unlabeled multiples starting from the candidate's square.
5. For each value, initialize `divisor_count` to one.
6. Divide out one prime completely and count its exponent.
7. Multiply by `exponent+1` and continue until the remainder is one.
