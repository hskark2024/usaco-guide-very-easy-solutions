# Edge-case checklist

- Query has one checkpoint, so distance is zero.
- Query has two checkpoints, so no skip is legal.
- The best saving is zero.
- Several interior checkpoints have the same saving.
- Consecutive checkpoints share coordinates.
- Update the first or last checkpoint.
- Update one position repeatedly.
- Coordinates are negative or at the allowed extremes.
