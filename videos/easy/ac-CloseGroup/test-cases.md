# Test-case walkthroughs

For three vertices with edges `1-2` and `1-3`, all three do not form a clique because `2-3` is missing. Either edge can be deleted to leave one pair and one singleton, so the answer is two.

A complete graph needs one group. An empty graph needs one singleton group per vertex. Two disconnected triangles need two groups. A path on four vertices can be split into two edge-cliques, so its answer is two.
