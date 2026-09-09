#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    // Read every query first.  This lets us build the totient table only as
    // far as this input needs, rather than assuming a fixed judge limit.
    vector<int> queries(test_cases);
    int largest_query = 0;
    for (int &value : queries) {
        cin >> value;
        largest_query = max(largest_query, value);
    }

    // Initially phi[x] = x.  Each prime p will replace the factor p in phi[x]
    // by p - 1 for every multiple x of p.  Performing
    //     phi[x] -= phi[x] / p
    // is an integer-safe form of multiplying by (1 - 1/p).
    vector<int> phi(largest_query + 1);
    for (int value = 0; value <= largest_query; ++value) {
        phi[value] = value;
    }

    // The problem explicitly defines phi(1) as 1.  The sieve loop starts at
    // 2, so preserving this base case requires no further special handling.
    if (largest_query >= 1) {
        phi[1] = 1;
    }

    for (int candidate = 2; candidate <= largest_query; ++candidate) {
        // A number is still equal to its initial value exactly when no smaller
        // prime divided it.  Therefore it is prime and must update its multiples.
        if (phi[candidate] != candidate) {
            continue;
        }

        for (int multiple = candidate; multiple <= largest_query;
             multiple += candidate) {
            phi[multiple] -= phi[multiple] / candidate;
        }
    }

    // All expensive work is shared.  Each original test case is now one lookup.
    for (int value : queries) {
        cout << phi[value] << '\n';
    }

    return 0;
}
