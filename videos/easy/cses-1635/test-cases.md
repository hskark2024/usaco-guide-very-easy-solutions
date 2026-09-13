# Test-case walkthroughs

## Official sample

Coins are `2, 3, 5`, and the target is `9`.

- Sequences ending in `2` come from total `7`.
- Sequences ending in `3` come from total `6`.
- Sequences ending in `5` come from total `4`.
- Their counts add to `8`.

## Order-sensitive example

With coins `1, 2` and target `4`, the sequences are `1+1+1+1`, `1+1+2`, `1+2+1`, `2+1+1`, and `2+2`. The answer is `5`, not `3`.

## Unreachable target

Coins `4, 6` cannot make target `5`, so every relevant transition begins at a zero state and the answer remains `0`.

## Independent verifier

For small random inputs, a recursive generator literally chooses the next coin and records every sequence that reaches the target. It stops a branch when the sum would become too large and compares the exact enumeration with the compiled program.
