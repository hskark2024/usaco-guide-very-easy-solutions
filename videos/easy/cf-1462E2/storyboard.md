# Storyboard

1. **Hook — choose close values**: Highlight triples whose tallest and shortest bars differ by at most `k`.
2. **Sort the array**: Rearrange bars from shortest to tallest so valid ranges become continuous windows.
3. **Fix one minimum index**: Pin the left dot and extend the right boundary through `minimum+k`.
4. **Choose the rest**: Show `C(window size minus 1, m minus 1)` choices around the pinned dot.
5. **No double counting**: Color each tuple according to its unique leftmost selected sorted index.
6. **Fast combinations**: Fill factorial and inverse-factorial arrays once through 200,000.
7. **C++ and complexity**: Trace the two pointers, duplicate values, `m=1`, and `O(n log n)` time.
