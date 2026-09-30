# C++ coding walkthrough

1. Read the lowercase performance string and store its length.
2. Allocate an `(N+1) x (N+1)` zero-filled table so empty intervals cost zero.
3. Loop over interval lengths from one through `N`.
4. Convert each length and left endpoint into an inclusive right endpoint.
5. Seed the answer with one inserted copy plus the suffix state.
6. Scan every possible partner to the right.
7. Skip partners with a different note.
8. Add the already-computed inside and suffix costs for equal partners.
9. Minimize the interval answer and finally print the full-string cell.
