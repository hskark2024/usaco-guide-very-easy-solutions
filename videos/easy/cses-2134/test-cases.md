# Test-case walkthroughs

## Official sample

The path `3-1-2-5` initially has values `1,2,4,3`, so its maximum is `4`. Updating vertex 2 to value 2 changes the route maximum to `3`.

## Same vertex

A query from a vertex to itself must return exactly that vertex's current value.

## Multiple chains

Use a balanced tree and query between opposite leaves so the algorithm processes chain pieces from both sides.
