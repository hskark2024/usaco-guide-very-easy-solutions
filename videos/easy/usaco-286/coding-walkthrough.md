# C++ coding walkthrough

1. Store each undirected edge with weight `+1` or `-1`.
2. `find_centroid` iteratively roots the active component and computes subtree sizes in reverse order.
3. `collect_branch` uses enter and exit events so `path_frequency_` represents only the current centroid-to-node path.
4. `PathInfo` separates a true internal repeat from the zero label that merely repeats the centroid.
5. `count_paths_through` queries total and unusable histograms before merging the current branch.
6. Only touched balance cells are cleared, keeping each centroid step linear.
7. `decompose` removes the centroid and recurses into smaller components.
