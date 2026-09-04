#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int children, maximum_candies;
    cin >> children >> maximum_candies;

    // E[max] = sum_{value=1}^k P(max >= value).
    long double expected = 0.0L;
    for (int value = 1; value <= maximum_candies; ++value) {
        long double below = static_cast<long double>(value - 1) / maximum_candies;
        expected += 1.0L - pow(below, children);
    }

    cout << fixed << setprecision(6) << expected << '\n';
}
