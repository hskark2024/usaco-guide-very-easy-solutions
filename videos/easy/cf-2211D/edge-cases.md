# Edge-case checklist

- [x] An all-zero AND-array reconstructs all zeros.
- [x] `n=1` reconstructs the only element directly by its bits.
- [x] Several bits may share the same recovered frequency mask.
- [x] A bit present in all elements is discovered first at `k=n`.
- [x] A bit present once is discovered last at `k=1`.
- [x] Modular subtraction adds `MOD` after a negative result.
- [x] All 29 allowed bit positions are inspected.
- [x] Factorials cover the maximum summed `n` of 100,000.
- [x] Constructed values remain strictly below `2^29`.
- [x] Different valid constructions are accepted; exact sample output is unnecessary.
