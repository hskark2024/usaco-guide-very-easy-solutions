# C++ coding walkthrough

1. Store two powers and two prefix arrays in `DoubleRollingHash`.
2. Use half-open intervals so substring length is always `right-left`.
3. Pack two 32-bit modular residues into one `uint64_t` set key.
4. Handle `needle.size() > haystack.size()` before opening a window.
5. Fill two `array<int, 26>` frequency tables.
6. Compare the arrays, insert a hash for candidates, then slide.
7. Reserve the unordered set to reduce rehashing on large inputs.
8. Print only the final set size.
