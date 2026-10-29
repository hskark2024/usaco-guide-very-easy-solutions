# Algorithm derivation

Directly simulating a dense progression is expensive, but a large step cannot be dense. Split at about square root of `N`.

Simulate large steps. Group small steps, encode each progression with start and stop events, and sweep each residue class through the recurrence `diff[i] += diff[i-d]`. Reusing one buffer keeps memory linear.
