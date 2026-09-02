# Storyboard

1. **Hook — impossible array**: Zoom from indexes `0, 1, 2` out to `10^18` and show a memory warning.
2. **Sparse insight**: Highlight only a few written positions among a huge empty range.
3. **Hash-map model**: Convert written cells into key-value cards and buckets.
4. **Update versus lookup**: Assignment inserts/overwrites; `find` returns a value or the default zero.
5. **Walkthrough**: Missing key `8`, set `8 -> 12`, overwrite with `99`.
6. **C++ details**: 64-bit integers, `find` instead of `operator[]`, reserve, custom hash.
7. **Proof and complexity**: Latest-value invariant, `O(Q)` expected time and `O(U)` space.
