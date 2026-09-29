# C++ coding walkthrough

1. Store each cow's three values as `long long`.
2. Allocate `height` and `safety` arrays with `1<<N` cells.
3. Use `numeric_limits<long long>` to seed the empty stack safely.
4. Recover subset height from its lowest set bit.
5. Loop through every selected cow as the possible top cow.
6. Skip an unreachable lower subset before doing arithmetic.
7. Subtract the top cow's weight, apply her strength limit, and maximize.
8. Print the best tall-enough safety or the exact required failure message.
