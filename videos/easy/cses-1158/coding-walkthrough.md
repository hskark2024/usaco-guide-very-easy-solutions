# C++ coding walkthrough

1. Read `N`, budget `X`, then the price and page arrays.
2. Allocate `best[0..X]` and initialize it to zero.
3. Loop over each book index so equal-looking books remain distinct items.
4. For the current book, loop `money` downward from `X` to its price.
5. Compare skipping with `best[money-price] + pages`.
6. Store the larger value in place.
7. Print `best[X]` after every book has been processed.

The comments connect the descending scan with the zero-one restriction and explain why impossible-state sentinels are unnecessary.
