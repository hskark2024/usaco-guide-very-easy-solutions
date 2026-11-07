# Test-case walkthroughs

## Official sample

The mapping is `1->2`, `2->1`, `3->1`, and `4->4`.

- From 1, two teleports are `1->2->1`.
- From 3, four teleports are `3->1->2->1->2`.
- From 4, every positive number of teleports stays at 4.

## Zero teleports

A query `(x, 0)` applies no set-bit shortcuts, so it must return `x` unchanged.

## Huge count on a cycle

On a three-planet cycle, reduce a hand calculation modulo three and compare it with the billion-step table answer.
