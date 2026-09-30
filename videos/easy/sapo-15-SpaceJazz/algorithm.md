# Algorithm derivation

1. Treat every valid completed piece as a noncrossing pairing of equal notes.
2. Define `dp[left][right]` as the fewest insertions for that inclusive substring.
3. Give empty intervals cost zero.
4. Initialize an interval with `1 + dp[left+1][right]` by inserting a copy of its first note.
5. For each later equal note at `partner`, try pairing the two observed notes.
6. The pairing costs `dp[left+1][partner-1] + dp[partner+1][right]`.
7. Fill intervals from shortest to longest and print `dp[0][N-1]`.
