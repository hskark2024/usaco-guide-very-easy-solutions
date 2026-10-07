# Test-case walkthroughs

For heights `1 3 8` with add cost 1 and expensive removal and movement, raising the shorter pillars is cheapest and the official answer is 12.

For the same heights with move cost 1, surplus bricks are transferred into missing spots and the official answer drops to 4.

If all pillars are already equal, choosing that height has zero deficit and zero surplus, so the answer is zero. If moving costs more than adding plus removing, the capped price forces the equivalent cheaper plan.
