# Test-case walkthroughs

## First official example

For three of the four households, a circle centered at `(4,3.5)` with radius `2.5` is optimal. The sweep finds an angle where the anchor plus two intervals overlap.

## Two households

Points `(0,0)` and `(2,0)` require radius `1`. At the optimum their event intervals touch at one angle, so processing entry before exit is necessary.

## Right triangle

For `(0,0)`, `(4,0)`, and `(0,3)`, the minimum circle uses the hypotenuse as a diameter and has radius `2.5`.

## Interval across zero

When a valid center-angle interval begins just below zero and ends just above it, duplicating the interval places one complete copy around `2*pi` for an ordinary sweep.
