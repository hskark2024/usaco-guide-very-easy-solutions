# C++ coding walkthrough

1. Read cell values and the target into `long long`.
2. Compute the forward and backward move counts.
3. Allocate one XOR-frequency hash map per grid cell.
4. Write a forward recursive lambda with down and right branches.
5. Store a frequency when the forward move limit is reached.
6. Write a backward recursive lambda with up and left branches.
7. Correct the duplicated meeting cell in the complement formula.
8. Add the matching forward frequency to a 64-bit answer.
