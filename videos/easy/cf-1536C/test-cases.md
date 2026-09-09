# Test-case walkthroughs

## Official prefix: `DDK`

Reduced ratios are `(1,0)`, `(1,0)`, and `(2,1)`. Their running frequencies are `1 2 1`, so those are the answers.

## Alternating: `DKDK`

The two balanced prefixes end at lengths two and four. Ratio `(1,1)` appears twice by the end, so the last answer is two.

## All one letter: `DDDDDD`

Every prefix reduces to `(1,0)`. The running frequencies are `1 2 3 4 5 6`, matching one single-character piece per `D`.

## Single character: `K`

The ratio `(0,1)` appears once, so the answer is one.

## Mixed growth: `DKDKDDDDK`

Whenever a reduced ratio repeats, another equal-ratio chunk becomes possible. The official answers end with three when the final ratio returns for its third occurrence.
