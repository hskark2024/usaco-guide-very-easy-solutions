# Edge-case checklist

- `k = 0`, so the starting planet is the answer.
- `k = 10^9`, using the highest supported bits.
- One planet with a self-loop.
- Every planet is a self-loop.
- One cycle containing all planets.
- A long tail entering a short cycle.
- Several disconnected functional-graph components.
- Repeated queries from the same starting planet.
