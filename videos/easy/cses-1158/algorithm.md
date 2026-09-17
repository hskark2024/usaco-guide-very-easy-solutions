# Algorithm Derivation

Define `best[m]` as the greatest page count obtainable with the already processed books while spending at most `m`. All capacities start at zero because buying nothing is feasible.

For price `h` and pages `p`, a selection either skips this book or buys it after a selection fitting in `m-h`: `best[m] = max(best[m], best[m-h] + p)`. Scan `m` downward so the source entry refers to earlier books. This rolls a conceptual `N`-by-`X` DP table into one row.
