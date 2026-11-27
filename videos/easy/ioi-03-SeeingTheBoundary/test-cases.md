# Test-case walkthroughs

## Official sample

The observer is at `(60,50)` in a `100` by `100` field. The five-vertex rock creates one blocked angular wedge. Its inclusive post interval contains 81 posts, so `400-81=319` are visible.

## Tangent through a post

If a tangent ray lands exactly on an integer perimeter coordinate, both fraction numerator and denominator divide evenly. Ceiling and floor both include that post, matching the special visibility rule.

## Wraparound

A rock whose wedge crosses perimeter position zero creates an unrolled interval ending beyond `4N`. Split it into a suffix and prefix before merging.

## Overlapping shadows

Two separated rocks can hide some of the same posts. Interval union counts the shared portion only once.
