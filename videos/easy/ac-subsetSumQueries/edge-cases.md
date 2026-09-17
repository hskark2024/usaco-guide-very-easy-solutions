# Edge-case checklist

- The target is unreachable: print `0`.
- Several balls have the same value: keep their subset choices distinct.
- A query value exceeds `K`: skip the table update but still print.
- Removing one of several equal values must leave the others represented.
- Addition scans downward so one inserted ball is not reused.
- Removal scans upward so recovered `new[s-x]` is available.
- Subtraction must be normalized after it becomes negative.
- Large duplicate counts can wrap around the modulus many times.
- Keep `ways[0] = 1`; it represents the empty subset.
