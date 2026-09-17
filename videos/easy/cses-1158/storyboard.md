# Storyboard

1. **Book cards.** Display prices and page counts under a budget meter.
2. **Greedy fails.** Compare the 12-page book with the better 5-plus-8-page pair.
3. **DP state.** Reveal one slot for every available budget.
4. **Skip or buy.** Split the transition into its two exhaustive choices.
5. **Descending sweep.** Freeze the source slot while updating the destination.
6. **Sample trace.** Show the 4-cost and 5-cost books producing 13 pages.
7. **Correctness.** Partition selections by whether the current book is included.
8. **C++ and bounds.** Highlight `max`, loop direction, and `O(NX)`/`O(X)`.
