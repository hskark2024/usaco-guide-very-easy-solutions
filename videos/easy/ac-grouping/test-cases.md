# Test-case walkthroughs

In the first official sample, pair scores are `10`, `20`, and `-100`. Putting all three rabbits together scores negative seventy. Grouping rabbits one and three scores twenty while leaving rabbit two alone, so twenty is optimal.

With two rabbits and a negative edge, two singleton groups score zero. If every edge is positive, one full group is optimal. If every edge is negative, all singletons are optimal. A four-rabbit case with billion-sized positive scores confirms that 64-bit arithmetic is required.
