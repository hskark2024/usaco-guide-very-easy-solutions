# Algorithm derivation

1. Let `moves = N+M-2` and choose `first = floor(moves/2)`.
2. DFS from `(0,0)` for exactly `first` moves.
3. Store each partial XOR frequency in the map for its endpoint cell.
4. DFS backward from `(N-1,M-1)` for `moves-first` moves.
5. At meeting cell `(r,c)`, compute `needed = K XOR backward XOR grid[r][c]`.
6. Add the frequency of `needed` in that cell's forward map.
7. Print the total.
