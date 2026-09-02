# Algorithm derivation

1. Connectivity queries need component identity, not an explicit path.
2. Represent every component by one root in a parent forest.
3. `find(x)` follows parents to the root and compresses the traversed path.
4. `unite(a, b)` finds both roots and, if distinct, attaches the smaller tree to the larger.
5. `connected(a, b)` is true exactly when the two roots match.

Path compression and union by size preserve membership while keeping the trees shallow.
