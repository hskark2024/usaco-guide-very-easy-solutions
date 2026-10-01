# Algorithm derivation

1. Root the tree and save an iterative traversal order.
2. Define `ways[v][c]` for each of three colors.
3. Initialize an unpainted vertex to `(1,1,1)`.
4. Initialize a fixed vertex to one at its required color and zero elsewhere.
5. For every child and parent color `c`, sum the child's two states not equal to `c`.
6. Multiply that sum into `ways[v][c]` modulo `1,000,000,007`.
7. Process vertices backward and sum the root's three states.
