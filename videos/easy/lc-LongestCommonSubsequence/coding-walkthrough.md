# C++ coding walkthrough

1. Keep the LeetCode-facing algorithm in `Solution::longestCommonSubsequence`.
2. Swap the strings so the column dimension is shorter.
3. Allocate two zero-filled integer rows with an extra empty-prefix column.
4. Reset column zero and scan each row from left to right.
5. Use the diagonal entry on a match and the above/left maximum otherwise.
6. Swap row vectors instead of copying them.
7. Use the small `main` adapter only for repository tests.
