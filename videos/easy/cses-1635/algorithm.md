# Algorithm derivation

1. Let `ways[s]` count ordered sequences totaling `s`.
2. Set `ways[0] = 1` for the empty sequence.
3. Compute sums from small to large.
4. For every coin `c <= s`, treat `c` as the final coin.
5. Add `ways[s-c]` into `ways[s]` modulo `1,000,000,007`.
6. Return `ways[target]`.

The outer sum loop preserves every different coin order. Time is `O(NX)` and space is `O(X)`.
