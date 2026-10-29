# Algorithm derivation

The judge asks for any path below a generous limit, not the optimum. Split the x-axis into width-1000 strips. Sort strips left to right, but alternate increasing and decreasing y order inside them.

Horizontal moves stay small inside each strip. Vertical movement telescopes instead of resetting by one million at every boundary, giving a total safely below the required limit.
