# Storyboard

1. **Hook — answer every prefix**: Reveal a `D/K` string one character at a time.
2. **Count pairs**: Plot each prefix at coordinates `(D count,K count)`.
3. **Reduce with gcd**: Collapse points on the same ray to one primitive direction.
4. **Frequency becomes pieces**: Mark first, second, and third visits to one ratio.
5. **Proof by differences**: Subtract consecutive prefix count points to obtain equal-ratio chunks.
6. **Examples and axes**: Trace `DDK`, `DKDK`, all `D`, and all `K`.
7. **C++ implementation**: Highlight cumulative counts, gcd, pair keys, and map frequency.
