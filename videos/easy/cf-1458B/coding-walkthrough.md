# C++ coding walkthrough

1. Read glasses and compute global totals.
2. Allocate dp[count][capacity] with -1 as the unreachable sentinel.
3. Update both axes downward for a 0/1 choice.
4. Evaluate min(2*capacity, total_water+inside_water).
5. Print fixed-point results from doubled integers.
