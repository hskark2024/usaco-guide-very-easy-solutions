# Storyboard

1. Show a fixed array and a black-box `Secret(x,y)` machine.
2. Emphasize that the machine is associative but may be order-sensitive.
3. Split the array at its midpoint.
4. Build all left suffix aggregates ending at the midpoint.
5. Build all right prefix aggregates beginning after the midpoint.
6. Recurse and repeat the same preparation inside both halves.
7. Drop a query across its first crossed split.
8. Join its two stored pieces with exactly one black-box call.
9. Walk through sample queries and the singleton case.
10. Finish with proof, operation-call count, randomized folding, and maximum limits.
