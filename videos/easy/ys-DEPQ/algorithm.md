# Algorithm derivation

1. The data structure must remain ordered, expose both extremes, and preserve duplicates.
2. A C++ `multiset<int>` satisfies all three requirements with a balanced tree.
3. Insert the initial `N` values.
4. For query `0 x`, call `insert(x)`.
5. For query `1`, print and erase the iterator returned by `begin()`.
6. For query `2`, use `prev(end())`, then print and erase that iterator.
7. Erase by iterator so exactly one copy disappears.
