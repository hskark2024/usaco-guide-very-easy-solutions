#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Kattis: Polygon Area
//
// The shoelace sum is twice the signed area.  Its magnitude gives the area,
// while its sign reveals whether the listed vertices travel counterclockwise
// or clockwise.  We keep the entire computation integral and format the final
// half unit ourselves, so no floating-point rounding is needed.
struct Point {
    long long x;
    long long y;
};

static string to_decimal(__int128 value) {
    // Only nonnegative magnitudes are passed here.
    if (value == 0) return "0";
    string digits;
    while (value > 0) {
        digits.push_back(static_cast<char>('0' + value % 10));
        value /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int vertex_count;
    while (cin >> vertex_count && vertex_count != 0) {
        vector<Point> polygon(vertex_count);
        for (Point &point : polygon) cin >> point.x >> point.y;

        __int128 twice_signed_area = 0;
        for (int i = 0; i < vertex_count; ++i) {
            const Point &current = polygon[i];
            const Point &next = polygon[(i + 1) % vertex_count];

            // Each directed edge contributes one shoelace term.  Including
            // the last-to-first edge closes the polygon automatically.
            twice_signed_area += static_cast<__int128>(current.x) * next.y -
                                 static_cast<__int128>(current.y) * next.x;
        }

        cout << (twice_signed_area > 0 ? "CCW " : "CW ");
        const __int128 magnitude = twice_signed_area >= 0
                                       ? twice_signed_area
                                       : -twice_signed_area;

        // magnitude / 2 is the integer part; parity chooses .0 or .5.
        cout << to_decimal(magnitude / 2)
             << (magnitude % 2 == 0 ? ".0\n" : ".5\n");
    }
    return 0;
}
