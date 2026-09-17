# C++ Coding Walkthrough

1. Read the number of books and budget.
2. Read the price array and page array separately, matching the input format.
3. Allocate `best` with `budget+1` zero entries; each state means an at-most capacity.
4. For each book, scan money from `budget` down to its price.
5. Compare skipping with `best[money-price] + pages` using `max`.
6. Print `best[budget]`. The comments emphasize that downward order keeps every book single-use.
