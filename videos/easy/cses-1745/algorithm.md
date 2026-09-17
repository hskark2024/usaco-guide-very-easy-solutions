# Algorithm Derivation

All possible sums lie between zero and the total value `S`, so use a boolean array `reachable[0..S]`. Begin with only zero true.

For each physical coin `c`, every previously reachable sum `t` makes `t+c` reachable. Implement this as `reachable[s] |= reachable[s-c]` while scanning `s` from `S` down to `c`. Descending order stops the same coin from making a chain of new states. Finally scan positive indices upward to collect a sorted answer.
