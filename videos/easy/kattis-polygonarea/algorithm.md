# Algorithm derivation

1. Initialize `twice_signed_area = 0`.
2. For every vertex `i`, let `j=(i+1) mod N`.
3. Add `x_i*y_j - y_i*x_j`.
4. Print `CCW` when the sum is positive and `CW` when it is negative.
5. Let `magnitude = abs(sum)`.
6. Print `magnitude/2`, followed by `.0` if even or `.5` if odd.

The shoelace theorem proves the sum equals twice the signed area of the closed polygon.
