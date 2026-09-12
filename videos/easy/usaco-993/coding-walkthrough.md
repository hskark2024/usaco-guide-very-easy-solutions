# C++ coding walkthrough

1. Read rewards and convert road endpoints to zero-based indices.
2. Store each directed road as a `(from, to)` pair.
3. Fill the previous-day array with an unreachable sentinel and set city 1 to zero.
4. For days 1 through 1000, create a fresh unreachable current-day array.
5. Relax each road from reachable previous states, adding the destination reward.
6. If city 1 is reachable, subtract `C * day * day` and update the answer.
7. Swap day layers and continue.
8. Print zero when no trip produces positive profit.

The solution comments explain the day bound, the gross-versus-net distinction, and safe sentinel handling.
