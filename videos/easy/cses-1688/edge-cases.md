# Edge-case checklist

- [ ] one employee queried with itself
- [ ] director paired with any employee
- [ ] one employee is the other's boss
- [ ] one employee is a distant ancestor of the other
- [ ] siblings with the same direct boss
- [ ] employees in different top-level branches
- [ ] both endpoints at very different depths
- [ ] chain-shaped hierarchy of maximum length
- [ ] query requiring several lifting bits
- [ ] repeated identical queries
