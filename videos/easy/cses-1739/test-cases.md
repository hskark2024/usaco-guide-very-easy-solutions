# Test-case walkthroughs

## Official sample

The first requested rectangle contains three trees. Toggling row three, column three adds one tree inside the same rectangle, so its second answer is four.

## One cell

Start with a `1 x 1` empty grid, query zero, toggle it, query one, toggle again, and query zero. This checks both update signs and prefix coordinate zero.

## Random oracle

On small random grids, apply the same toggles to a plain character matrix and answer each rectangle by nested loops. Compare every result with the Fenwick program.

## Maximum constraints

Build an empty `1000 x 1000` grid, perform nearly `200,000` toggles, and finish with a full-grid query. This checks the optimized build and operation limits.
