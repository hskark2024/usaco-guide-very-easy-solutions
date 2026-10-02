# Algorithm derivation

1. Choose any temporary root and record a parent-first traversal order.
2. Process vertices backward to calculate every subtree size.
3. For the temporary root, sum all subtree sizes to get its painting score.
4. Process parent-child edges forward.
5. If the child's old subtree has size `s`, reroot with `score[child] = score[parent] + N - 2s`.
6. Keep the largest score over all vertices.

The update works because `s` vertices move one level closer and `N-s` vertices move one level farther.
