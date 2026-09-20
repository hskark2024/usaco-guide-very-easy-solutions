# Test-case walkthroughs

For `ABCDE` and `ACE`, the matching diagonal cells grow from 1 at `A`, to 2 at `C`, to 3 at `E`. Mismatch cells carry the largest nearby value, so the bottom-right answer is 3.

For `ABC` and `DEF`, no diagonal match ever adds one, so every cell stays zero. For `AAAA` and `AA`, prefix limits prevent reusing a letter and the answer is exactly 2.
