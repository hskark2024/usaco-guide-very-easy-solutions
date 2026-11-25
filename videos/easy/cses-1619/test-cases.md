# Test-case walkthroughs

## Official sample

Visits `[5,8]`, `[2,4]`, and `[3,9]` produce a peak of `2` because the last two overlap from time 3 to time 4.

## No overlap

Visits `[1,2]`, `[3,4]`, and `[5,6]` never share time, so the running total never exceeds `1`.

## Nested visits

Visits `[1,10]`, `[2,9]`, `[3,8]`, and `[4,7]` create four consecutive arrivals before any departure. The answer is `4`.

## Large times

Times near one billion behave exactly like small times because they are only sorted and compared.
