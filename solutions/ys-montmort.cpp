#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long mod;
    cin >> n >> mod;

    // d[k] counts permutations of k items with no fixed point.
    long long d_two_back = 1 % mod;  // d[0]
    long long d_one_back = 0;        // d[1]

    for (int k = 1; k <= n; ++k) {
        long long current;
        if (k == 1) {
            current = d_one_back;
        } else {
            current = ((k - 1LL) * ((d_one_back + d_two_back) % mod)) % mod;
            d_two_back = d_one_back;
            d_one_back = current;
        }

        if (k > 1) cout << ' ';
        cout << current;
    }
    cout << '\n';
    return 0;
}
