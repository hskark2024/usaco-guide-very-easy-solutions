# Test-case walkthroughs

In the official sample, the route `H1 -> G1 -> G2 -> H2 -> H3` costs `9 + 1 + 9 + 1 = 20`. Each breed appears in number order and the route ends at `H3`, so it is legal and optimal.

When all cows share one coordinate, every edge costs zero and the answer is zero. With one Holstein and one Guernsey, the route must leave `H1`, visit `G1`, then return to the same required final `H1`, correctly charging both legs.
