# Test-case walkthroughs

In the first official sample, choosing person one for the only position gives eighteen. Persons two and three are then the strongest two audience members, adding sixteen and ten, for a total of forty-four.

A useful conflict case gives one person both the highest audience score and a huge position score. The DP can sacrifice that audience value, use the person as a player, and promote the next-best nonplayer into the audience. Tied audience values are safe in any sort order because they add the same amount. Maximum-size testing checks the full `100000 * 128` state updates.
