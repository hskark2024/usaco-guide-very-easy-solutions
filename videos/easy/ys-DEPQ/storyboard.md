# Storyboard

1. **Hook — a sorted shelf with two exits**: Values enter anywhere and leave from the left or right.
2. **Three query types**: Insert, pop minimum, and pop maximum cards appear.
3. **Why multiset**: Contrast one-ended heaps and duplicate-losing `set` with an ordered duplicate-preserving tree.
4. **Insert operation**: Slide a new value into sorted position.
5. **Minimum endpoint**: Highlight `begin()` and erase one node.
6. **Maximum endpoint**: Show `end()` past the shelf, then step back with `prev`.
7. **Duplicate walkthrough**: Insert a second `3`, then pop maximum twice.
8. **Proof and complexity**: Maintain the collection invariant and show logarithmic operations.
