# Algorithm derivation

Represent a tree by `1` and an empty cell by `0`. A 2D Fenwick tree supports a point delta and a prefix-rectangle sum in `O(log^2 N)`.

Compute an inclusive rectangle with four prefixes: `P(y2,x2)-P(y1-1,x2)-P(y2,x1-1)+P(y1-1,x1-1)`. Keep the literal grid so a toggle chooses `+1` or `-1`.

Build the initial tree in `O(N^2)` by propagating raw cells first along `x` and then along `y`. Memory is `O(N^2)`.
