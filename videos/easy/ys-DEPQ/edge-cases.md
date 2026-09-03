# Edge-case checklist

- [x] `N = 0` creates an empty multiset successfully.
- [x] Removal occurs only when nonempty, as guaranteed by the statement.
- [x] Duplicate values are stored and erased one at a time.
- [x] Negative and positive values sort naturally.
- [x] `begin()` is dereferenced only for a valid minimum query.
- [x] `end()` is never dereferenced; `prev(end())` selects the maximum.
- [x] Erasing uses an iterator rather than a key, avoiding removal of all equal values.
- [x] Official values fit in signed `int`.
