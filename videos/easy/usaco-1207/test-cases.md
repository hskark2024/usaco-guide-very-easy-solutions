# Test-case walkthroughs

In the official sample, two two-card selections, three four-card selections, and one six-card selection reach `(5,10)`. The other size buckets are zero.

With moves `(1,0)`, `(1,0)`, and goal `(1,0)`, two different one-card subsets work, so the first output is two.

With moves `(2,-1)` and `(-2,1)` and a nonzero unreachable goal, cancellation reaches the origin but must not be counted.
