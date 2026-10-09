# C++ coding walkthrough

1. Keep `left` and `right` as the current unpartitioned boundaries.
2. Reset four `uint64_t` hashes and two powers for each outer search.
3. Append the left letter by multiplying the old hash by its base.
4. Prepend the right letter by multiplying the new value by the current power.
5. Compare both hash pairs before doing any full character comparison.
6. Use `std::equal` as a collision-proof confirmation.
7. On success, add two and move both boundaries by the chunk length.
8. If the search ends without a pair, add one center chunk and finish.
