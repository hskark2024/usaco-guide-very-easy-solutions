# Test-case walkthroughs

In the first official sample, the target is `11`. Exactly three of the six monotone routes through the `3 x 3` grid have that XOR, so the output is `3`.

For a one-cell grid containing `7`, target `7` gives one path while any other target gives zero.

For a row `1 2 3`, there is only one route. Its XOR is `1 XOR 2 XOR 3 = 0`, which directly checks that endpoints and the meeting cell are included once.
