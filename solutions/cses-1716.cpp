#include <iostream>
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

    int children, apples;
    cin >> children >> apples;

    // Stars and bars: choose the positions of children - 1 separators.
    const int slots = children + apples - 1;
    vector<long long> factorial(slots + 1, 1);
    for (int value = 1; value <= slots; ++value) {
        factorial[value] = factorial[value - 1] * value % MOD;
    }

    long long denominator = factorial[children - 1] * factorial[apples] % MOD;
    long long answer = factorial[slots] * mod_pow(denominator, MOD - 2) % MOD;
    cout << answer << '\n';
}
