# C++ coding walkthrough

1. Allocate arrays for `minimum_`, `sum_`, and `lazy_add_`.
2. At a leaf, initialize both summaries to the field's value.
3. `pull` takes the smaller child minimum and adds the child sums.
4. `apply_add` updates both summaries using the node length and accumulates the tag.
5. `push` sends that tag to both children before partial recursion.
6. Return positive infinity for no overlap in a minimum query.
7. Return zero for no overlap in a sum query.
8. Use `long long` for values, tags, and totals.
9. Support both `haybales.in` files and standard input for local tests.
