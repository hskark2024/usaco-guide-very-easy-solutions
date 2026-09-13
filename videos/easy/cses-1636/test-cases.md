# Test-case walkthroughs

## Official sample

For coins `2, 3, 5` and target `9`, the combinations are represented once each:

- `2 + 2 + 5`
- `3 + 3 + 3`
- `2 + 2 + 2 + 3`

The answer is `3`.

## Rearrangement check

With coins `1, 2` and target `4`, there are three multisets: four ones, two ones plus one two, or two twos. The position of coin `2` is irrelevant.

## Reusing one denomination

Coins `3, 10` can make target `9` with three copies of `3`. The upward sum scan is what keeps that possibility available.

## Independent verifier

For small random cases, the oracle assigns a count from zero through `target / coin` to every denomination. It adds the denomination totals and counts assignments equaling the target, completely avoiding the solution's DP recurrence.
