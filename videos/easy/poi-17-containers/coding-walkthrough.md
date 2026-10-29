# C++ coding walkthrough

1. Set the small-step threshold to 320.
2. Group small operations by step as `(start, stop)`.
3. Simulate each large-step placement immediately.
4. For each used small step, clear one difference buffer.
5. Add start and stop events.
6. Sweep positions and inherit from `position - step`.
7. Add active counts into the final answer and print it.
