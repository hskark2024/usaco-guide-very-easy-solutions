# Test-case walkthroughs

## Official sample

For edges `1-2, 2-3, 3-4, 3-5` and `K=2`, the pairs are `(1,3)`, `(2,4)`, `(2,5)`, and `(4,5)`. Answer: `4`.

## Star with K=2

Every pair of distinct leaves is two edges apart. With `L=N-1` leaves, the answer is `L*(L-1)/2`.

## Chain

In an `N`-node chain, exactly `N-K` pairs have distance `K` when `K<N`; otherwise the answer is zero.

## Random oracle

Run BFS from each vertex, count unordered pairs at distance `K`, and compare with the solution.
