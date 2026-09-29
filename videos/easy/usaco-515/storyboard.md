# Storyboard and slide outline

Voice: Daniel, a calm male macOS voice for a 9th-grade audience. Each numbered narration paragraph matches one slide.

1. Show a solid viewing bar from zero to the target with no gaps allowed.
2. Draw multiple showing intervals and mark which one contains the current time.
3. Display a bitmask with used and unused movie posters.
4. Define `dp[mask]` as the farthest solid endpoint and highlight `dp[0]=0`.
5. Put a binary-search cursor on the latest showtime not after `t`.
6. Extend the colored coverage bar to the showing's end and set one bit.
7. Merge two paths into one subset, keeping the farther endpoint.
8. Trace the sample's three-movie chain to time one hundred.
9. Finish with the time and memory bounds.
