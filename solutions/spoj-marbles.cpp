#include <algorithm>
#include <iostream>
using namespace std;

long long binomial(int n, int k) {
    // C(n, k) = C(n, n-k), so use the shorter product.
    k = min(k, n - k);
    long long result = 1;

    for (int step = 1; step <= k; ++step) {
        // The division is exact at every step. A 128-bit temporary prevents
        // the multiply-before-divide expression from overflowing even though
        // the problem guarantees that the final answer fits signed 64 bits.
        const __int128 enlarged =
            static_cast<__int128>(result) * (n - k + step);
        result = static_cast<long long>(enlarged / step);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int marble_count, color_count;
        cin >> marble_count >> color_count;

        // Give one marble to every color first. The remaining marbles can be
        // distributed freely, which is the stars-and-bars value below.
        cout << binomial(marble_count - 1, color_count - 1) << '\n';
    }

    return 0;
}
