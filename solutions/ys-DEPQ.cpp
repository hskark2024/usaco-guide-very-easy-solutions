#include <iostream>
#include <iterator>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    multiset<int> values;
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        values.insert(value);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int value;
            cin >> value;
            values.insert(value);
        } else if (type == 1) {
            auto smallest = values.begin();
            cout << *smallest << '\n';
            values.erase(smallest);
        } else {
            auto largest = prev(values.end());
            cout << *largest << '\n';
            values.erase(largest);
        }
    }
}
