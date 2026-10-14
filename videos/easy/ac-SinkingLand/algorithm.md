# Algorithm derivation

1. Make one bucket for every requested year.
2. Mark boundary cells sea-adjacent at year zero.
3. Schedule each boundary cell at its elevation if that year is within the horizon.
4. Process years from `1` through `Y`.
5. Sinking a cell reduces the remaining area by one.
6. Every unseen neighbor first becomes sea-adjacent in the current year.
7. Schedule that neighbor at `max(current year, elevation)`.
8. Continue through cells appended to the current bucket for same-year cascades.
9. Print the remaining area after each bucket is empty.
