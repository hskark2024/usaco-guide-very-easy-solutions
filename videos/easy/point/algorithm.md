# Algorithm derivation

For vectors `u=P2-P1` and `v=P3-P1`, calculate `u.x*v.y-u.y*v.x`.

- Positive signed area: `v` is counterclockwise from `u`, so print `LEFT`.
- Negative signed area: `v` is clockwise from `u`, so print `RIGHT`.
- Zero signed area: the vectors are collinear, so print `TOUCH`.

Use `__int128` for every difference, product, and subtraction. No division or floating-point tolerance is needed.
