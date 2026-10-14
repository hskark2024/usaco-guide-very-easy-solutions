# Algorithm derivation

1. Sort robots by position and retain their input indices.
2. Split them by starting-coordinate parity.
3. Scan each parity group left to right.
4. Push each `R`; pair each `L` with the nearest saved `R` when possible.
5. Save `L` robots that had no preceding `R`.
6. Pair saved `L` robots from left to right using `(x1+x2)/2`.
7. Pair saved `R` robots from right to left using `(2M-x1-x2)/2`.
8. If one of each remains, use `(2M+xL-xR)/2`.
9. Leave any single final robot at `-1`.
