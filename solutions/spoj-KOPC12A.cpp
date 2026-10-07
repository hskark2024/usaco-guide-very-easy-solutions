#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;

    while (test_count--) {
        int building_count;
        cin >> building_count;

        vector<int> height(building_count);
        vector<int> change_cost(building_count);
        int largest_height = 0;

        for (int &value : height) {
            cin >> value;
            largest_height = max(largest_height, value);
        }
        for (int &value : change_cost) {
            cin >> value;
        }

        // If every building is changed to target_height, building i needs
        // |height[i] - target_height| brick changes.  Its own price is paid
        // for every change, so the total is a weighted sum of V shapes.
        auto total_cost = [&](int target_height) {
            long long answer = 0;
            for (int index = 0; index < building_count; ++index) {
                answer += 1LL * abs(height[index] - target_height)
                          * change_cost[index];
            }
            return answer;
        };

        // A sum of convex V-shaped functions is convex.  Therefore, when
        // cost(mid + 1) is at least cost(mid), no point to the right of mid
        // can start a better descending section; an optimum remains on the
        // left.  Otherwise the function is still descending, so we move right.
        int low = 0;
        int high = largest_height;
        while (low < high) {
            int middle = low + (high - low) / 2;
            if (total_cost(middle) <= total_cost(middle + 1)) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }

        // low is the first integer height at the bottom of the convex curve.
        cout << total_cost(low) << '\n';
    }

    return 0;
}
