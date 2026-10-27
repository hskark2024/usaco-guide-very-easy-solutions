# Storyboard

1. Show weighted grass patches and a movable Manhattan-radius diamond.
2. Draw the diamond's awkward slanted boundary.
3. Replace `(x,y)` with `(x+y,x-y)` and animate the diamond becoming a square.
4. Mark the square's width as `2K` in both directions.
5. Sort points along transformed `u` and slide a two-pointer window.
6. Turn one active point into a valid-center interval `[v-K,v+K]`.
7. Add its grass across that interval in a lazy segment tree.
8. Read the largest active overlap from the tree root.
9. Walk through the official sample and its answer of eight.
10. Finish with correctness, complexity, randomized checks, and the maximum case.
