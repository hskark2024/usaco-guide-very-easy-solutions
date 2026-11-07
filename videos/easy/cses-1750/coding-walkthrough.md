# C++ coding walkthrough

1. `destination[planet][0]` stores the direct teleporter from the input.
2. Thirty fixed columns match the largest official query count.
3. Each preprocessing assignment reads a middle planet from level `j-1`, then follows that planet's same-level shortcut.
4. A query keeps one mutable `planet` and one `long long teleport_count`.
5. The bit loop applies only selected shortcuts; a zero count selects none.
6. Every table value is a real planet number, so no sentinel or bounds branch is required.
