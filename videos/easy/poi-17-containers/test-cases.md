# Test-case walkthroughs

## Official example

Three progressions overlap at several positions. Directly list each placement, then add columns to obtain `0 1 2 1 3 1 0 1`.

## Small step

For step 3, positions form three residue chains. A start event activates one chain, and a stop event cancels the contribution after the requested number of placements.

## Large step

With step 321 and `N = 100000`, an operation touches at most about 312 positions, so literal iteration is efficient.
