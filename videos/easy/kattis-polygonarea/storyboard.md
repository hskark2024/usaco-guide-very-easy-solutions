# Storyboard

1. Trace a polygon boundary clockwise and counterclockwise.
2. Arrange x and y coordinates in the visual shoelace pattern.
3. Highlight one edge term `x_i*y_next - y_i*x_next`.
4. Close the last vertex back to the first.
5. Reveal the sum as twice the signed area.
6. Use the sign to choose `CCW` or `CW`.
7. Format even doubled area as `.0` and odd as `.5`.
8. Review concave shapes, exact arithmetic, and `O(N)` time.
