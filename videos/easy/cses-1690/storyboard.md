# Storyboard and slide outline

Voice: Daniel, a calm male macOS voice for a 9th-grade audience. Each numbered narration paragraph matches one slide.

1. Draw a directed route from city 1 through every dot to city `N`.
2. Replace the visited-city drawing with a row of on/off bits.
3. Label a card `dp[mask][last]` and explain both coordinates.
4. Switch off `last` and draw incoming arrows from possible predecessors.
5. Split routes by their unique final flight, then merge their counts.
6. Animate the two valid orders in the four-city sample.
7. Cross out masks missing city 1 or reaching city `N` early.
8. Display state count, complexity, modulo, and verifier strategy.
