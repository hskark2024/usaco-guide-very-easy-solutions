# Storyboard

1. Highlight every possible prefix of a requested subarray, including empty.
2. Split one interval into left and right segment-tree children.
3. Show a prefix that ends inside the left child.
4. Show a prefix that takes all of the left child and continues right.
5. Derive `max(left.best, left.sum+right.best)`.
6. Store both `sum` and `best_prefix` in every node.
7. Replace one leaf and rebuild nodes along its root path.
8. Walk through the three official sample answers.
9. Emphasize left-to-right merge order and the `(0,0)` identity.
10. Finish with proof, complexity, randomized scans, and a maximum case.
