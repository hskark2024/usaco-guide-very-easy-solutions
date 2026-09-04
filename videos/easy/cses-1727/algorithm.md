# Algorithm derivation

1. Express an integer maximum `M` as the sum of indicators `[M >= x]` for `x = 1..k`.
2. Use linearity of expectation to obtain `E[M] = sum P(M >= x)`.
3. Use the complement `P(M >= x) = 1 - P(M < x)`.
4. A single child is below `x` with probability `(x-1)/k`.
5. Independence gives `P(M < x) = ((x-1)/k)^n`.
6. Sum `1 - ((x-1)/k)^n` for every threshold and print six decimal places.
