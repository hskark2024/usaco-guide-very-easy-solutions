# C++ coding walkthrough

1. Store `sum_`, `pending_add_`, `pending_set_`, and `has_pending_set_` arrays.
2. `apply_set` replaces the sum, records the new set value, and clears the add tag.
3. `apply_add` increases the sum and folds into a pending set when possible.
4. `push` sends a set to both children before sending an addition.
5. Separate recursive functions handle add and set range updates clearly.
6. The query returns zero for no overlap and a stored node sum for full overlap.
7. Use `long long` for sums, values, and lazy tags.
