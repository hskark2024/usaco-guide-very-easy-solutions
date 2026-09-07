# Test-case walkthroughs

## Official query: `3 4`

The exponent is binary `100`, so only `3^4` is selected. Repeated squaring gives `3^2=9` and `3^4=81`.

## Official query: `2 8`

The single set bit represents eight. Three squarings produce `2^8=256`.

## Zero exponent: `7 0`

No binary bits are set, the loop never runs, and the result stays `1`.

## Stated convention: `0 0`

The same empty-product rule returns `1`, matching the problem's convention.

## Zero base: `0 9`

The first set bit multiplies the result by zero, so the final answer is `0`.
