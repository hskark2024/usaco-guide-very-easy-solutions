# Test-case walkthroughs

## Internal black node

On edges `1-2`, `1-3`, `2-4`, `2-5`, toggle node `2` black. Querying node `4` examines path `1, 2, 4` and returns `2`.

## Root wins

Toggle root `1` black too. Any root-path query now returns `1`, even when another black node is farther down.

## No candidate

Toggle all black vertices on a requested path back to white. Every segment-tree interval returns infinity, which converts to `-1`.

## Separate branch

If node `3` is black, a query at `4` must not see it because node `3` is outside path `1, 2, 4`.
