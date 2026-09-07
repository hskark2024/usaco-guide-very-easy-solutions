# Algorithm derivation

1. Factor `N` with trial division.
2. For every discovered prime, count its exponent `e`.
3. Start the next distinct power cost at one.
4. While the cost fits in `e`, subtract it and count one operation.
5. Increase the next cost from one to two to three and so on.
6. Add the independent counts for all prime factors.
7. If a prime factor remains after trial division, add one final operation.
