# Edge-case checklist

- No squares overlap.
- Exactly one overlapping pair.
- At least two overlapping pairs.
- Borders touch with `|dx|=K` or `|dy|=K`.
- Corners touch but area is zero.
- Equal x-coordinates or equal y-coordinates.
- One square offset by one unit from full overlap.
- Negative center coordinates.
- Maximum side length and coordinate magnitude.
- Many dense squares, requiring immediate exit on pair two.
