# Test-case walkthroughs

In the first official sample, the center has elevation one but is initially blocked from the sea. In year two, the top-middle boundary cell sinks and immediately exposes the center, so both disappear that year.

For a single cell of elevation three, the remaining area is one after years one and two, then zero from year three onward.

For one row, every cell is already on the boundary. Each cell therefore sinks exactly in its elevation year.

A low basin surrounded by boundary cells taller than `Y` remains dry throughout the requested years, even though its own elevation is small.
