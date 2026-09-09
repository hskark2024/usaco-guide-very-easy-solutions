# C++ coding walkthrough

1. Read the modulus `n`.
2. Loop through every candidate below `n` and test `gcd(candidate,n)`.
3. Append every coprime value and update the modular product.
4. If the product is not one, build a filtered vector without that residue.
5. Print the vector size and its increasing contents.
6. Use `long long` for the temporary multiplication.
