# Test-case walkthroughs

## Official sample opening

The initial total of `[1,2,3,4,5]` is `15`. Applying `100*x+101` to positions two and three changes them to `401` and `501`, so the first three values sum to `404`.

## Composition order

Start with `x=2`. Apply `3*x+4`, producing `10`, then apply `5*x+6`, producing `56`. The combined rule must be `15*x+26`; reversing the composition gives a different answer and catches the most common bug.

## Constant replacement

Although the official multiplier is positive, the algebraic identity is easy to test with multiplier one and addend zero. Identity updates must leave sums and tags unchanged.

## Maximum command count

Use `N=Q=500,000`, repeat full-range affine updates, and finish with a total query. This checks running time, modular reduction, interval-length multiplication, and deep lazy composition.
