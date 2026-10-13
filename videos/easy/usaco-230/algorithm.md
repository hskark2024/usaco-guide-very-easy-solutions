# Algorithm derivation

1. Flood-fill every unlabelled `X` component with a new island ID.
2. For each source island, seed all its cells in a 0-1 BFS deque at distance zero.
3. Ignore `.`, charge zero for entering `X`, and charge one for entering `S`.
4. Record the minimum distance reaching every target island.
5. Define `dp[mask][last]` as the least cost visiting `mask` and ending at `last`.
6. Set `dp[1<<i][i]=0` for every possible first island.
7. Transition to every island absent from `mask` using the pairwise cost.
8. Take the minimum state in the full mask.
