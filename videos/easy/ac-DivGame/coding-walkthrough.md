# C++ coding walkthrough

1. Read `N` into a signed 64-bit integer.
2. Try divisors while `candidate*candidate <= N`.
3. Skip candidates that do not divide the remaining number.
4. Divide out every copy and count the prime exponent.
5. Spend exponent costs `1,2,3,...` while they fit.
6. Add one if a prime factor remains after the loop.
7. Print the sum of optimal operations across all primes.
