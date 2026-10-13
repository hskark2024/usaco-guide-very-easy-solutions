# Algorithm derivation

1. Split the array near its midpoint.
2. Generate all left-half and right-half subset sums, including zero.
3. Sort the right sums without removing duplicates.
4. For each left sum `s`, compute `target - s`.
5. Use `equal_range` to count that value in the right list.
6. Add all range sizes into a 64-bit answer.
