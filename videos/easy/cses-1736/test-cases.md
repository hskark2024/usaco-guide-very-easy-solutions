# Test-case walkthroughs

## Official sample

The starting values sum to `17`. Updating the full five-position range adds `1+2+3+4+5=15`, so the next query reports `32`.

## Progression starts in the middle

Updating `[3,5]` must add `1,2,3`, not `3,4,5`. The affine intercept `1-left` resets the sequence correctly.

## One position

Updating `[4,4]` adds exactly `1`. This catches off-by-one mistakes when converting endpoints.

## Maximum operations

Apply `199,999` full-range updates to `200,000` initial ones, then query the total. The expected value uses the triangular number `n(n+1)/2` and requires 64-bit arithmetic.
