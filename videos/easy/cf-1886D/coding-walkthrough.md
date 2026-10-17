# C++ coding walkthrough

1. Read `N`, query count, and the length `N-1` record.
2. Compute modular inverses with binary exponentiation.
3. Build a product from question marks after index zero.
4. Put answer printing in a small lambda.
5. Convert each one-based update position to zero-based.
6. Remove an old question-mark factor only when the position is positive.
7. Add a new question-mark factor under the same condition.
8. Update the string before printing.
9. Keep the product alive even while a leading question mark makes the displayed answer zero.
