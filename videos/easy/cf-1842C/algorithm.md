# Algorithm derivation

1. Define `kept[0]=0`; all later values begin at infinity.
2. Maintain `best_before[color]`, initially infinity.
3. At position `i` with color `c`, compute `keep = kept[i-1]+1`.
4. Compute `erase = best_before[c]`.
5. Set `kept[i] = min(keep, erase)`.
6. Update `best_before[c] = min(best_before[c], kept[i-1])`.
7. Output `N-kept[N]`.
