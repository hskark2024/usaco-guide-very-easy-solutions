# 2003 — Seeing the Boundary

- Official problem: [IOI 2003 — Seeing the Boundary](https://ioinformatics.org/files/ioi2003problem6.pdf)
- USACO Guide ID: `ioi-03-SeeingTheBoundary`
- Difficulty on the checked USACO Guide listing: Easy
- Listing evidence: [Sweep Line module at Guide commit `70bfb31`](https://github.com/cpinitiative/usaco-guide/blob/70bfb314cd0be2e8102215a8a3efb0a8cc558a06/content/5_Plat/Sweep_Line.problems.json)
- Topics: radial sweep, convex geometry, interval union, exact fractions
- Solution: [`solutions/ioi-03-SeeingTheBoundary.cpp`](../../solutions/ioi-03-SeeingTheBoundary.cpp)

## Paraphrased summary

An observer stands inside a square field whose boundary has a post at every integer meter. Convex polygonal rocks block some viewing directions. Count how many of the `4N` distinct boundary posts remain visible; a ray through a rock vertex is blocked too.

## Visualization

Imagine rotating a flashlight around the observer. One rock occupies a continuous wedge between its two tangent rays. Extend those rays to the square boundary. They cut out one circular interval of fence posts, and the answer is the total number of posts minus the union of every rock's interval.

```mermaid
flowchart LR
    V[rock vertices] --> A[sort viewing angles]
    A --> G[largest outside angular gap]
    G --> T[two tangent rays]
    T --> P[exact perimeter fractions]
    P --> I[inclusive integer post interval]
    I --> M[merge all blocked intervals]
    M --> C[4N minus blocked posts]
```

## Approach

1. Translate every rock vertex by the observer's position and sort its angle.
2. Because the observer is outside the convex rock, its rays fit inside an angle smaller than 180 degrees. The largest cyclic gap is outside the rock; the vertices on its two sides are the tangents.
3. Extend each tangent ray to the first square side it hits. Represent the hit as an exact rational position on a counterclockwise perimeter scale from `0` through `4N`.
4. The blocked integer posts run from `ceil(start)` through `floor(end)`, inclusively. Split an interval if it wraps across position zero.
5. Sort and merge every blocked interval, then subtract the merged integer length from `4N`.

## Why it is correct

A convex polygon viewed from an exterior point subtends one continuous angular interval whose endpoints are tangent rays. A boundary post is obscured by that rock exactly when its viewing ray lies in this closed interval; closed endpoints correctly handle the rule that alignment with a rock vertex is not visible. Boundary traversal around a convex square has the same circular order as viewing angle, so mapping the tangents to perimeter positions preserves the entire blocked interval. `ceil(start)` and `floor(end)` select exactly its integer post positions. Finally, interval union counts a post once even when several rocks block the same direction. Therefore the subtraction leaves exactly the visible posts.

## Complexity

If `P` is the total number of rock vertices and `R` is the number of rocks:

- Time: `O(P log 20 + R log R)`, effectively `O(P + R log R)` because each rock has at most 20 vertices.
- Memory: `O(P + R)` while reading and storing intervals.

## Verification notes

The official sample returns `319`. Independent tests enumerate every fence post on small fields and use exact segment intersection against every polygon edge. They cover tangent rays through posts, wraparound intervals, observers near different sides, multiple rocks, and randomized rectangles.
