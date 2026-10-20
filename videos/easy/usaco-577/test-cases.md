# Test-case walkthroughs

## Official example

Elsie has `1,8,4,3`; Bessie has `2,5,6,7`. Bessie can beat `1` under the high rule, switch, then use smaller cards to beat two later rounds. The maximum is three.

## Switch immediately

Split zero uses only suffix-low matching. This matters when Elsie's early cards are large.

## Never switch

Split `N` uses only prefix-high matching and handles an order dominated by small Elsie cards.

## Mixed advantage

A middle split can beat both endpoint strategies by using high Bessie cards early and low Bessie cards late.
