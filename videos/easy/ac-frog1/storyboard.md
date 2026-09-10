# Storyboard

1. **Meet the frog.** Show stones with heights and arrows of length one or two.
2. **Why greedy fails.** Contrast the cheapest next jump with the cheapest full route.
3. **Define the state.** Place `dp[i]` beneath each stone.
4. **Build the recurrence.** Merge arrows from `i-1` and `i-2` into stone `i`.
5. **Trace an example.** Fill `0,20,30,30` under heights `10,30,40,20`.
6. **C++ implementation.** Highlight the base case and two transitions.
7. **Proof and complexity.** Emphasize that every route has one of two final jumps.
