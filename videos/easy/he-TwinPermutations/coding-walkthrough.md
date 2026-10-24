# C++ coding walkthrough

1. Build `position_in_first[value]` while reading the first permutation.
2. Transform the second permutation into first-permutation positions.
3. Store the requested range length for every query.
4. Add a positive event at `R2` and a negative event at `L2-1`.
5. Sweep prefixes from zero through `n`.
6. Insert the current transformed position into the Fenwick tree.
7. Answer each event with a Fenwick range sum on `[L1,R1]`.
8. Print `range_length - common_value_count` for every query.
