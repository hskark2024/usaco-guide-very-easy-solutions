# Algorithm derivation

1. Avoid floating-point angles because distinct directions may be extremely close.
2. Cut the circle at the required negative x-axis starting ray.
3. Assign region 0 to `y < 0`, region 1 to `y == 0 && x >= 0`, and region 2 to all remaining points.
4. Sort different regions by their integer region numbers.
5. Within one region, put `a` before `b` exactly when `a.x*b.y - a.y*b.x > 0`.
6. Treat a zero cross product as an allowed tie and use `stable_sort` for deterministic behavior.
7. Print the sorted coordinates.
