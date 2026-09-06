# Algorithm derivation

1. Read all child lists and count `frequency[y]` for every gift `y`.
2. For a fixed first child `x`, sum `frequency[y]` over gifts in that child's list.
3. Multiply that sum by `inverse(k_x)` because the bot chooses uniformly within the list.
4. Add the contribution for every possible first child.
5. Multiply the total by `inverse(n)^2` for the independent first-child and recipient choices.
6. Compute every inverse as `value^(MOD-2) mod MOD` because `MOD` is prime.
7. Reduce every intermediate sum and product modulo `998,244,353`.
