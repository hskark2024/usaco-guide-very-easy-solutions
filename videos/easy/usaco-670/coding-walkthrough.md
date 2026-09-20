# C++ coding walkthrough

1. Detect `checklist.in` so the same executable supports USACO and local stdin.
2. Store points one-based and compute squared distance with `long long`.
3. Allocate two `(H+1) × (G+1)` tables filled with a safe infinity.
4. Seed only the required starting state at `H1`.
5. Guard each transition by whether another cow of that breed remains.
6. Never use `G0`; the G-ending block requires `j > 0`.
7. Print only the all-visited H-ending state.
