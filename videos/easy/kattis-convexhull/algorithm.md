# Algorithm derivation

1. Sort all points lexicographically by `(x,y)`.
2. Erase duplicate points.
3. Scan forward to build a lower stack.
4. While the newest triple has cross product at most zero, pop its middle point.
5. Scan backward with the same rule for the upper stack.
6. Concatenate the chains without duplicating their shared endpoints.
7. Print the resulting counterclockwise cycle.

Popping on equality is important because Kattis forbids collinear consecutive hull edges.
