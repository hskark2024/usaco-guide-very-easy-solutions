# Test-case walkthroughs

## Official query: `3 7 1`

The inner power is `7^1 = 7`. The outer power is `3^7 = 2187`, so the answer is `2187`.

## Official query: `15 2 2`

The reduced exponent is `2^2 = 4`. Then `15^4 = 50625`, matching the official output.

## Zero outer exponent: `8 0 5`

The true exponent is `0^5 = 0`, so the answer is `8^0 = 1`.

## Problem convention: `0 0 0`

The inner expression `0^0` is defined as `1`, so the whole expression is `0^1 = 0`.

## Zero base and zero true exponent: `0 0 3`

The inner expression is `0^3 = 0`, so the whole expression is `0^0 = 1` by the stated convention.
