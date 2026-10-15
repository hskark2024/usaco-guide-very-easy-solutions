# Algorithm derivation

1. Sort the speed array.
2. Let `dp[l][r]` be the minimum total for the sorted interval `[l,r]`.
3. Set `dp[i][i] = 0`.
4. Process interval lengths from two through `N`.
5. The previous used set is `[l+1,r]` if the smallest was added last.
6. It is `[l,r-1]` if the largest was added last.
7. Add the forced current discrepancy `speed[r] - speed[l]` to the cheaper choice.
8. Output `dp[0][N-1]`.
