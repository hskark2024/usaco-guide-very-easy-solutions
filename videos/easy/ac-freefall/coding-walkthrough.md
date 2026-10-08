# C++ coding walkthrough

1. Read `A` and `B` as `long long`.
2. Create an `arrival_time(x)` lambda returning `long double`.
3. Add the linear setup time to `A / sqrtl(x+1)`.
4. Set the integer search range to zero through `A/B`.
5. Calculate both third-points without overflowing.
6. Keep the side containing the convex minimum.
7. Exhaustively scan the final short interval.
8. Print with `fixed` and fifteen digits after the decimal point.
