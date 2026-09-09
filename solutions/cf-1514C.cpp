#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int modulus;
    cin >> modulus;

    vector<int> usable;
    long long product = 1;

    // Any chosen number must be coprime with n. If a chosen value shared a
    // prime factor with n, then the complete product would share that factor
    // too and could not possibly be congruent to 1 modulo n.
    for (int value = 1; value < modulus; ++value) {
        if (gcd(value, modulus) != 1) {
            continue;
        }

        usable.push_back(value);

        // Reduce after every multiplication. Both factors are below 1e5, so
        // long long is already more than enough, but the reduction also keeps
        // the running value equal to the residue we care about.
        product = product * value % modulus;
    }

    // If all units already multiply to 1, taking all of them is optimal.
    // Otherwise, `product` itself is one of the units above. Removing it makes
    // the remaining product product * inverse(product) == 1 (mod n).
    // We never need to remove more than this single value.
    if (product != 1) {
        vector<int> filtered;
        filtered.reserve(usable.size() - 1);
        for (int value : usable) {
            if (value != product) {
                filtered.push_back(value);
            }
        }
        usable.swap(filtered);
    }

    cout << usable.size() << '\n';
    for (size_t index = 0; index < usable.size(); ++index) {
        if (index != 0) {
            cout << ' ';
        }
        cout << usable[index];
    }
    cout << '\n';
    return 0;
}
