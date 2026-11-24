# C++ coding walkthrough

1. Read the test count and six coordinates per query.
2. Cast before subtracting so each delta is computed as `__int128`.
3. Compute the two exact products and subtract them.
4. Compare the result only with zero; do not use slopes or division.
5. Print `LEFT`, `RIGHT`, or `TOUCH` from the sign.

The code is intentionally short, while comments preserve the geometric meaning of each expression.
