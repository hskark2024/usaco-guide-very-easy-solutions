# Algorithm derivation

A point update changes just one root-to-leaf path. To merge intervals, record enough boundary information to decide whether two runs connect: first and last bits plus longest prefix and suffix. The longest run in the parent is the maximum of both child answers and the joined boundary run when its bits match.

Build in `O(n)`. Each flip and answer takes `O(log n)` with `O(n)` storage.
