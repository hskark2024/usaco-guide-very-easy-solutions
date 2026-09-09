# Test-case walkthroughs

## Official sample

For `k=3` and values `1,3,9,8,24,1`, the five valid pairs multiply to cubes. In particular, signatures for `3` and `9` complement each other, while `1` and `8` have empty signatures because both are already cubes.

## Empty signatures

With `k=2`, values `1`, `4`, and `9` all have empty signatures. Every pair among them has a square product.

## Simple complements

For `k=3`, `2` has signature `(2,1)` and `4` has `(2,2)`. Together their exponent sum is three, so their product eight is a cube.

## Nonmatching primes

For `k=2`, `2` needs another factor of two. The value `3` carries the wrong prime, so `2*3` is not a square.

## Duplicate values

Distinct indices are separate choices. The frequency map counts every earlier matching occurrence.
