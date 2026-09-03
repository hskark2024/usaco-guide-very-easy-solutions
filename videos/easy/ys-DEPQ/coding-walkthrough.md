# C++ coding walkthrough

1. Include `<set>` for `multiset` and `<iterator>` for `prev`.
2. Read `n` and `q`, then insert each starting value into `multiset<int> values`.
3. Read the operation type inside the query loop.
4. Type zero reads one more integer and inserts it.
5. Type one saves `values.begin()`, prints its value, and erases that iterator.
6. Type two saves `prev(values.end())`, prints its value, and erases that iterator.

The problem guarantee removes the need for empty-case output behavior, so the implementation stays focused on the three specified operations.
