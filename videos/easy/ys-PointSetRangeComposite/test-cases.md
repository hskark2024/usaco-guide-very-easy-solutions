# Test-case walkthroughs

## Order-sensitive pair

Apply `2x+1` and then `3x+4` to `x=5`: the answer is `37`. Reversing them gives `35`, so this case catches a swapped combiner.

## Single function

A range containing one leaf must return exactly that leaf's function.

## Point replacement

Query an interval, replace one middle function, and query again. Only compositions containing that position should change.

## Identity behavior

Padding beyond `n` uses `f(x)=x`, so a non-power-of-two array keeps the same answers.
