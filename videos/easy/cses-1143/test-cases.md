# Test-case walkthroughs

## Official opening

Capacities start `3 2 4 1 5 5 2 6`. A request of four skips the first two hotels and uses hotel three. The next request of four uses hotel five because hotel three now has zero rooms.

## Exact fit

A hotel with capacity five accepts a request of five and becomes zero. It cannot accept later positive groups.

## No valid hotel

When the root maximum is below the request, output zero and do not update any capacity.

## Earliest among many

If several hotels work, left-first descent always returns the smallest index.
