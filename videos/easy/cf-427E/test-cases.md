# Test-case walkthroughs

For positions `1 2 3` with capacity 6, one trip can collect everyone. Trying station positions 1, 2, and 3 gives total round-trip distances 4, 4, and 4, so the answer is 4.

With one criminal at position 0, building the station there arrests that criminal immediately and costs zero.

With capacity 1, each non-station criminal needs its own round trip. Duplicate coordinates still work because zero-length trips add nothing.
