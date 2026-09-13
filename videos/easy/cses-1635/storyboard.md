# Storyboard

1. **Problem setup.** Show reusable coins and a target jar labeled `X`.
2. **Order matters.** Place `2 + 3` beside `3 + 2` and count both.
3. **State.** Reveal `ways[s]` as the number of sequences totaling `s`.
4. **Choose the last coin.** Remove the final coin `c` and point to state `s-c`.
5. **Official sample.** Fill selected cells for coins `2, 3, 5` until target `9` reaches `8`.
6. **Loop-order warning.** Highlight sum outside and coin inside.
7. **Proof.** Sort all sequences into disjoint boxes by final coin.
8. **Code and complexity.** Walk through the compact array, modulo, and `O(NX)` bound.
