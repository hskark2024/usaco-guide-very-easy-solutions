# Algorithm derivation

1. Root the tree and save an iterative traversal order.
2. Initialize both color counts at every vertex to one.
3. For a white vertex, multiply by `white[child] + black[child]`.
4. For a black vertex, multiply by `white[child]` only.
5. Reduce every operation modulo `1,000,000,007`.
6. Process the order backward so every child is ready.
7. Add the root's white and black counts.
