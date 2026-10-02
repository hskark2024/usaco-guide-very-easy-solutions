# C++ coding walkthrough

1. Store the undirected tree in adjacency lists.
2. Build `parent` and `order` iteratively from vertex zero.
3. Initialize every `subtree_size` to one.
4. Add each vertex's size into its parent while walking the order backward.
5. Sum those sizes into the first root's 64-bit score.
6. Walk the order forward and apply `+N-2*subtree_size[child]` to every child.
7. Update a 64-bit maximum and print it.
