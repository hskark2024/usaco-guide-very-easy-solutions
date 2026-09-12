# Edge-case checklist

- `K = 0`: all rounds must use one fixed gesture.
- `N = 1`: the initial gesture is free and can always win the only round.
- All opponent gestures are identical: no switch is needed.
- The best strategy uses fewer than `K` switches: maximize over every allowed count.
- Rapidly alternating opponent gestures: the DP must respect the switch budget.
- Impossible exact-switch states: use a negative sentinel and never add to it.
- USACO file I/O and standard-input fallback both work.
