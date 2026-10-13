# C++ coding walkthrough

1. Store the modulus and values in `long long`.
2. Reduce values before enumeration.
3. Build each half's residue list by iterative doubling.
4. Include residue zero for the empty subset.
5. Sort the right residue list.
6. Compute `m-1-x` for each left residue.
7. Use `upper_bound`, step back once, and update the maximum.
8. Print the best residue.
