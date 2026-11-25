# Test-case walkthroughs

## Official sample

With side length `6`, centers `(0,0)` and `(-2,1)` have gaps `2` and `1`. Their shared area is `(6-2)(6-1)=20`, and no other pair overlaps.

## Border touch only

For side length `4`, centers `(0,0)` and `(4,0)` have horizontal gap exactly `K`. Shared width is zero, so the required answer is `0`.

## Exactly one overlap

For side length `10`, centers `(0,0)` and `(3,4)` share width `7` and height `6`, so the answer is `42`.

## More than one pair

For side length `10`, centers `(0,0)`, `(1,1)`, and `(20,20)` plus another center `(2,2)` produce at least two overlapping pairs, so the algorithm stops with `-1`.
