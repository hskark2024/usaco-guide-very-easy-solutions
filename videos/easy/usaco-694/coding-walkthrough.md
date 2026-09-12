# C++ coding walkthrough

1. Encode `H`, `P`, and `S` as three target categories.
2. Allocate `previous` and `current` as `(K + 1) x 3` integer tables.
3. Fill impossible states with a safely negative sentinel; set the three zero-switch starting states to zero.
4. For every round, switch count, and ending gesture, compare staying with switching from either other gesture.
5. Add one when the ending gesture-state beats this round's opponent move.
6. Swap the two layers after finishing the round.
7. Scan all final switch counts and gestures for the answer.

The submitted file comments why every initialization, transition, and sentinel check is necessary.
