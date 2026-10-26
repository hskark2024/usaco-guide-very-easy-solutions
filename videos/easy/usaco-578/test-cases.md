# Test-case walkthroughs

## Official sample

The interval `[3,4]` has minimum `2`, and `[1,3]` has sum `6`. Adding one to fields two and three changes the array from `[3,1,2,4]` to `[3,2,3,4]`. The next minimum is `3`, and the next sum is `8`.

## One field

With a single field containing `7`, both minimum and sum queries return `7`. After adding `5`, both return `12`, confirming the leaf update formulas.

## Overlapping intervals

Add to the entire array, then add to a middle slice. Query across both updated and untouched boundaries to force lazy tags to push and child summaries to merge.

## Maximum constraints

Use `N=200,000` and `Q=100,000`, repeatedly add `100,000` to the full array, then ask for the total and minimum. This checks 64-bit totals and logarithmic processing.
