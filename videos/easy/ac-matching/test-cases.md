# Test-case walkthroughs

For the first official sample, man one has two choices. Following the compatible unused choices through all three rows produces exactly three full-mask paths.

An identity matrix has only the diagonal choices, so each state has one useful transition and the answer is one. If a man has no compatible unused woman, that state has no outgoing edge. A one-by-one zero matrix therefore returns zero. An all-ones matrix returns `N!` modulo `1,000,000,007`.
