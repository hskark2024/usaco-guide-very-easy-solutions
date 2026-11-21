# Test-case walkthroughs

## One vertex

The only vertex is the whole component's centroid, so it receives `A`.

## Five-node star

The center's removal leaves four components of size one. The center receives `A`; every leaf receives `B`. Each leaf-to-leaf path passes through the `A` center.

## Five-node chain

The middle vertex receives `A`. Each two-vertex half chooses one endpoint as `B`, and the remaining endpoint becomes `C`. Same-letter vertices lie in opposite halves and their path crosses `A`.

## Uneven branches

The centroid need not be the input root or the visually central drawing point. The subtree-size test chooses a vertex only when its largest remaining piece is at most half.
