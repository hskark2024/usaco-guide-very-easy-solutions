# C++ coding walkthrough

1. Define `RunSummary` with length, prefix, suffix, best, first bit, and last bit.
2. Make the zero-length summary the merge identity.
3. In `combine`, test whether the touching bits match.
4. Compute the crossing candidate and the parent best.
5. Extend the prefix or suffix only through a completely uniform child.
6. Build leaves from the input bits and merge upward.
7. Flip a leaf's bit and rebuild its ancestors.
8. Print the root's best length after each update.
