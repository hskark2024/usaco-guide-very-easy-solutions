# Test-case walkthroughs

For speeds `3 1 2`, sort to `1 2 3`. A size-two interval costs one, and the full width is two, so the answer is three.

One runner always has discrepancy zero.

If every speed is equal, every interval width is zero and the total remains zero.

Large values require 64-bit totals: the official large sample exceeds a signed 32-bit integer.
