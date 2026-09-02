# C++ coding walkthrough

1. Construct `parent[i] = i` with `iota` and set every component size to one.
2. In `find`, stop at a self-parent; otherwise assign the recursive result back to `parent[x]`.
3. In `unite`, replace both endpoints with roots.
4. Return early if the roots match.
5. Swap roots when necessary so the larger component remains on top.
6. Attach the smaller root and update the larger root's size.
7. For a connectivity query, print the Boolean result of equal roots.
