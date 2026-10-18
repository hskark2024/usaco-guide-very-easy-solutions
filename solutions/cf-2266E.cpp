#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int MAX_VALUE = 200'000;

    // smallest_prime[x] lets every number be factorized quickly.  We only
    // need distinct prime divisors in the transition, so repeated copies of
    // one prime are skipped later.
    vector<int> smallest_prime(MAX_VALUE + 1);
    for (int value = 2; value <= MAX_VALUE; ++value) {
        if (smallest_prime[value] != 0) {
            continue;
        }
        for (int multiple = value; multiple <= MAX_VALUE; multiple += value) {
            if (smallest_prime[multiple] == 0) {
                smallest_prime[multiple] = value;
            }
        }
    }

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int element_count, limit;
        cin >> element_count >> limit;

        vector<int> values(element_count);
        for (int &value : values) {
            cin >> value;
        }

        // cost[x] is the fewest operations needed to replace one x by a
        // collection whose every value is at most limit.  Values at most the
        // limit already satisfy the goal and therefore cost zero.
        vector<long long> cost(element_count + 1, 0);
        for (int value = limit + 1; value <= element_count; ++value) {
            cost[value] = numeric_limits<long long>::max();

            int remaining = value;
            while (remaining > 1) {
                const int prime = smallest_prime[remaining];

                // One operation on value using prime creates exactly prime
                // independent copies of value / prime.  Each copy needs the
                // already-computed optimal smaller-state cost.
                cost[value] = min(
                    cost[value], 1LL + prime * cost[value / prime]
                );

                // Remove every occurrence so this prime divisor is tried
                // exactly once. Trying it again would be the same choice.
                while (remaining % prime == 0) {
                    remaining /= prime;
                }
            }
        }

        // Operations on descendants of different original values never
        // interact, so the optimal costs add.
        long long answer = 0;
        for (int value : values) {
            answer += cost[value];
        }
        cout << answer << '\n';
    }

    return 0;
}
