# Algorithm derivation

1. Let `best[m]` be the maximum pages obtainable from processed books while spending at most `m`.
2. Initialize every capacity to zero because the empty purchase is legal.
3. Process each book `(price[i], pages[i])` once.
4. Scan `m` downward from `X` to `price[i]`.
5. Set `best[m] = max(best[m], best[m-price[i]] + pages[i])`.
6. Return `best[X]` after all books.

The downward capacity order preserves the previous-book row, so each item is used at most once. Time is `O(NX)` and space is `O(X)`.
