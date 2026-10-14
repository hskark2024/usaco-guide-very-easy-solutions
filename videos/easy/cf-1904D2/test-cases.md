# Test-case walkthroughs

For `A = [1,2,3,2,4]` and `B = [1,3,3,2,4]`, the original `3` at position three can spread left across `[2,3]`. No blocker exists, so the answer is `YES`.

For `A = [1,1]` and `B = [1,2]`, target `2` has no original source. The answer is `NO`.

For `A = [1,3,1]` and `B = [3,3,1]`, the middle `3` can spread left. It does not cross a target below `3`, so the transformation works.

For `A = [2,3,1]` and `B = [2,3,3]`, spreading `3` to the last position crosses no larger original and no smaller target, so it works.
