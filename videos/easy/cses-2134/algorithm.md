# Algorithm derivation

1. Root the tree and record parent, depth, and traversal order.
2. Process the order backward to compute subtree sizes and each heavy child.
3. Follow heavy children to assign consecutive positions and chain heads.
4. Store vertex values in a maximum segment tree.
5. For different chain heads, query the deeper chain suffix and move above it.
6. Query the final same-chain interval.
7. Point assignments update one flattened position.
