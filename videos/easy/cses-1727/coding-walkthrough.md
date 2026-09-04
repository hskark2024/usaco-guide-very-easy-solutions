# C++ coding walkthrough

1. Read `children` and `maximum_candies`.
2. Initialize a `long double expected` value to zero.
3. Loop `value` from one through `maximum_candies`.
4. Convert `(value-1)/maximum_candies` to `long double` before division.
5. Add `1 - pow(below, children)` for the current threshold.
6. Print with `fixed` and `setprecision(6)`.
