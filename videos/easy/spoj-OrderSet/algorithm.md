# Algorithm derivation

Offline coordinate compression maps every relevant numeric argument to its rank without changing comparisons. Store set membership as a zero-or-one frequency array represented by a Fenwick tree.

- `I` and `D`: update one compressed index if membership changes.
- `C x`: `lower_bound(x)` identifies how many coordinate positions are strictly below `x`; query that prefix.
- `K k`: if the total count is at least `k`, Fenwick binary lifting finds the first prefix whose count reaches `k`.

Preprocessing and all operations fit `O(Q log Q)` time and `O(Q)` space.
