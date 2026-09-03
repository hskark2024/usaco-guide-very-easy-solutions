# Edge-case checklist

- [x] The origin `(0,0)` is assigned angle zero.
- [x] Positive and negative x-axis points land on the correct sides of the circular cut.
- [x] Vertical up and down vectors sort correctly.
- [x] Multiple points on the same ray compare as an allowed tie.
- [x] Duplicate points compare as an allowed tie.
- [x] Negative coordinates require no special multiplication rule.
- [x] Products and their difference fit in signed 64-bit integers under official limits.
- [x] The comparator returns false for equal directions, preserving strict weak ordering.
