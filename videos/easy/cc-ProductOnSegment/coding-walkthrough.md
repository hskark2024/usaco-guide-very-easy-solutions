# C++ coding walkthrough

1. Reduce every array value modulo `P`.
2. Allocate one product row per binary level.
3. Build left suffixes and right prefixes around each block midpoint.
4. Return the original value for a singleton query.
5. Otherwise use the highest bit of `left XOR right` and multiply two table cells.
6. Decode the online query recurrence carefully, resetting from `B` every 64 queries.
7. Use `long long` for modular multiplication and state arithmetic.
