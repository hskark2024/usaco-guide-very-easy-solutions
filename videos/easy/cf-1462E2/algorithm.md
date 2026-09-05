# Algorithm derivation

1. Sort each test case so tuple minimums and maximums become endpoints in index order.
2. Assign every tuple to its unique leftmost selected sorted index `left`.
3. Advance `right` to the first index with `a[right] - a[left] > k`.
4. Keep `left` as the chosen minimum.
5. Choose the other `m-1` indices from the `right-left-1` later values still inside the window.
6. Add `C(right-left-1, m-1)` modulo `1,000,000,007`.
7. Precompute factorials and inverse factorials through 200,000 so each combination is constant time.
8. Reuse the monotonic `right` pointer, giving a linear scan after sorting.
