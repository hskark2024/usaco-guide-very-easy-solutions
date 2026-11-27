# Storyboard

1. Plot many arrow hits and draw several candidate pair segments.
2. Wrap the point set with a convex hull and remove interior candidates.
3. Place parallel supporting lines on opposite hull sides.
4. Fix one hull edge and identify opposite vertex `j`.
5. Show triangle area increasing as `j` advances, then decreasing.
6. Update squared distances to both edge endpoints.
7. Rotate the edge and show `j` moving only forward.
8. Take the final square root and review complexity.
