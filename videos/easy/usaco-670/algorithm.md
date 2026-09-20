# Algorithm derivation

1. Store Holstein and Guernsey coordinates with one-based indices.
2. Fill `end_at_h` and `end_at_g` with infinity.
3. Set `end_at_h[1][0] = 0`.
4. At every reachable H-ending state, append the next Holstein or Guernsey.
5. At every reachable G-ending state, append the next Holstein or Guernsey.
6. Add squared Euclidean distance for each appended cow and keep the minimum.
7. Output `end_at_h[H][G]` to enforce the required ending.
