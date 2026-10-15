# Test-case walkthroughs

The official sample assigns cow 1 to event 1, cow 3 to event 2, and cow 2 to event 3. The first two skill scores total seven, which activates a six-point bonus and produces seventeen overall.

For one cow and no bonuses, the answer is exactly the single skill entry.

For two bonuses at the same prefix, a score may pass the first threshold, receive points, and then pass the second. Sorting thresholds captures this cascade.

Random instances with at most eight cows are checked against every assignment permutation.
