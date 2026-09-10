# Algorithm derivation

1. A position alone is insufficient because the cost of the next bosses depends on whose session comes next.
2. Define `dp[i][0]` as the minimum skips after `i` bosses when the friend goes next.
3. Define `dp[i][1]` similarly when you go next.
4. Initialize only `dp[0][0] = 0`, because the friend begins.
5. From a reachable state, try taking one boss and two bosses when available.
6. A friend transition adds the number of hard bosses taken; your transition adds zero.
7. Toggle the next-turn bit after every session.
8. The answer is the minimum state after all `n` bosses because either player may finish the tower.
