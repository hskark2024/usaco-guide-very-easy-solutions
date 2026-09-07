# Test-case walkthroughs

## Official example: `24`

`24 = 2^3 * 3^1`. Exponent three fits costs `1+2`, and exponent one fits cost `1`, for `3` moves total.

## Identity: `1`

There is no prime power divisor to choose, so the answer is `0`.

## Official prime power: `64`

`64 = 2^6`, and `1+2+3=6`, so choose `2`, `4`, and `8` for `3` moves.

## Large prime: `1,000,000,007`

No small factor is found. The remaining prime has exponent one and contributes one move.

## Leftover copies: `256`

`256 = 2^8`. Costs `1+2+3=6` fit, but adding cost four would require ten copies. The answer is `3` with two exponent copies unused.
