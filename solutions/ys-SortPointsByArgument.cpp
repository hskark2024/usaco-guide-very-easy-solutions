#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

int region(const Point &point) {
    if (point.y < 0) return 0;
    if (point.y == 0 && point.x >= 0) return 1;
    return 2;
}

bool angle_less(const Point &a, const Point &b) {
    int a_region = region(a);
    int b_region = region(b);
    if (a_region != b_region) return a_region < b_region;

    long long cross = a.x * b.y - a.y * b.x;
    return cross > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> points(n);
    for (Point &point : points) cin >> point.x >> point.y;

    stable_sort(points.begin(), points.end(), angle_less);

    for (const Point &point : points) {
        cout << point.x << ' ' << point.y << '\n';
    }
}
