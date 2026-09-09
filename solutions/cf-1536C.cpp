#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <utility>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        int length;
        string plank;
        cin >> length >> plank;

        int diluc_count = 0;
        int kaeya_count = 0;

        // The key is a reduced D:K ratio. Its frequency among prefixes is also
        // the maximum number of equal-ratio pieces for the current prefix.
        map<pair<int, int>, int> ratio_frequency;

        for (int index = 0; index < length; ++index) {
            if (plank[index] == 'D') {
                ++diluc_count;
            } else {
                ++kaeya_count;
            }

            // gcd(x, 0) == x, so this same normalization correctly turns an
            // all-D prefix into (1, 0) and an all-K prefix into (0, 1).
            int common = gcd(diluc_count, kaeya_count);
            pair<int, int> reduced_ratio = {
                diluc_count / common,
                kaeya_count / common,
            };

            int pieces = ++ratio_frequency[reduced_ratio];
            if (index != 0) {
                cout << ' ';
            }
            cout << pieces;
        }
        cout << '\n';
    }

    return 0;
}
