# Storyboard

1. **Hook — rotate from the origin**: Rays point toward scattered dots as a sweep line turns counterclockwise.
2. **Why not `double atan2`**: Show two nearly identical rays and a rounding warning.
3. **Cross product**: Display `a.x*b.y - a.y*b.x` with a positive-turn diagram.
4. **The wraparound problem**: Highlight the circular cut at the negative x-axis.
5. **Three regions**: Color lower half-plane, nonnegative x-axis/origin, and upper-through-negative axis.
6. **Compass walkthrough**: Order down, right, up, left.
7. **Ties**: Place `(1,1)`, `(2,2)`, and duplicate points on one ray.
8. **Code and complexity**: Show the comparator and `O(N log N)` result.
