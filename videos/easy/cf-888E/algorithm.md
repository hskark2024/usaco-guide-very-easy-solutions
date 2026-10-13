# Algorithm derivation

1. Reduce every value modulo `m`.
2. Split the array into two halves.
3. Generate all subset residues in both halves, including zero.
4. Sort the right residues.
5. For each left residue `x`, find the largest right residue `<= m-1-x`.
6. Maximize `x + right` over all left residues.
