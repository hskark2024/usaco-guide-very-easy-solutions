# Edge-case checklist

- `K=2`, where the answer is half the closest pair distance.
- `K=N`, requiring every household.
- Collinear households.
- Several households on the final circle boundary.
- Distance exactly `2R`, producing a zero-width angular interval.
- Angular interval crosses zero.
- Enter and exit events share an angle.
- Coordinates at zero or 10000.
- Maximum 500 households and output tolerance checks.
