# Test-case walkthroughs

## Official-style example

For heights `10 30 40 20`, the DP values are `0, 20, 30, 30`. The final move from height `30` to `20` gives total cost `30`.

## Two equal stones

For `10 10`, the only jump costs `0`, so the answer is `0`.

## Skipping helps

For `10 100 10`, moving directly from the first stone to the third costs `0`; visiting the middle would cost `180`.

## Mixed route

For `30 10 60 10 60 50`, the route `1 -> 3 -> 5 -> 6` costs `40`.
