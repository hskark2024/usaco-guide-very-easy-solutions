# Edge-case checklist

- `N = 1`, so the hierarchy contains only the director.
- Query starts at the director.
- Requested distance equals the employee's depth.
- Requested distance is one larger than the depth.
- Deep chain near the maximum size.
- Wide tree where many employees share one manager.
- Several set bits in `k`, requiring multiple shortcuts.
- Sentinel `0` is never printed as an employee number.
