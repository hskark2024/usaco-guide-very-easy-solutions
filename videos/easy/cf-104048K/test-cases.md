# Test-case walkthroughs

For `abcd`, `defg`, `fghi`, merge in that order. The first overlap is `d` and the second is `f`, so the result length is `4+3+2=9`.

For duplicate phrases `abc`, `abc`, only one copy survives and the answer is `3`.

For `bc`, `abcd`, the first phrase is contained in the second, so the answer is `4` without any DP transition.
