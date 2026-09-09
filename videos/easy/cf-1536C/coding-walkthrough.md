# C++ coding walkthrough

1. Read the test count, then each length and string.
2. Maintain cumulative `D` and `K` counts.
3. Compute their gcd after adding each character.
4. Create the reduced pair `(D/g,K/g)`.
5. Increment that pair in a map and print its frequency.
6. Rely on `gcd(x,0)=x` to handle one-letter ratios cleanly.
