#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

constexpr long long MOD = 1'000'000'007;

long long mod_pow(long long base, long long exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1LL) result = result * base % MOD;
        base = base * base % MOD;
        exponent >>= 1LL;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int query_count;
    cin >> query_count;

    vector<pair<int, int>> queries(query_count);
    int largest_a = 0;
    for (auto &[a, b] : queries) {
        cin >> a >> b;
        largest_a = max(largest_a, a);
    }

    vector<long long> factorial(largest_a + 1, 1);
    vector<long long> inverse_factorial(largest_a + 1, 1);
    for (int value = 1; value <= largest_a; ++value) {
        factorial[value] = factorial[value - 1] * value % MOD;
    }

    inverse_factorial[largest_a] = mod_pow(factorial[largest_a], MOD - 2);
    for (int value = largest_a; value >= 1; --value) {
        inverse_factorial[value - 1] = inverse_factorial[value] * value % MOD;
    }

    for (const auto &[a, b] : queries) {
        long long answer = factorial[a] * inverse_factorial[b] % MOD;
        answer = answer * inverse_factorial[a - b] % MOD;
        cout << answer << '\n';
    }
}
