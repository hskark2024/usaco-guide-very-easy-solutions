# C++ coding walkthrough

1. Build `parent`, `depth`, and a root-first `order` iteratively.
2. Traverse `order` backward to compute `subtree_size` and `heavy_child`.
3. Assign `chain_head` and `position` while walking each heavy chain.
4. Implement a segment tree whose values are `(depth, vertex)` pairs.
5. Store infinity for white vertices and the real pair for black vertices.
6. For a query, combine chain-interval minima while moving toward root `1`.
7. Print the candidate's vertex field, which is already `-1` for infinity.

The many comments in the solution connect each array and loop to its tree meaning.
