# Algorithm derivation

For `i <= k`, `p[i]+|i-k|=(p[i]-i)+k`. For `i >= k`, it equals `(p[i]+i)-k`. Store range minima for both transformed arrays in one segment tree. A query combines one prefix minimum and one suffix minimum, while an update replaces both values at a single leaf.

The build costs `O(n)`. Every update and minimum-price query costs `O(log n)`.
