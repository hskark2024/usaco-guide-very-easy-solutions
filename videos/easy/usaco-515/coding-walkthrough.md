# C++ coding walkthrough

1. Read each duration and its already sorted showtime vector.
2. Allocate `covered_until` for all `1<<N` masks and fill it with `-1`.
3. Seed the empty state with endpoint zero.
4. Skip unreachable states and already-used movie bits.
5. Call `upper_bound(showtimes, current_time)` and step back once.
6. Add the movie duration to that showing's start.
7. Update only when the finish is later than current coverage.
8. Use `__builtin_popcount` for every target-reaching subset.
9. Print the minimum count or `-1`.
