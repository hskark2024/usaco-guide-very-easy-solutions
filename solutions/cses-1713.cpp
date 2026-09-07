#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int query_count;
    cin >> query_count;

    // Read first so the sieve only grows as large as today's largest query.
    vector<int> values(query_count);
    int maximum_value = 1;
    for (int &value : values) {
        cin >> value;
        maximum_value = max(maximum_value, value);
    }

    // smallest_prime_factor[x] stores one prime divisor of x. Starting with
    // zero lets us recognize primes the first time the sieve sees them.
    vector<int> smallest_prime_factor(maximum_value + 1, 0);
    for (int candidate = 2; candidate <= maximum_value; ++candidate) {
        if (smallest_prime_factor[candidate] != 0) {
            continue;  // A smaller prime already marked this composite.
        }

        smallest_prime_factor[candidate] = candidate;

        // Multiples below candidate^2 already have a smaller prime factor.
        // Use a 64-bit product so the square cannot overflow accidentally.
        if (1LL * candidate * candidate > maximum_value) {
            continue;
        }
        for (int multiple = candidate * candidate;
             multiple <= maximum_value;
             multiple += candidate) {
            if (smallest_prime_factor[multiple] == 0) {
                smallest_prime_factor[multiple] = candidate;
            }
        }
    }

    for (int value : values) {
        int remaining = value;
        int divisor_count = 1;

        // If x = p1^e1 * p2^e2 * ..., a divisor independently chooses an
        // exponent from 0 through ei for every prime. The choice counts
        // therefore multiply as (e1+1)(e2+1)... .
        while (remaining > 1) {
            const int prime = smallest_prime_factor[remaining];
            int exponent = 0;

            // Consume the whole group of equal prime factors at once.
            while (remaining % prime == 0) {
                remaining /= prime;
                ++exponent;
            }

            divisor_count *= exponent + 1;
        }

        // For value 1 the loop is empty and divisor_count stays 1, exactly
        // accounting for its only positive divisor.
        cout << divisor_count << '\n';
    }

    return 0;
}
