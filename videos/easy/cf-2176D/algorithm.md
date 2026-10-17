# Algorithm derivation

1. Read each directed edge `u -> v` and compute `a[u]+a[v]`.
2. Sort edges by that sum in descending order.
3. Keep an ordered map `ways[u]` keyed by the next vertex value.
4. For each edge, set `count=1+ways[v][a[u]+a[v]]`.
5. Add `count` to `ways[u][a[v]]` modulo `998244353`.
6. Add `count` to the answer.
7. Print the answer after processing all edges.
