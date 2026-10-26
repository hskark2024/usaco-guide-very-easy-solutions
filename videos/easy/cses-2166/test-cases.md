# Test-case walkthroughs

## Official first query

Range two through six is `[2,-1,3,1,-5]`. Its running sums are `2,1,4,5,0`, so the maximum prefix is `5`.

## After replacement

Replacing position four with `-2` changes that range to `[2,-1,-2,1,-5]`. Its best running sum is now `2`, which matches the second output.

## All negative

For `[-8,-2,-5]`, every nonempty prefix is negative. Because the empty prefix is allowed, the answer is `0`.

## Maximum constraints

Use `N=Q=200,000`, alternate large positive and negative values, perform many point replacements, and query the whole array. This checks 64-bit sums, merge order, and logarithmic performance.
