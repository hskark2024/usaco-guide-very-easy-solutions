# Test-case walkthroughs

## Building one component

For vertices `0, 1, 2`, query `0 2` before any union: output `0`. Union `0 1`, then `1 2`. Query `0 2`: both find the same root, so output `1`.

## Redundant union

After `0`, `1`, and `2` are connected, union `0 2` again. Both endpoints already have the same root, so nothing changes.

## Separate components

Joining `3 4` must not affect the component containing `0, 1, 2`. A query `2 4` remains `0`.
