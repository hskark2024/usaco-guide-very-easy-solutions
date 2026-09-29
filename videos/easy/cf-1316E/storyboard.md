# Storyboard and slide outline

Voice: Daniel, a calm male macOS voice for a 9th-grade audience. Each numbered narration paragraph matches one slide.

1. Show candidate cards with one audience score and several position scores.
2. Highlight a person whose player value beats their audience value.
3. Sort cards by audience strength and circle the first available `k` nonplayers.
4. Display a seven-bit position mask and a best-score label.
5. Move the current card into each possible empty position.
6. Calculate `processed - popcount(mask)` for the nonplayer choice.
7. Remove fixed player cards and show that the audience prefix is optimal.
8. Display time, memory, and the `P≤7` reason the method scales.
