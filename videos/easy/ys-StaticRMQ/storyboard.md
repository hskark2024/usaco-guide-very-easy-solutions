# Storyboard

1. **Hook — many questions, frozen array**: Show one array and several highlighted query ranges.
2. **Half-open intervals**: Highlight `[2, 5)` over `7 2 5 1 9 3`, ending before index 5.
3. **Power-of-two layers**: Stack blocks of lengths 1, 2, and 4 above the array.
4. **Build recurrence**: Join two neighboring half-block minima into one larger block.
5. **Two-block query**: Cover a length-five query with two overlapping length-four blocks.
6. **Walkthrough**: Evaluate `[0, 3)` using the two length-two blocks.
7. **Proof and code**: Show coverage/no-outside-values, then the C++ table lookup.
8. **Complexity recap**: `O(N log N)` build and `O(1)` per query.
