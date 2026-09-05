#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr long long MOD = 1'000'000'007;
constexpr int MAX_N = 200'000;

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

    // Every test case uses the same modulus and n never exceeds MAX_N, so one
    // global preprocessing pass supports every combination query.
    vector<long long> factorial(MAX_N + 1, 1);
    vector<long long> inverse_factorial(MAX_N + 1, 1);
    for (int value = 1; value <= MAX_N; ++value) {
        factorial[value] = factorial[value - 1] * value % MOD;
    }

    // Invert only MAX_N!, then derive all smaller inverse factorials in a
    // backward pass: 1/(i-1)! = i/i!.
    inverse_factorial[MAX_N] = mod_pow(factorial[MAX_N], MOD - 2);
    for (int value = MAX_N; value >= 1; --value) {
        inverse_factorial[value - 1] = inverse_factorial[value] * value % MOD;
    }

    auto choose = [&](int n, int r) -> long long {
        if (r < 0 || r > n) return 0;
        long long result = factorial[n] * inverse_factorial[r] % MOD;
        return result * inverse_factorial[n - r] % MOD;
    };

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int n, tuple_size, allowed_difference;
        cin >> n >> tuple_size >> allowed_difference;

        vector<int> values(n);
        for (int &value : values) cin >> value;
        sort(values.begin(), values.end());

        long long answer = 0;
        int right = 0;

        // Count each valid tuple once by declaring its leftmost sorted index
        // to be the tuple's minimum. The two-pointer window [left, right)
        // contains every value no more than k above that minimum.
        for (int left = 0; left < n; ++left) {
            if (right < left + 1) right = left + 1;

            // right only moves forward over the whole test case, making the
            // scan linear after sorting.
            while (right < n && values[right] - values[left] <= allowed_difference) {
                ++right;
            }

            // The minimum at index left is already selected. Choose the other
            // tuple_size - 1 indices from the following values in the window.
            const int available_after_minimum = right - left - 1;
            answer += choose(available_after_minimum, tuple_size - 1);
            if (answer >= MOD) answer -= MOD;
        }

        cout << answer << '\n';
    }
}
