# C++ Coding Walkthrough

1. Read the coin values and accumulate their total to size the DP exactly.
2. Allocate a `vector<char>` so each boolean state is compact.
3. Set `reachable[0] = true` for the empty subset.
4. For each coin, loop from the total down to the coin value.
5. If `sum-coin` is reachable, mark `sum` reachable.
6. Collect true states from one upward into an answer vector.
7. Print the vector size, then its values separated by spaces.
