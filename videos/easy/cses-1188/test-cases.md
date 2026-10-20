# Test-case walkthroughs

## Official example

`001011` becomes `000011`, so the first answer is four. Flipping position two produces `010011`, whose longest runs have length two. Flipping position five produces `010001`, whose three zeroes give answer three.

## Uniform string

Flipping an interior bit splits one long run into two; flipping it back must restore the full length.

## Alternating string

Every initial run has length one. A flip can join equal neighbors on both sides and create length three.

## Repeated endpoint flip

This checks one-sided merging and confirms the update does not rely on both neighbors existing.
