# C++ coding walkthrough

1. `vector<array<int, LOG>> manager` stores every shortcut contiguously per employee.
2. Level zero is read directly for employees `2..N`; zero-initialization gives the director and sentinel correct missing parents.
3. The nested preprocessing loops fill longer jumps from shorter ones.
4. Each query keeps one mutable `employee` and scans all 30 bit positions.
5. A set bit applies `manager[employee][level]`; the sentinel makes extra checks unnecessary.
6. The final ternary prints `-1` for sentinel zero and the employee otherwise.
