# Edge-case checklist

- [x] Lookup before any update returns zero.
- [x] Reassigning a key replaces its old value.
- [x] An explicitly stored zero prints zero.
- [x] Keys and values at `10^18` fit the chosen 64-bit type.
- [x] Lookup uses `find` and does not insert missing keys.
- [x] Multiple independent keys retain their own latest values.
- [x] Reserved capacity is based on the operation count.
