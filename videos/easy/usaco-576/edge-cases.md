# Edge-case checklist

- One vertex and routes whose endpoints are both that vertex.
- Both endpoints are identical.
- One endpoint is the LCA.
- The root is the LCA.
- Star-shaped tree.
- Maximum-depth chain without recursive DFS.
- Many duplicate routes.
- A vertex value large enough to require the chosen numeric type.
- Parent sentinel `0` is accumulated but never considered as the answer.
