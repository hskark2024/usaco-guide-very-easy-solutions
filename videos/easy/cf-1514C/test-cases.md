# Test-case walkthroughs

## Official example: `n=5`

All values `1,2,3,4` are coprime with five. Their product is `4 mod 5`, so remove `4`. The remaining product `1*2*3=6` is `1 mod 5`, and the answer has length three.

## Official example: `n=8`

The usable values are `1,3,5,7`. Their product is `1 mod 8`, so all four are printed.

## Minimum modulus: `n=2`

Only `1` is available and its product is already one.

## Composite modulus: `n=6`

Only `1` and `5` are coprime with six. Their product is five, so remove `5` and keep `1`.

## Prime modulus: `n=7`

All values are units. The algorithm computes their total residue and removes it only when necessary.
