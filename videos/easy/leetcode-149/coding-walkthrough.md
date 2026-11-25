# C++ coding walkthrough

1. Store every coordinate in a `Point` with `long long` fields.
2. Write `normalized_direction` to compute differences, divide by `std::gcd`, and fix the sign.
3. Loop over each anchor.
4. Use `map<pair<long long,long long>,int>` for exact direction counts.
5. Update the best frequency whenever a key is incremented.
6. Add one for the anchor itself.
7. Print the global maximum from the local stdin/stdout wrapper.
