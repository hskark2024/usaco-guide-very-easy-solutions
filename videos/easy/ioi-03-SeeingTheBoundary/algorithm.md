# Algorithm derivation

1. Translate each rock vertex relative to the observer.
2. Sort the directions by `atan2` only to locate the unique outside gap larger than 180 degrees.
3. Take the vertices after and before that gap as the counterclockwise tangent endpoints.
4. Intersect each tangent ray with the first square side using exact rational arithmetic.
5. Convert the hits to one counterclockwise perimeter coordinate.
6. Block integer indices from `ceil(start)` through `floor(end)`.
7. Split at `4N` when necessary, sort all intervals, and merge their inclusive union.
8. Return `4N - blocked_union_size`.
