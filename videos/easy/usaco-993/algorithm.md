# Algorithm derivation

1. Route value cannot be compared without its duration because cost is `C*T^2`.
2. Store maximum gross reward by exact day and ending city.
3. Initialize only city 1 as reachable on day zero.
4. For every new day, relax every directed road from the preceding day's layer.
5. Whenever city 1 is reachable, subtract the quadratic cost and update the answer.
6. Bound the search at 1000 days: daily reward is at most 1000, while cost is at least `T^2`.
7. Roll two city arrays because transitions use only the previous day.

This gives `O(1000M)` time and `O(N + M)` space.
