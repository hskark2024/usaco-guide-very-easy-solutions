# Test-case walkthroughs

With robots at `2 R` and `4 L`, both positions have even parity. They move toward each other and meet at coordinate three after one second.

With robots at `1 L` and `3 L`, both reach toward wall zero. The first reflects, and they meet after `(1+3)/2 = 2` seconds.

With robots at `1 R` and `6 R` in a corridor of length ten, their parities differ. They can cross only at half-integer coordinates, so both answers are `-1`.

For one robot, neither parity group contains a partner. Its output is always `-1`.
