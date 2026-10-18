# Edge-case checklist

- Empty set with a k-th query.
- Duplicate insertions.
- Deleting a missing value.
- Count below a value already in the set is strict.
- Count below every value returns zero.
- Count above every value returns the set size.
- `K 1` on a nonempty set.
- `K` equal to or larger than the set size.
- Values at negative and positive one billion.
- A workload containing only `K` queries has no compressed coordinates.
