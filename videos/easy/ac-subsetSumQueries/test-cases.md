# Test-case walkthroughs

## Duplicate balls and a direct target

For `K = 10`, add `5`, add another `5`, then add `10`. The answers are `0`, `1`, and `2`: the pair of distinguishable fives is one target subset, and the ten alone is another. Removing one five leaves only the ten, so the next answer is `1`.

## Value above the target

With `K = 7`, adding or removing value `20` cannot change any subset totaling seven. The implementation still prints an answer for each query.

## Empty target count

Even though `ways[0]` is always one for the empty subset, queries ask for the given positive `K`; an unreachable target correctly prints zero.

## Independent verifier

Random valid add/remove sequences keep at most ten balls. After each operation, the oracle enumerates all `2^n` physical subsets and compares the target count. A second case inserts eighty ones and removes them again, checking modular wraparound with exact binomial coefficients.
