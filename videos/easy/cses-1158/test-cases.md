# Test-case walkthroughs

## Official sample

With prices `4, 8, 5, 3`, pages `5, 12, 8, 1`, and budget `10`, the four-dollar and five-dollar books cost nine and give thirteen pages. The eight-dollar book gives twelve, so the optimum is `13`.

## Unaffordable book

One book costs `6`, has `100` pages, and the budget is `5`. It never enters a transition, so the answer is `0`.

## Exact fit

One book costs `2`, has `7` pages, and the budget is `6`. The answer remains `7`, because a descending scan does not buy the same book three times.

## Independent verifier

For random collections of at most twelve books, the oracle enumerates every subset of book indices, rejects subsets over budget, and takes the largest page sum. This directly checks duplicate prices, unused budget, and multi-book optima.
