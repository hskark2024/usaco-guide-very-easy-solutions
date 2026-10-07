# Test-case walkthroughs

For heights `1 2 3` and prices `10 100 1000`, target 3 costs `2*10 + 1*100 + 0*1000 = 120`, which is the official answer.

For heights `0 10` with equal prices, every target from 0 through 10 costs 10. This checks that a flat minimum is handled safely.

If every price is zero, every target is free and the answer is zero. A single building also always costs zero at its own height.
