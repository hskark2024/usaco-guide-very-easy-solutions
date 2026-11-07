# Algorithm derivation

1. A literal query follows `parent` exactly `k` times, but its cost depends on `k`.
2. Precompute `up[v][j]`, the employee reached after `2^j` manager links.
3. The recurrence is `up[v][j] = up[up[v][j-1]][j-1]`: two equal half-jumps form the full jump.
4. Give node `0` a self-loop so missing ancestors propagate safely.
5. Decompose `k` into set bits and apply the corresponding jumps to the current employee.
6. Convert a final `0` to `-1`.

The official bound `k <= n <= 200,000` needs fewer than 30 stored levels.
