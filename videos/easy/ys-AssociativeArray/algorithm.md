# Algorithm derivation

1. The full key range is too large for direct allocation.
2. At most one new key can be touched per update, so the number of stored positions is at most `Q`.
3. Store only assigned positions in a hash map.
4. Update with `map[key] = value`.
5. Lookup with `find` so missing keys do not get inserted.
6. Print zero for a missing key and the mapped value otherwise.
7. Use 64-bit key/value types and a mixed hash for robust expected performance.
