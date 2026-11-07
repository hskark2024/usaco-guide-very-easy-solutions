#include <array>
#include <iostream>
#include <vector>
using namespace std;

// CSES 1687: Company Queries I
//
// A query may ask for an ancestor one billion levels above an employee.  We
// cannot walk through every manager.  Binary lifting stores the manager after
// 1, 2, 4, 8, ... steps, so the set bits of k describe at most 30 useful jumps.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int employee_count, query_count;
    cin >> employee_count >> query_count;

    // The official distance is at most N <= 200,000, so bits 0 through 29 are
    // more than enough. Employee 0 is a sentinel meaning "above the director";
    // every jump from it stays at 0 and safely absorbs all later shortcuts.
    constexpr int LOG = 30;
    vector<array<int, LOG>> manager(employee_count + 1);

    for (int employee = 2; employee <= employee_count; ++employee) {
        cin >> manager[employee][0];
    }

    // If 2^(level-1) steps reach middle, another stored jump of the same size
    // reaches exactly 2^level steps above the original employee.
    for (int level = 1; level < LOG; ++level) {
        for (int employee = 1; employee <= employee_count; ++employee) {
            const int middle = manager[employee][level - 1];
            manager[employee][level] = manager[middle][level - 1];
        }
    }

    while (query_count--) {
        int employee;
        long long distance;
        cin >> employee >> distance;

        // Decompose distance into powers of two.  Once employee becomes 0,
        // later jumps remain at the sentinel and the final answer is -1.
        for (int level = 0; level < LOG; ++level) {
            if ((distance >> level) & 1LL) {
                employee = manager[employee][level];
            }
        }

        cout << (employee == 0 ? -1 : employee) << '\n';
    }
    return 0;
}
