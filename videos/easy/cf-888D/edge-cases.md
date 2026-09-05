# Edge-case checklist

- [x] Zero mismatches contributes the identity permutation.
- [x] Exactly one mismatch contributes zero.
- [x] Two mismatches are exactly one swap of the chosen pair.
- [x] The loop includes `m=k`.
- [x] The derangement table covers every allowed `k <= 4`.
- [x] Combination multiplication and the final answer use 64-bit integers.
- [x] Requiring a derangement prevents counting the same permutation in two `m` groups.
