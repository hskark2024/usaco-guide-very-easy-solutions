# Test-case walkthroughs

## Missing, insert, overwrite

1. Query key `8`: it is absent, so print `0`.
2. Assign `8 -> 12`; query `8`, so print `12`.
3. Assign `8 -> 99`; query `8`, so print `99`.

## Largest key

Assign `1000000000000000000 -> 7`, then query it. A 64-bit type preserves the key and prints `7`.

## Explicit zero

Assign `3 -> 0`, then query `3`. The output is `0`; this is indistinguishable in output from an absent key, but the invariant still holds.
