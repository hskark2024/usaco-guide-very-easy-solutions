# C++ coding walkthrough

- Read all limits first and find the largest.
- Initialize `phi[x] = x` and run the Euler totient sieve.
- Use a `long long` prefix array because pair counts grow quadratically.
- For each `y`, add `y - phi[y]` to the previous prefix.
- Print `Case k: answer` using one-based case numbering.

The update includes equal pairs such as `(4,4)`, because `x` ranges all the way through `y`. It excludes duplicates such as both `(2,4)` and `(4,2)` by always requiring `x <= y`.
