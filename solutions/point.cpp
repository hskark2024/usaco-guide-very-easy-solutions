#include <iostream>
using namespace std;

// CSES 2189: Point Location Test
//
// The signed cross product of vectors P1->P2 and P1->P3 tells which side P3
// occupies.  Positive means a counterclockwise (left) turn, negative means a
// clockwise (right) turn, and zero means all three points are collinear.
// __int128 keeps the subtraction exact even at the coordinate limits.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        long long x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        const __int128 dx_line = static_cast<__int128>(x2) - x1;
        const __int128 dy_line = static_cast<__int128>(y2) - y1;
        const __int128 dx_point = static_cast<__int128>(x3) - x1;
        const __int128 dy_point = static_cast<__int128>(y3) - y1;
        const __int128 cross = dx_line * dy_point - dy_line * dx_point;

        if (cross > 0) {
            cout << "LEFT\n";
        } else if (cross < 0) {
            cout << "RIGHT\n";
        } else {
            cout << "TOUCH\n";
        }
    }
    return 0;
}
