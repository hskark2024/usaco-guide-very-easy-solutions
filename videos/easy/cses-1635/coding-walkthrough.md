# C++ coding walkthrough

1. Enable fast I/O and read `N`, `X`, and the coin values.
2. Create `ways` with `X + 1` integer cells initialized to zero.
3. Set `ways[0] = 1` to represent the empty prefix.
4. Loop `sum` upward from `1` through `X`.
5. Inside that loop, try each coin as the sequence's last coin.
6. Skip a coin when it is larger than `sum`.
7. Add `ways[sum-coin]` and normalize modulo `1,000,000,007`.
8. Print `ways[X]`.

The source comments emphasize state meaning, why smaller states are ready, and why this exact loop nesting counts order.
