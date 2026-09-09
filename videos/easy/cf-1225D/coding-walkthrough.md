# C++ coding walkthrough

1. Read the array and remember its maximum value.
2. Sieve the smallest prime factor for every value up to that maximum.
3. Repeatedly divide each number by its smallest prime and count the exponent.
4. Append nonzero exponent residues to the signature and complements to a second vector.
5. Look up the complement in a map of earlier signatures.
6. Add the frequency to a `long long` answer.
7. Insert the current signature and continue left to right.
