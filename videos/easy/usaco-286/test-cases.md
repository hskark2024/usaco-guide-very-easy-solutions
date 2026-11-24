# Test-case walkthroughs

## Official sample

The only valid route is `3-1-2-5-7`. Both color counts balance from barn 3 to rest barn 2 and from barn 2 to barn 7, so the answer is `1`.

## Four-edge alternating chain

Weights `+1,-1,+1,-1` give prefix sums `1,0,1,0`. The full path totals zero and its middle vertex has prefix zero, so it is valid.

## Two-edge balanced chain

Weights `+1,-1` total zero, but there is only one internal vertex and neither half is balanced. It must not be counted.

## All one color

No nonempty segment has sum zero, so the answer is `0`.
