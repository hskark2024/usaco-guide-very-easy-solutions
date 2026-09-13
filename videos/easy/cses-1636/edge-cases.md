# Edge-case checklist

- Target cannot be formed: answer `0`.
- One coin equals the target: count that combination once.
- One denomination may be reused many times.
- Different orders of the same multiset must not be duplicated.
- Scan sums upward to allow reuse of the current denomination.
- Keep the denomination loop outside the sum loop.
- Coin input does not need sorting; it only needs a fixed processing order.
- Preserve `ways[0] = 1` throughout every phase.
- Reduce each update modulo `1,000,000,007`.
- Use iterative storage for a target up to one million.
