# C++ coding walkthrough

1. Define an integer `Point` so orientation remains exact.
2. Implement `cross`, `sign_of`, and inclusive `on_segment`.
3. Build `segments_intersect` with boundary cases before strict straddling.
4. In `point_to_segment_distance`, convert coordinate differences to `long double`.
5. Guard the zero-length case before division.
6. Compute and clamp projection parameter `t`.
7. Evaluate the four symmetric endpoint candidates.
8. Print with `fixed` and two decimal places.
