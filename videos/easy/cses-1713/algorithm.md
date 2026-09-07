# Algorithm derivation

1. Read all values and find their maximum `M`.
2. Sieve a smallest prime factor for every integer from `2` through `M`.
3. For each query, start `answer=1`.
4. Look up a prime dividing the remaining value.
5. Divide out all copies of that prime and count exponent `e`.
6. Multiply the answer by `e+1`.
7. Continue until the remaining value is one, then print the product.
