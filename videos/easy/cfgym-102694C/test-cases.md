# Test-case walkthroughs

## Path crossing the root

For route `4-2-1-3-7`, energy values `0, 2, 3, 4, 9` end at `4, 1, 3, 7, 7`.

## Same endpoint

If start equals finish, the route length is zero and every energy amount returns that same vertex.

## Answer on downward half

After passing the LCA, compute the remaining distance to the finish and climb backward from the finish.
