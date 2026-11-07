# Algorithm derivation

1. Root the attraction tree and record parent, depth, and order.
2. Compute subtree sizes in reverse order and select heavy children.
3. Flatten each heavy chain into consecutive positions.
4. Build an XOR segment tree over current values.
5. While chain heads differ, XOR the deeper chain suffix and move above it.
6. XOR the final same-chain interval.
7. Replace a value by assigning its one segment-tree leaf.
