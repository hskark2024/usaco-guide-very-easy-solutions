# Edge-case checklist

- No book is affordable: answer `0`.
- One book fits exactly at the budget boundary.
- The optimum leaves some budget unused.
- Several books have the same price or page count.
- A less efficient-looking pair beats the best individual book.
- Process book indices separately even when their values match.
- Scan capacities downward to prevent repeated use.
- Keep zero as a valid empty-purchase value at every capacity.
- Maximum page totals fit in a 32-bit signed integer under the official constraints.
