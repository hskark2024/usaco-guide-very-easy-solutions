# Algorithm derivation

1. Root the tree at vertex 1 and compute iterative preorder.
2. Save `[entry[v], exit[v])` for every subtree.
3. Scan Euler positions from right to left.
4. Remember the currently marked position of every color.
5. Remove a color's old marker if it exists.
6. Mark the current position and remember it as that color's new representative.
7. Query the current vertex's subtree interval and save the marker count.
8. Print answers in vertex-number order.

Exactly one marker represents each color in the current suffix, converting distinct counts into ordinary range sums.
