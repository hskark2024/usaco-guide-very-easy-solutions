# Algorithm derivation

Let edge `i` be the distance from checkpoint `i` to `i+1`. Let saving `i` be `edge[i-1]+edge[i]-dist(i-1,i+1)`. A query `[l,r]` equals the sum of edges `[l,r)` minus the maximum saving centered in `[l+1,r)`.

Moving checkpoint `i` affects only edges `i-1` and `i` and savings centered at `i-1`, `i`, and `i+1`. Segment-tree updates and both range queries take `O(log n)`.
