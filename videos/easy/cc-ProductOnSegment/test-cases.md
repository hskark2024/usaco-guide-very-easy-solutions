# Test-case walkthroughs

## Composite modulus

For `[6, 10, 15]` modulo 12, division-based prefix products fail because factors are not invertible. The disjoint table simply multiplies stored halves and returns the correct remainder.

## Crossing one split

For a query `[2, 6]`, locate the highest bit where 2 and 6 differ. The saved suffix beginning at 2 and saved prefix ending at 6 meet at that level's midpoint and cover the range exactly once.

## Online update

After each product `answer`, set `x = (answer + 1) mod P`. Add that state to the correct base endpoints before the next table lookup.
