# Algorithm derivation

Choose a payment subset of physical coins totaling K. Find every amount that can be formed by a further subset inside at least one such valid payment.

Use a bitset for each payment total p. Bit x in possible[p] records that some payment of p contains a marked subset totaling x. Start with possible[0][0]=true. For coin v and p descending from K to v, merge possible[p-v] and possible[p-v]<<v into possible[p]. The first source selects v for the payment only; the shifted source selects it for both payment and marked subset. Existing bits skip the coin. Read all set bits 0..K from possible[K].

## Why this works

Initially the empty payment and empty marked subset establish exactly state (0,0). Every assignment of a new coin puts it in one of three disjoint roles: unused, selected for the payment only, or selected for both the payment and its marked subset. The three transitions represent these roles and preserve a marked subset inside the payment. Conversely, removing the new coin from any feasible assignment gives a valid previous state represented by the transition. Descending payment totals ensure all source rows precede this coin. Induction proves the reachable-state invariant, so the final K row contains exactly the requested values.

## Cost

Time: O(NK⌈(K+1)/w⌉) bit-word operations, where w is the machine word width. The fixed bitset has 501 bits. Space: O(K²) bits, with K+1 rows. A plain boolean implementation would take O(NK²) time.
