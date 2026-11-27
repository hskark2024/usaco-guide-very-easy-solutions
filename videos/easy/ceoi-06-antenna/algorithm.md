# Algorithm derivation

1. Binary-search a candidate radius `R`.
2. For each household `A`, treat it as a point on the circle boundary.
3. For each `B` with distance `d <= 2R`, compute `alpha=atan2(B-A)` and `beta=acos(d/(2R))`.
4. Add the closed valid interval `[alpha-beta, alpha+beta]` twice, separated by `2*pi`.
5. Sort angular events, ordering enters before exits on a tie.
6. Sweep from a count of one for `A`; reaching `K` proves feasibility.
7. Convert the successful angle into center `A + R(cos angle, sin angle)`.
8. Keep the witness for each feasible binary-search midpoint.
