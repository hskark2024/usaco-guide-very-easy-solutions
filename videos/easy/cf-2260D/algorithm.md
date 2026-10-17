# Algorithm derivation

1. Represent candidate prefix sums by integers from `-3` to `3`.
2. Set only prefix sum zero reachable before processing the string.
3. For each sign, create a fresh unreachable DP row.
4. Try all old and new candidate sums.
5. Require the new candidate to match the sign and differ from the old sum.
6. Relax with `max(old_cost, abs(new_sum-old_sum))`.
7. Replace the old row and continue.
8. Print the minimum final cost, or `-1` when no state is reachable.
