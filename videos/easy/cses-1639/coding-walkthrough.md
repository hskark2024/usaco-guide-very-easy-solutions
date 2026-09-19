# C++ coding walkthrough

1. Read both uppercase strings and swap them to minimize the column count.
2. Allocate two integer vectors of `shorter.size()+1`.
3. Use `iota` for the base insertion row.
4. Set the deletion base at the beginning of each new row.
5. Compare `first[i-1]` and `second[j-1]` because DP lengths are one-based.
6. Use the free diagonal on equality; otherwise take the minimum of three edit predecessors.
7. Swap rows and print the final distance.
