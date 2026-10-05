# C++ coding walkthrough

1. Read `n` and `q`, then compute enough binary-lifting levels.
2. Allocate `depth` and `up[level][employee]` arrays.
3. Treat employee 1 as its own ancestor at every level.
4. While reading each boss, compute the employee's depth and jump row.
5. Write a `lift(employee, steps)` helper that reads the bits of `steps`.
6. In the LCA helper, swap so the first employee is never shallower.
7. Level the pair and handle the ancestor case immediately.
8. Scan levels backward, taking only jumps whose destinations differ.
9. Convert zero-based answers back to the one-based employee numbers.
