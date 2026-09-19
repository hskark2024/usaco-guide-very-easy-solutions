# Test-case walkthroughs

`LOVE → MOVIE` can replace `L` with `M`, producing `MOVE`, then insert `I` before `E`. Two operations are sufficient, and the DP proves one is impossible, so the answer is 2.

Equal strings follow only free matching diagonals and return 0. `A → AB` needs one insertion, while `AB → A` needs one deletion. `AAAA → BBBB` needs four replacements.
