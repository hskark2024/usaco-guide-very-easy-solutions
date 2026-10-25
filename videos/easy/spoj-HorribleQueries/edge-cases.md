# Edge-case checklist

- One-element arrays and one-element update ranges.
- Updates beginning at index one, where the correction is zero.
- Updates ending at `n`, whose stopping event is stored at `n+1`.
- Queries before any updates.
- Many overlapping and nested additions.
- Multiple test cases, ensuring no state leaks between them.
- Maximum update values repeated enough to exceed 32-bit totals.
- Inclusive endpoints on both updates and queries.
