# Algorithm derivation

Make math counts positive and economics counts negative. A valid subarray becomes an ordered pair of prefix sums with difference `K`.

Convert every query `[l,r]` to the prefix-index window `[l-1,r]`. Use Mo's algorithm to move between windows. A new right prefix matches old values `current-K`; a new left prefix matches old values `current+K`. Coordinate compression supports constant-time frequency updates.
