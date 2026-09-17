# Test-Case Walkthroughs

## Official sample

Coins are `4, 2, 5, 2`. The reachable positive sums are `2, 4, 5, 6, 7, 8, 9, 11, 13`, so the count is nine. The two separate twos explain why sum four can be made without the four-valued coin.

## One coin

Coin `7` gives only sum `7`. Sum zero is internally reachable but excluded from output.

## Catch wrong loop direction

With one coin valued `2`, an upward scan would incorrectly mark `4, 6, 8`, and so on. The correct descending scan marks only `2`.

## Powers of two

Coins `1, 2, 4, 8` create every total from one through fifteen.
