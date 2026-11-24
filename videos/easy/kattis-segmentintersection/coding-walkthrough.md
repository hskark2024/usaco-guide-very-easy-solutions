# C++ coding walkthrough

1. Define an integer `Point` and lexicographic ordering.
2. Write `cross` with `__int128`, then derive `sign_of` and `on_segment`.
3. Detect the all-collinear case before using line equations.
4. Insert shared original endpoints into a set to remove duplicates and obtain ordered extremes.
5. Apply the two straddle checks to noncollinear segments.
6. Solve the parametric intersection with `long double` only for a proven unique crossing.
7. Use fixed two-decimal output and replace tiny values by zero.
