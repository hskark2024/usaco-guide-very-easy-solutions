# Edge-case checklist

- `N = 1`, where every query is a singleton.
- Values equal to zero.
- Composite `P`, so modular inverses cannot be assumed.
- Values larger than `P`.
- Previous answer `P-1`, making the next state zero.
- Endpoints that require swapping.
- Query numbers 63, 64, and 65 around an encoded-block reset.
- Full-array and one-element ranges.
