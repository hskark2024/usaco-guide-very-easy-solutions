# Edge-case checklist

- [x] A one-character prefix produces one piece.
- [x] All-`D` prefixes reduce to `(1,0)`.
- [x] All-`K` prefixes reduce to `(0,1)`.
- [x] Equivalent ratios such as `(1,1)` and `(2,2)` share a key.
- [x] Unequal ratios such as `(2,1)` and `(3,1)` remain separate.
- [x] Frequency state is reset between test cases.
- [x] Output spacing has no leading or trailing problems.
- [x] Total input length of `500,000` fits comfortably in linear storage.
