# Algorithm derivation

1. Build a smallest-prime-factor table through the largest input value.
2. Factor each number using that table.
3. Reduce every prime exponent modulo `k` and discard zero residues.
4. Store the remaining `(prime,residue)` pairs as the number's signature.
5. Replace every residue `r` by `k-r` to form the needed partner signature.
6. Add the number of earlier occurrences of that partner.
7. Insert the current signature for later positions.
