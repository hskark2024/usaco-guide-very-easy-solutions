#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    vector<int> queries(test_cases);
    int largest_query = 0;
    for (int &limit : queries) {
        cin >> limit;
        largest_query = max(largest_query, limit);
    }

    // Euler's totient sieve.  phi[y] is the number of x in [1, y] for which
    // gcd(x, y) equals 1 (with phi[1] = 1).
    vector<int> phi(largest_query + 1);
    for (int value = 0; value <= largest_query; ++value) {
        phi[value] = value;
    }
    if (largest_query >= 1) {
        phi[1] = 1;
    }

    for (int prime = 2; prime <= largest_query; ++prime) {
        // Untouched entries identify primes in the standard totient sieve.
        if (phi[prime] != prime) {
            continue;
        }
        for (int multiple = prime; multiple <= largest_query; multiple += prime) {
            phi[multiple] -= phi[multiple] / prime;
        }
    }

    // Count every unordered pair once by treating y as the larger endpoint.
    // Among x = 1..y, exactly phi[y] are coprime to y, so y - phi[y]
    // choices have gcd(x, y) > 1.  Prefix sums answer all limits instantly.
    vector<long long> non_coprime_pairs(largest_query + 1, 0);
    for (int y = 1; y <= largest_query; ++y) {
        non_coprime_pairs[y] =
            non_coprime_pairs[y - 1] + static_cast<long long>(y - phi[y]);
    }

    for (int case_number = 1; case_number <= test_cases; ++case_number) {
        cout << "Case " << case_number << ": "
             << non_coprime_pairs[queries[case_number - 1]] << '\n';
    }

    return 0;
}
