# Algorithm derivation

The query needs more than a global maximum: it needs the first position meeting a threshold. Store interval maximums in a segment tree. The root says whether any position works. When one does, the left child says whether the answer lies in the earlier half. Descend left if possible and right otherwise. This proves both existence and minimal index at every level.

After choosing a leaf, subtract the request and restore every ancestor maximum. Building costs `O(n)` and each group costs `O(log n)`.
