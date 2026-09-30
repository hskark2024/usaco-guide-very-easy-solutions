# Test-case walkthroughs

The official sample is `1 2 3 4 1 4 3 2 1 6`. Wide strokes for colors one through four create the nested structure, then later paint repairs the center and final cell. The minimum is `6`.

A row containing one color needs one stroke, no matter how long it is. A row of all distinct colors needs one stroke per cell. For `1 2 1`, paint all three cells color one, then paint the middle color two, for two strokes.
