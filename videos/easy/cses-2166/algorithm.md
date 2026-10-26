# Algorithm derivation

For each interval store its total sum and its best prefix sum, allowing the empty prefix. If a node is `L` followed by `R`, its total is `L.sum+R.sum`. Its best prefix is either inside `L`, or all of `L` plus the best prefix of `R`, giving `max(L.best, L.sum+R.best)`.

A leaf `x` stores `(x,max(0,x))`. Point updates rebuild one root-to-leaf path. Range queries merge covered nodes in left-to-right order with `(0,0)` as the identity.

The tree builds in `O(N)`, and every update or query takes `O(log N)` with `O(N)` memory.
