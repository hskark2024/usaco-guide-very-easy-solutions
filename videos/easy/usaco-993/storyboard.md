# Storyboard

1. **Business trip setup.** Show a directed city graph with reward badges and city 1 highlighted.
2. **Reward versus cost.** Plot linear maximum earnings against a quadratic travel-cost curve.
3. **Add time to the state.** Expand the city graph into day 0, day 1, and day 2 layers.
4. **Road transition.** Animate an edge from `(day t, u)` to `(day t+1, v)` and add `reward[v]`.
5. **Official sample cycle.** Compare one loop's profit 21 with two loops' profit 24.
6. **Why 1000 days suffice.** Show `1000T - T^2 < 0` beyond 1000.
7. **Rolling implementation.** Keep only previous and current city vectors.
8. **Proof and complexity.** Emphasize the unique final road and `O(1000M)` time.
