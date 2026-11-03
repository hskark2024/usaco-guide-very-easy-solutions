# Test-case walkthroughs

## Official example

The first query walks from hole 1 through the row and exits after seven jumps at hole 8. After changing hole 1's power to 3, only its block is rebuilt and the next query uses five jumps.

## Block boundary

If a jump lands on the first hole of the next block, the first summary ends at the old block and the next summary begins exactly at the destination. No jump is skipped or counted twice.

## Long chain

With all powers equal to one, a literal query takes `N` steps. Block shortcuts consume the same path in only about `sqrt(N)` transitions.
