# C++ coding walkthrough

1. Use one-based indexing to match the prefix definition.
2. Allocate `kept` and `best_before` arrays with an unreachable sentinel.
3. Initialize the empty prefix with zero survivors.
4. Read the keep transition from `kept[i-1]`.
5. Read the delete transition from the current color's shortcut.
6. Store their minimum in `kept[i]`.
7. Only afterward, update the color shortcut with `kept[i-1]`.
8. Print total balls minus minimum survivors.
