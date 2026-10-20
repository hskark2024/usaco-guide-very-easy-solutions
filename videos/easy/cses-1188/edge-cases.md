# Edge-case checklist

- A one-bit string.
- All zeroes or all ones.
- Perfectly alternating bits.
- The first or last position flips.
- The same position flips repeatedly.
- A flip joins matching runs on both sides.
- A flip splits the unique longest run.
- String length is not a power of two.
- Both `n` and update count equal `200,000`.
