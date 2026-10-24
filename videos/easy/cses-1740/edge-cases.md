# Edge-case checklist

- All segments are horizontal.
- All segments are vertical.
- One horizontal crosses many verticals.
- One vertical crosses many horizontals.
- Horizontal query range contains no compressed x-coordinate.
- Negative and positive coordinates appear together.
- Input endpoints arrive in decreasing order.
- Several disjoint verticals share one x-coordinate.
- The answer is zero.
- The answer exceeds signed 32-bit range.
- The input contains `100,000` segments.
