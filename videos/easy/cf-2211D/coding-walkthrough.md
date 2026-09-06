# C++ coding walkthrough

1. Precompute factorials and inverse factorials through `100,000`.
2. Define `choose(n,k)` with constant-time modular products.
3. Store each test case's `b[1..n]` in a mutable residual vector.
4. Create 29 zeroed frequency slots, one for every legal bit.
5. Loop `k` downward from `n` to `1`.
6. Read `residual[k]` as the newly discovered bitmask and record frequency `k` for its set bits.
7. Subtract `mask * choose(k,length)` from all smaller residual lengths.
8. Set each bit in the first `count_for_bit[bit]` answer elements.
9. Print spaces only between elements so every test case occupies one clean line.
