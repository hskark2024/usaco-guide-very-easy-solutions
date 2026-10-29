# Test-case walkthroughs

## One strip

All points have `x < 1000`. Sorting by rising `y` makes vertical movement telescope, while every horizontal step is below 1000.

## Two strips

The first strip rises in `y`; the next falls. The boundary joins two high points instead of resetting from high to low.

## Verification

Read the produced indices, confirm every number from 1 through `N` appears once, then sum Manhattan distances from the original coordinates and compare with `2.5 * 10^9`.
