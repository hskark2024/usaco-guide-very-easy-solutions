# Storyboard

1. **Rules and constraint.** Show the three gestures in a win cycle and a meter with at most `K` switches.
2. **Why greedy fails.** Animate winning every current round while the switch meter runs out.
3. **State definition.** Display a grid with switch counts as rows and three current gestures as columns.
4. **Two transitions.** Draw a straight stay arrow and two switch arrows into one destination state.
5. **Official sample.** Mark the winning plan `S, S, S, S, H` against `P, P, H, P, S` for four wins.
6. **Rolling memory.** Collapse many round layers into `previous` and `current` tables.
7. **Proof and complexity.** Highlight exhaustive stay-or-switch cases and `O(NK)` time.
