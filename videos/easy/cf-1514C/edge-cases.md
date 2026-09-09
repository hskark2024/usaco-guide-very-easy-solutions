# Edge-case checklist

- [x] `n=2` keeps the single value `1`.
- [x] Prime `n` may require removing `n-1`.
- [x] Composite `n` rejects every non-unit.
- [x] Product is reduced after every multiplication.
- [x] The removed residue is guaranteed to be in the usable list.
- [x] Output remains strictly increasing.
- [x] A second output line is printed even if the list were empty.
- [x] Multiplication uses 64-bit arithmetic before taking modulo.
