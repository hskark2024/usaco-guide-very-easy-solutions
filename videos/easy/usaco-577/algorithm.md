# Algorithm derivation

For high-card matching, the smallest card that beats the current opponent is never worse than a larger winning card; exchanging them preserves all future options. Compute these maximum matching sizes for every prefix. Apply the symmetric greedy backward for each low-card suffix, using the largest card still below Elsie's.

For each split `k`, add `high_prefix[k] + low_suffix[k]`. Ordered-card exchange makes those two win counts jointly realizable, and leftover cards fill losses. Two ordered-set scans give `O(N log N)` time and `O(N)` space.
