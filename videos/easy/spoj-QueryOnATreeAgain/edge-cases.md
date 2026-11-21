# Edge-case checklist

- One vertex, initially white.
- Root toggled black and back to white.
- The queried vertex itself is the only black candidate.
- Black vertices exist only outside the requested path.
- Several black vertices on one path; choose minimum depth.
- Query path entirely inside the root heavy chain.
- Query crosses many light edges.
- Repeated toggles of the same vertex.
- Maximum-size chain without recursive DFS.
