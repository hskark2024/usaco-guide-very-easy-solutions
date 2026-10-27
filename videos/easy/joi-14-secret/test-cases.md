# Test-case walkthroughs

## Official grader sample

With values `1 4 7 2 5 8 3 6`, the four queries produce `13`, `32`, `8`, and `13` under the grader's public order-sensitive operation.

## Singleton

A query such as `[5,5]` returns the original value `8` and makes no `Secret` call.

## Order-sensitive random oracle

For random arrays and ranges, fold values strictly from left to right with the public grader operation. This catches a reversed left suffix or right prefix even though the operation is associative.

## Maximum constraints

Initialize `N=1000` values and answer `Q=10,000` ranges, including wide ranges that saturate at one billion. Compare all answers with a direct fold.
