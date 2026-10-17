# Algorithm derivation

1. Precompute modular inverses for factors `1..N-2`.
2. Multiply zero-based index `i` for every `s[i]=='?'` with `i>0`.
3. Print zero when `s[0]=='?'`; otherwise print the product.
4. For each update at position `i>0`, divide out `i` if the old character is `?`.
5. Multiply by `i` if the replacement is `?`.
6. Store the replacement and print using the same first-position rule.
