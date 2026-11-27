# C++ coding walkthrough

1. Store coordinates as `long double` points.
2. Implement a feasibility lambda accepting an optional witness center.
3. Skip pairs beyond diameter `2R` and clamp the `acos` ratio.
4. Normalize the interval start, then add both original and shifted events.
5. Sort by angle and put entering events first on ties.
6. Start coverage at one, save the center as soon as it reaches `K`.
7. Use the maximum pair distance as a guaranteed feasible upper bound.
8. Run 80 binary-search iterations and print radius plus center precisely.
