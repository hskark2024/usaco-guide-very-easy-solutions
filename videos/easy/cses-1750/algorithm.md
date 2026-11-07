# Algorithm derivation

1. Treat the teleporter mapping as a function `f(v)`.
2. Store `jump[v][j] = f^(2^j)(v)`, the result of applying `f` exactly `2^j` times.
3. Level zero is the input mapping.
4. Compose two half-length applications: `jump[v][j] = jump[jump[v][j-1]][j-1]`.
5. Decompose each query count into binary and compose the selected table entries.

No cycle detection is necessary because function composition remains correct on every part of a functional graph. Thirty levels cover `k <= 10^9`.
