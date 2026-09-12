# Test-case walkthroughs

## Official sample

Input opponent sequence: `P P H P S`, with `K = 1`.

- Play Scissors for rounds 1–4: win against Paper in rounds 1, 2, and 4.
- Switch once to Hoof for round 5: win against Scissors.
- Total: `4`.

## No switches

For `H P S H` and `K = 0`, each fixed gesture wins against one opponent type. The best fixed gesture beats the two Hoofs, so the answer is `2`.

## Single round

For one Paper round, Bessie chooses Scissors initially. The starting choice costs no switch, so the answer is `1` even when `K = 0`.

## Verification oracle

For short random sequences, enumerate all `3^N` choices for Bessie, count adjacent gesture changes, discard choices above `K`, and directly score the rest. This is independent of the optimized recurrence.
