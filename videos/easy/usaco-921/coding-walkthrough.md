# C++ coding walkthrough

1. Use iterative traversal for parent and depth data.
2. Reverse the traversal order for subtree-size accumulation.
3. Follow `heavy_child` links to assign positions and chain heads.
4. The segment tree uses XOR for both parent recomputation and range queries.
5. `path_xor` consumes the deeper chain suffix until both heads match.
6. The last inclusive interval contains the remaining route and both endpoints.
7. An update assigns the new value at `position[vertex]`.
