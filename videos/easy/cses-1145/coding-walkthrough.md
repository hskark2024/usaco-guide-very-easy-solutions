# C++ coding walkthrough

1. Read `N` and create an empty `smallest_tail` vector.
2. Reserve `N` positions so growth does not repeatedly reallocate.
3. Process the array from left to right to preserve subsequence order.
4. Use `lower_bound` to find the first stored tail at least as large as the current value.
5. Append if every tail is smaller; otherwise replace the located tail.
6. Print the vector size.

The vector stores useful representatives for every length, not necessarily one literal subsequence from the input.
