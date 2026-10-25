# Test-case walkthroughs

## Official sample

The first queried slice sums to `7`. Adding `2` on positions two through four raises the next slice sum to `11`. Replacing positions two through four with `5` makes the final slice sum `15`.

## Add, then set

Start with `[1,1,1]`, add `4` everywhere, then set the middle position to `2`. The result is `[5,2,5]`; the set must erase the older addition at that position.

## Set, then add

Set a range to `7`, then add `3` there. Every covered value must become `10`, confirming that a later add is folded on top of the assignment.

## Maximum command count

Use `200,000` positions and commands: many full-range large additions, a right-half assignment, many more additions, then one total query. This checks both tag orders and 64-bit sums.
