# Test-case walkthroughs

## Official sample highlights

- Route `1-3-5` initially XORs `1 ^ 4 ^ 16 = 21`.
- After vertex 1 becomes 16, route `3-5` XORs `4 ^ 16 = 20`.
- Route `1-3` then XORs `16 ^ 4 = 20`.

## Zero values

All-zero routes return zero. Changing one vertex to seven makes every route containing it XOR to seven when all other values remain zero.

## Self route

A route from one vertex to itself returns its current value exactly once.
