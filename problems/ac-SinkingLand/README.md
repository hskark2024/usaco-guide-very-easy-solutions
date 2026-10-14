# Sinking Land

- Official problem: [AtCoder ABC363 E](https://atcoder.jp/contests/abc363/tasks/abc363_e)
- USACO Guide ID: `ac-SinkingLand`
- Difficulty on the checked USACO Guide listing: Easy
- Topics: flood fill, bucket queue, minimax paths
- Solution: [`solutions/ac-SinkingLand.cpp`](../../solutions/ac-SinkingLand.cpp)

## Paraphrased summary

An elevation grid is surrounded by sea. The sea level rises by one each year. A low-enough cell sinks only when it is connected to the outside sea through boundary or already-sunken neighbors. Output the remaining land area after every requested year.

## Visualization

Think of every cell as having two locks:

1. the water must have reached the cell from the boundary;
2. the current year must be at least the cell's elevation.

When a cell first becomes sea-adjacent in year `t`, its earliest sinking year is `max(t, elevation)`. That single formula lets us schedule the entire flood.

```mermaid
flowchart TD
    B[Boundary cells touch sea at year 0] --> Q[Schedule at max(0, elevation)]
    Q --> Y[Process bucket for year y]
    Y --> S[Sink every cell in the bucket]
    S --> N[Each new neighbor first touches sea at y]
    N --> T[Schedule neighbor at max(y, elevation)]
    T --> Y
    Y --> A[Print remaining area]
```

## Approach

1. Create buckets `1..Y`, where bucket `y` holds cells whose earliest sinking year is `y`.
2. Schedule every boundary cell using its elevation, because it touches the sea at year zero.
3. For each year in order, process every cell in that bucket and decrement the remaining area.
4. When that cell sinks, each never-seen neighbor becomes sea-adjacent. Schedule it for `max(current year, neighbor elevation)`.
5. Continue processing newly appended same-year cells to capture the instantaneous chain reaction.
6. Print the remaining area after the bucket is exhausted.

Cells scheduled beyond `Y` need no bucket because they cannot change any requested answer.

## Correctness argument

Boundary cells are scheduled at their first possible year. Assume all cells processed before or during year `y` have their true earliest sinking times. When one sinks, an unseen neighbor becomes adjacent to the sea for the first time at `y`; it cannot sink before adjacency or before its elevation year, so `max(y, elevation)` is a lower bound. At exactly that year both requirements hold, so it is also achievable. Induction therefore gives every scheduled cell its exact sinking year. Subtracting each cell once makes every reported remaining area correct.

## Complexity

- Time: `O(HW + Y)` because every cell is scheduled and processed at most once.
- Space: `O(HW + Y)`.

## Verification notes

The test suite checks both official samples, compares random small grids with an independent per-year boundary flood fill, covers one-row and one-column grids, same-year cascades around high walls, and uses a million-cell stress grid.
