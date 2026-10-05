# Algorithm derivation

1. Store the direct boss of every employee as `up[0]`.
2. Compute each depth as one plus the boss's depth.
3. Build `up[k][v] = up[k-1][up[k-1][v]]` for powers of two.
4. For a query, lift the deeper employee until depths match.
5. If both employees now match, return that employee.
6. Otherwise, scan jump sizes from largest to smallest.
7. When the two jump destinations differ, move both employees there.
8. Return their now-shared direct boss.

Preprocessing turns every long climb into at most one jump per binary digit.
