# Algorithm derivation

Store each segment's sum plus an optional assignment tag and an addition tag. Applying `set(x)` changes the sum to `x*length`, records the assignment, and clears older additions. Applying `add(x)` increases the sum; fold it into a pending assignment when one exists, otherwise accumulate the addition.

When descending, push assignment before addition to preserve operation order. Standard lazy recursion visits `O(log n)` nodes per command after an `O(n)` build and uses `O(n)` memory.
