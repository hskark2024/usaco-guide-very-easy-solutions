# C++ coding walkthrough

1. Read each matrix row into a `uint32_t` compatibility mask.
2. Allocate an integer vector of size `1<<N`.
3. Seed the empty state with one way.
4. Use `__builtin_popcount(mask)` to identify the next man.
5. Form the available-woman mask with compatibility and unused bits.
6. Extract its lowest bit repeatedly.
7. Add into the next mask and reduce modulo `1,000,000,007`.
8. Print the final array cell.
