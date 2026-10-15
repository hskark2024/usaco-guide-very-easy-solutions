# Test-case walkthroughs

Both official examples are included in the smoke suite and exercise starts at internal nodes and leaves.

On a two-node tree, either starting node is winning because Ron makes the only move and Hermione is stuck.

At the center of a three-node path, Ron moves to a leaf and wins. Starting at an endpoint has two moves total, so Hermione wins.

Random trees with up to ten nodes are checked by recursive minimax over the literal current node and active-node mask.
