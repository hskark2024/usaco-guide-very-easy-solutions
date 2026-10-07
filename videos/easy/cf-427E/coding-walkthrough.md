# C++ coding walkthrough

1. Read the already sorted coordinates with fast iostream settings.
2. Allocate `left_cost` and `right_cost` as `long long` arrays.
3. During the left sweep, activate index `station - 1` when it is divisible by `M`.
4. Compute the left sum from active trip count and coordinate sum.
5. Reset the accumulators and sweep from the right.
6. Activate mirrored indices whose distance from `N-1` is divisible by `M`.
7. Scan all station indices for the minimum side-cost sum.
8. Multiply by two and print the round-trip distance.
