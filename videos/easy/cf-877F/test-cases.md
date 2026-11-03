# Test-case walkthroughs

## First official example

Math books contribute `+1` and the economics book contributes `-1`, with `K = 1`. The full interval contains the three singleton math books plus the subarray from book 2 through book 4, for four choices.

## Zero difference

If all book values are zero and `K = 0`, every nonempty subarray works. A length-`N` query therefore returns `N(N+1)/2`, which also checks 64-bit output.

## Negative K

More economics problems than math problems can be requested. The same prefix equation works; adding on the right still searches for `current-K`, even when subtracting `K` increases the target.
