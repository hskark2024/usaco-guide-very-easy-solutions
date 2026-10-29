#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

// CodeChef SEGPROD: Product on the Segment by Modulo
//
// Q can be as large as 20,000,000, so even an O(log N) segment-tree query is
// too expensive.  A disjoint sparse table spends O(N log N) time once and
// then answers every immutable inclusive range in O(1).  Unlike prefix
// products, this method never divides, so P may be composite and array values
// may share factors with P (or even be zero).
class DisjointSparseTable {
public:
    DisjointSparseTable(const vector<int> &values, int modulus)
        : original(values), mod(modulus) {
        const int n = static_cast<int>(values.size());

        // Level k handles queries whose endpoints first differ at bit k.
        int level_count = 0;
        while ((1LL << level_count) < n) ++level_count;
        products.assign(level_count, vector<int>(n));

        for (int level = 0; level < level_count; ++level) {
            const int half = 1 << level;
            const int block = half << 1;

            // Each block is split at mid.  Store every suffix on the left
            // half and every prefix on the right half.
            for (int mid = half; mid < n; mid += block) {
                const int left = mid - half;
                const int right = min(n, mid + half);

                products[level][mid - 1] = values[mid - 1];
                for (int i = mid - 2; i >= left; --i) {
                    products[level][i] = multiply(
                        values[i], products[level][i + 1]
                    );
                }

                products[level][mid] = values[mid];
                for (int i = mid + 1; i < right; ++i) {
                    products[level][i] = multiply(
                        products[level][i - 1], values[i]
                    );
                }
            }
        }
    }

    int query(int left, int right) const {
        // A singleton does not cross a split, so read it directly.
        if (left == right) return original[left];

        // The highest differing bit identifies the unique level where left
        // lies in a left half and right lies in the matching right half.
        const int level = 31 - __builtin_clz(left ^ right);
        return multiply(products[level][left], products[level][right]);
    }

private:
    vector<int> original;
    vector<vector<int>> products;
    int mod;

    int multiply(int left, int right) const {
        // Each factor is below 1e9, so signed 64-bit multiplication is safe.
        return static_cast<int>(1LL * left * right % mod);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        int n, modulus, query_count;
        cin >> n >> modulus >> query_count;

        vector<int> values(n);
        for (int &value : values) {
            long long input_value;
            cin >> input_value;
            value = static_cast<int>(input_value % modulus);
        }

        // A fresh pair is supplied at query 0, 64, 128, ... .  The extra
        // element promised by the statement always supplies the right base.
        vector<int> encoded(query_count / 64 + 2);
        for (int &value : encoded) cin >> value;

        DisjointSparseTable table(values, modulus);

        long long x = 0;
        int previous_left = 0;
        int previous_right = 0;
        for (int query_index = 0; query_index < query_count; ++query_index) {
            int left;
            int right;
            if (query_index % 64 == 0) {
                const int block = query_index / 64;
                left = static_cast<int>((encoded[block] + x) % n);
                right = static_cast<int>((encoded[block + 1] + x) % n);
            } else {
                left = static_cast<int>((previous_left + x) % n);
                right = static_cast<int>((previous_right + x) % n);
            }

            if (left > right) swap(left, right);
            const int answer = table.query(left, right);

            // The next query depends on both endpoints before sorting only
            // through their sorted values, exactly as the statement defines.
            previous_left = left;
            previous_right = right;
            x = (answer + 1LL) % modulus;
        }

        cout << x << '\n';
    }
    return 0;
}
