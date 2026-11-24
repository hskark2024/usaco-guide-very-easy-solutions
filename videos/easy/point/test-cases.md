# Test-case walkthroughs

## Official left case

`P1=(1,1)`, `P2=(5,3)`, `P3=(2,3)` gives vectors `(4,2)` and `(1,2)`. Cross `4*2-2*1=6`, so print `LEFT`.

## Official right case

For `P3=(4,1)`, the second vector is `(3,0)`. Cross `4*0-2*3=-6`, so print `RIGHT`.

## Collinear case

For `P3=(3,2)`, cross `4*1-2*2=0`, so print `TOUCH`.

## Reversed viewing direction

Swapping `P1` and `P2` negates the cross product, exchanging left and right as expected.
