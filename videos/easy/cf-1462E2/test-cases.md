# Test-case walkthroughs

## Official example: `1 2 4 3`, `m=3`, `k=2`

After sorting, the array is `1 2 3 4`. With minimum index at value 1, choose both later values from `2,3`, giving one tuple. With minimum index at value 2, choose both from `3,4`, giving another. Other windows are too short, so the answer is `2`.

## Duplicate values: `1 1 1 1`, `m=2`, `k=1`

All index pairs are valid even though their values are equal. The contributions are `C(3,1)+C(2,1)+C(1,1)+C(0,1) = 3+2+1+0 = 6`.

## One-element tuples

When `m=1`, each left index chooses zero additional elements. Since `C(c,0)=1`, all `n` single-index tuples are counted.

## Window too small

If fewer than `m-1` later elements are within distance `k`, the combination helper returns zero automatically.
