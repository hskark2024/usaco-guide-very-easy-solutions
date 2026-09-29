# Algorithm derivation

1. Store each movie's duration and sorted showtimes.
2. Define `covered_until[mask]` as the farthest continuous endpoint from zero.
3. Set the empty mask to zero and every other state to unreachable.
4. From a reachable mask, try every unused movie.
5. Binary-search for its latest showtime not greater than the current endpoint.
6. If that showing ends later, update the mask with this movie added.
7. For every target-reaching mask, minimize `popcount(mask)`.
8. Return `-1` if no subset reaches the target.
