# Test-case walkthroughs

For counts `2 2`, first place the two copies of value 1 in one way. Then choose two of four final positions for value 2, giving `C(4,2)=6`.

For counts `4 2 5`, the successive factors are `C(4,4)=1`, `C(6,2)=15`, and `C(11,5)=462`. Their product is `6930`.

A one-value case always has exactly one sequence, regardless of its frequency.

The verifier uses Python's exact integers to form multinomial coefficients, then compares residues for many prime and composite moduli. A total frequency of 5000 checks the largest Pascal table.
