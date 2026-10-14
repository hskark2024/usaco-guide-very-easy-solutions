# Algorithm derivation

1. Reject if any `a[i] > b[i]`; maximum operations cannot decrease values.
2. Store every index of each value in the original array.
3. Build a segment tree for range maximum in `a` and range minimum in `b`.
4. For position `i`, find the closest original `b[i]` on each side.
5. For each candidate source `j`, query the interval between `i` and `j`.
6. Accept that source when `max(a[l..r]) <= b[i]` and `min(b[l..r]) >= b[i]`.
7. The transformation is possible exactly when every position has a valid source.
