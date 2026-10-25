# Test-case walkthroughs

## Official sample pattern

After the first three updates, position eight contains `80`, so the first query reports `80`. Adding `14` on positions five through seven produces `508` across positions four through eight.

## One position

On an array of length one, adding `7` on `[1,1]` and querying `[1,1]` must return `7`. This checks the stopping event at `n+1`.

## Separate test cases

Run one case with several updates followed by a new case queried immediately. The second answer must be zero because its Fenwick trees are newly constructed.

## Maximum arithmetic

Add `10,000,000` to all `100,000` positions `99,999` times. The total is about `10^17`, proving every calculation needs 64-bit integers.
