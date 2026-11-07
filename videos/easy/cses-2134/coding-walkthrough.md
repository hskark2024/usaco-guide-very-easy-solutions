# C++ coding walkthrough

1. Iteratively build `parent`, `depth`, and a root-first order.
2. Reverse that order to accumulate subtree sizes and select heavy children.
3. Walk each chain in a loop and save light children as future chain starts.
4. `position[v]` maps a vertex to its segment-tree leaf.
5. `path_max` always removes the deeper chain suffix first.
6. Once heads match, one inclusive interval covers the remaining path.
7. Print type-two answers on one space-separated line as CSES expects.
