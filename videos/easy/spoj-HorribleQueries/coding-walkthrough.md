# C++ coding walkthrough

1. `FenwickTree::add` records one boundary event and `prefix_sum` accumulates all events through an index.
2. `RangeAddRangeSum::add_boundary` updates the coefficient and correction trees together.
3. `add_range` creates opposite events at `left` and `right+1`.
4. `prefix_sum` evaluates the linear contribution formula.
5. `range_sum` subtracts the prefix before the query from the prefix at its right edge.
6. Build a fresh pair of trees for every test case because each array starts at zero.
7. Use `long long` for values, corrections, and answers.
