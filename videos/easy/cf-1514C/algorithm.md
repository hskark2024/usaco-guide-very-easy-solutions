# Algorithm derivation

1. Examine every integer from `1` through `n-1`.
2. Keep exactly the values whose gcd with `n` is one.
3. Multiply all kept values modulo `n`.
4. If the product is one, the whole list is the answer.
5. Otherwise remove the value equal to that product.
6. Print the remaining values in their original increasing order.
