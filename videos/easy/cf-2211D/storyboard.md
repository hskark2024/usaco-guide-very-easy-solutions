# Storyboard

1. **Hook — reverse every subsequence AND**: Show an unknown array feeding sums for sizes `1..n`.
2. **One bit at a time**: Turn numbers into 29 rows of on/off switches.
3. **Count a bit's contribution**: Highlight `m` set positions and choose `k`, producing `2^bit * C(m,k)`.
4. **Start at the top**: Show `b[n]` exposing bits that occur in all `n` positions.
5. **Peel downward**: Subtract discovered binomial contributions and move from `k` to `k-1`.
6. **Canonical construction**: Place each recovered bit in the first `count[bit]` answer positions.
7. **Official example and complexity**: Compare `[7,7,7,1,0]` with another valid output and explain the 29-pass bound.
