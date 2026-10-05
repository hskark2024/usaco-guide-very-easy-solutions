#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int employee_count, query_count;
    cin >> employee_count >> query_count;

    // 2^18 is below 200,000 and 2^19 is above it.  We keep one extra
    // level so every employee can be lifted all the way to the director.
    int levels = 1;
    while ((1 << levels) <= employee_count) {
        ++levels;
    }

    vector<int> depth(employee_count, 0);
    vector<vector<int>> up(levels, vector<int>(employee_count, 0));

    // The input guarantees that employee i's boss has a smaller number.
    // Therefore the boss's depth and complete jump table are already known
    // when employee i is read; no tree traversal is needed.
    for (int employee = 1; employee < employee_count; ++employee) {
        int boss;
        cin >> boss;
        --boss;
        up[0][employee] = boss;
        depth[employee] = depth[boss] + 1;

        for (int level = 1; level < levels; ++level) {
            int halfway = up[level - 1][employee];
            up[level][employee] = up[level - 1][halfway];
        }
    }

    auto lift = [&](int employee, int steps) {
        // Bit level in steps means that a jump of exactly 2^level is needed.
        for (int level = 0; level < levels; ++level) {
            if ((steps >> level) & 1) {
                employee = up[level][employee];
            }
        }
        return employee;
    };

    auto lowest_common_boss = [&](int first, int second) {
        // First make both employees stand at the same depth.  LCA comparisons
        // only work when their remaining distance to the root is equal.
        if (depth[first] < depth[second]) {
            swap(first, second);
        }
        first = lift(first, depth[first] - depth[second]);

        // If leveling made them equal, that employee is an ancestor of the
        // other one and is immediately the lowest common boss.
        if (first == second) {
            return first;
        }

        // Consider powers of two from largest to smallest.  Whenever the two
        // ancestors differ, taking that jump keeps both employees strictly
        // below their LCA while moving them as high as safely possible.
        for (int level = levels - 1; level >= 0; --level) {
            if (up[level][first] != up[level][second]) {
                first = up[level][first];
                second = up[level][second];
            }
        }

        // They are now distinct children of the answer.
        return up[0][first];
    };

    while (query_count--) {
        int first, second;
        cin >> first >> second;
        --first;
        --second;
        cout << lowest_common_boss(first, second) + 1 << '\n';
    }

    return 0;
}
