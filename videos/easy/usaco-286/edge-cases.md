# Edge-case checklist

- Fewer than three vertices cannot provide a valid internal rest stop.
- A balanced whole path may still lack a balanced internal split.
- Several valid rest stops must count the path only once.
- A centroid can be a rest stop only when it is not an endpoint.
- Same-branch endpoint pairs are deferred to recursive components.
- Stars and chains stress opposite tree shapes.
- The answer requires 64-bit storage.
- Iterative original-tree traversals avoid deep recursion at `N=100,000`.
