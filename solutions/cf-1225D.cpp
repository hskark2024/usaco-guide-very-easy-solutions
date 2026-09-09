#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

using Signature = vector<pair<int, int>>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int count, power;
    cin >> count >> power;

    vector<int> values(count);
    int maximum_value = 1;
    for (int &value : values) {
        cin >> value;
        maximum_value = max(maximum_value, value);
    }

    // Build the smallest-prime-factor table once. It lets every later value be
    // factored by repeatedly removing a known prime instead of trial dividing
    // by every possible candidate.
    vector<int> smallest_prime(maximum_value + 1);
    for (int value = 2; value <= maximum_value; ++value) {
        if (smallest_prime[value] != 0) {
            continue;
        }
        smallest_prime[value] = value;
        if (1LL * value * value > maximum_value) {
            continue;
        }
        for (int multiple = value * value; multiple <= maximum_value;
             multiple += value) {
            if (smallest_prime[multiple] == 0) {
                smallest_prime[multiple] = value;
            }
        }
    }

    map<Signature, long long> seen;
    long long answer = 0;

    for (int original : values) {
        int remaining = original;
        Signature signature;
        Signature needed_partner;

        // A product is a perfect k-th power exactly when every prime exponent
        // in that product is divisible by k. Exponent multiples of k therefore
        // carry no useful information and are erased from the signature.
        while (remaining > 1) {
            int prime = smallest_prime[remaining];
            int exponent = 0;
            while (remaining % prime == 0) {
                remaining /= prime;
                ++exponent;
            }

            int residue = exponent % power;
            if (residue == 0) {
                continue;
            }

            // This value contributes `residue` copies of prime modulo k. Its
            // partner must contribute k-residue copies so their sum is k.
            signature.push_back({prime, residue});
            needed_partner.push_back({prime, power - residue});
        }

        // Only earlier values are stored, so every valid pair is counted once
        // with its right endpoint at the current array position.
        auto matching = seen.find(needed_partner);
        if (matching != seen.end()) {
            answer += matching->second;
        }
        ++seen[signature];
    }

    cout << answer << '\n';
    return 0;
}
