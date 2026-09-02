# C++ coding walkthrough

1. Read the operation count as `int`.
2. Declare an `unordered_map<uint64_t, uint64_t, SplitMix64Hash>`.
3. Reserve capacity before processing operations.
4. For type zero, read the value and assign `values[key] = value`.
5. For type one, call `find(key)`.
6. Print zero if the iterator equals `end`; otherwise print `it->second`.

The custom hash uses SplitMix64 plus a runtime seed. It changes bucket placement without changing key equality or stored values.
