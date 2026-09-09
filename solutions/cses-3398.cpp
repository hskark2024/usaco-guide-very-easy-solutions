#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace {
constexpr long long MODULO = 1'000'000'007LL;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int size;
    cin >> size;

    vector<int> permutation(size);
    for (int &destination : permutation) {
        cin >> destination;
        --destination;  // Convert positions to zero-based indices once.
    }

    // Smallest prime factor values make every later cycle factorization fast.
    // For a prime x, smallest_prime_factor[x] remains x.
    vector<int> smallest_prime_factor(size + 1);
    for (int value = 0; value <= size; ++value) {
        smallest_prime_factor[value] = value;
    }
    for (int prime = 2; 1LL * prime * prime <= size; ++prime) {
        if (smallest_prime_factor[prime] != prime) {
            continue;
        }
        for (long long multiple = 1LL * prime * prime; multiple <= size;
             multiple += prime) {
            if (smallest_prime_factor[multiple] == multiple) {
                smallest_prime_factor[multiple] = prime;
            }
        }
    }

    vector<bool> visited(size, false);

    // maximum_exponent[p] records the largest exponent of prime p in any cycle
    // length.  Multiplying p to that exponent for every p constructs the LCM.
    vector<int> maximum_exponent(size + 1, 0);

    for (int start = 0; start < size; ++start) {
        if (visited[start]) {
            continue;  // This entire cycle was already counted.
        }

        int cycle_length = 0;
        int current = start;

        // A permutation gives every vertex one incoming and one outgoing edge,
        // so an unvisited start always walks through exactly one new cycle.
        while (!visited[current]) {
            visited[current] = true;
            ++cycle_length;
            current = permutation[current];
        }

        // Factor this cycle length and merge it into the LCM by retaining the
        // greatest exponent seen for each prime across all cycles.
        int remaining = cycle_length;
        while (remaining > 1) {
            int prime = smallest_prime_factor[remaining];
            int exponent = 0;
            while (remaining % prime == 0) {
                remaining /= prime;
                ++exponent;
            }
            maximum_exponent[prime] = max(maximum_exponent[prime], exponent);
        }
    }

    long long answer = 1;
    for (int prime = 2; prime <= size; ++prime) {
        // Taking the modulo is safe only after the prime exponents have been
        // finalized; reducing an intermediate LCM would lose factor information.
        for (int copy = 0; copy < maximum_exponent[prime]; ++copy) {
            answer = answer * prime % MODULO;
        }
    }

    cout << answer << '\n';
    return 0;
}
