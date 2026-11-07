# Test-case walkthroughs

## Crossing branches

In a balanced seven-vertex tree, use routes `4-5`, `4-6`, `5-7`, `2-2`, and `6-7`. Vertex 2 lies on the first four routes, so the answer is 4. This checks branch LCAs and a single-vertex route.

## LCA is an endpoint

For a route from an ancestor to its descendant, the ancestor must still be counted exactly once. The `-1` at the LCA and `-1` at its parent preserve that inclusion.

## LCA is the root

The second negative marker lands at sentinel vertex 0. The route counts the root but does not create a fake real ancestor.

## Long chain

Repeated routes from vertex 1 to vertex N make every vertex equally busy and verify the non-recursive traversal.
