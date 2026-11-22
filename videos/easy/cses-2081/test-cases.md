# Test-case walkthroughs

## Official sample

The five-node sample allows distances two and three. Literal pair distances give six qualifying pairs, matching the output.

## One-length interval

When `K1=K2`, the result must match Fixed-Length Paths I for that length.

## Full useful range

For `K1=1` and `K2=N`, every unordered pair qualifies, so the answer is `N*(N-1)/2`.

## Chain formula

At distance `d`, an `N`-node chain has `N-d` pairs. Sum that value for all allowed `d < N`.

## Random oracle

Use BFS from every node and count unordered distances inside the interval.
