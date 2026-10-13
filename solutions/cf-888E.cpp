#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using int64 = long long;

// Enumerate all subset sums modulo modulus for one half of the input.
static vector<int64> make_residues(const vector<int64> &values,
                                   int begin, int end, int64 modulus) {
    vector<int64> residues = {0};  // Choosing nothing is allowed.
    for (int index = begin; index < end; ++index) {
        const int old_size = static_cast<int>(residues.size());
        for (int mask = 0; mask < old_size; ++mask) {
            residues.push_back((residues[mask] + values[index]) % modulus);
        }
    }
    return residues;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int length;
    int64 modulus;
    cin >> length >> modulus;

    vector<int64> values(length);
    for (int64 &value : values) {
        cin >> value;
        value %= modulus;
    }

    const int middle = length / 2;
    vector<int64> left = make_residues(values, 0, middle, modulus);
    vector<int64> right = make_residues(values, middle, length, modulus);
    sort(right.begin(), right.end());

    int64 answer = 0;
    for (int64 left_residue : left) {
        // We want the largest right residue that does not make the addition
        // wrap around modulo m.  The allowed limit is m - 1 - left_residue.
        // Such a value always exists because the empty right subset gives 0.
        const int64 limit = modulus - 1 - left_residue;
        auto first_too_large = upper_bound(right.begin(), right.end(), limit);
        --first_too_large;

        // This sum is below modulus, so taking modulo would not change it.
        // Any wrapped sum is smaller than left_residue, while pairing with the
        // empty right subset already achieves left_residue; it cannot improve
        // the optimum.
        answer = max(answer, left_residue + *first_too_large);
    }

    cout << answer << '\n';
    return 0;
}
