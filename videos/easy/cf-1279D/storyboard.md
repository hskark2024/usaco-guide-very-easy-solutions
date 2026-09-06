# Storyboard

1. **Hook — the bot's three choices**: Animate first child, gift, and recipient as three levels of a probability tree.
2. **Why direct enumeration is too large**: Show the tree exploding toward one million list entries.
3. **Count gift popularity**: Label each gift with the number of child lists containing it.
4. **One child's contribution**: Sum gift frequencies and divide by that child's list size.
5. **Two uniform child choices**: Apply the outer `1/n^2` factor.
6. **Official example**: Trace frequencies for gifts `1` and `2`, producing probability `7/8`.
7. **Modular division and C++**: Replace division with inverses and review the two passes.
