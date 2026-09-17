# Test-Case Walkthroughs

## Official sample

Budget is `10`. Prices are `4, 8, 5, 3`; pages are `5, 12, 8, 1`. After book one, capacities at least four hold five pages. The eight-cost book can produce twelve. The five-cost book then combines with the four-cost book: price nine and pages thirteen. The last book cannot improve that result.

## Catch wrong loop direction

One book costs `2` and has `7` pages, with budget `6`. The answer is `7`, not `21`, because the book can be bought only once.

## Unaffordable book

One book costs `6`, with budget `5`; the answer is zero.
