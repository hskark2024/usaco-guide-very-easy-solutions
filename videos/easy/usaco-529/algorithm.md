# Algorithm derivation

1. Build the answer left to right in a string used as a stack.
2. Precompute powers for two modular rolling hashes.
3. Save a prefix hash after every character currently in the stack.
4. After an append, only the newest suffix can become forbidden.
5. If the stack is long enough, extract its last `|T|` characters' hashes.
6. Compare them with the forbidden word's two hashes.
7. Confirm matching candidates byte for byte, then pop `|T|` characters and their hash states.
8. Print the stack after the source is exhausted.

The stack represents the completely censored version of every processed prefix.
