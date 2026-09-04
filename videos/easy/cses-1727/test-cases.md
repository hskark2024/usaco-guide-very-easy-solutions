# Test-case walkthroughs

## Official example

For `n = 2`, `k = 3`, the nine maxima sum to `22`, so the expectation is `22/9 = 2.444444...`. The printed answer is `2.444444`.

## One child

For `n = 1`, `k = 4`, one uniform choice has average `(1+2+3+4)/4 = 2.5`. The program prints `2.500000`.

## Only one possible value

For any `n` with `k = 1`, every child gets one candy. The maximum is always one, so the output is `1.000000`.
