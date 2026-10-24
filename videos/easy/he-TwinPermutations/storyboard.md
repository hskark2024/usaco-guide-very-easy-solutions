# Storyboard

1. Show two permutations with one highlighted range in each.
2. Color shared values green and unmatched values orange.
3. Move each value onto a coordinate grid.
4. Label x as position in the second permutation and y as position in the first.
5. Draw the query rectangle around points shared by both ranges.
6. Split the rectangle count into positive and negative x-prefix events.
7. Animate the x-sweep and Fenwick updates on y.
8. Walk through `123` versus `543`, leaving only value `3` shared.
9. Connect the rectangle count to the exact minimum swap formula.
10. Finish with complexity and independent test oracles.
