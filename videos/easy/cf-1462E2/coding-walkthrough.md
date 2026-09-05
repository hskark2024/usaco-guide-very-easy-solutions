# C++ coding walkthrough

1. Precompute factorials through `200,000` before reading the test cases.
2. Invert the largest factorial with binary exponentiation and fill inverse factorials backward.
3. Define a combination helper that returns zero for impossible choices.
4. Read and sort each test-case array.
5. Keep a `right` pointer outside the loop over `left`.
6. Advance `right` while `values[right]-values[left] <= k`.
7. Add `choose(right-left-1, m-1)` because `left` itself is already selected.
8. Print the result modulo `MOD` after processing all possible minimum indices.
