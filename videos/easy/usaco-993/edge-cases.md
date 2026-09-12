# Edge-case checklist

- City 1 has no return cycle: the answer remains the stay-home value `0`.
- A cycle exists but its cost exceeds its rewards: still return `0`.
- Repeated cycles are profitable for several lengths before quadratic cost wins.
- Roads are directed; never add a reverse road implicitly.
- Rewards are earned on arrival, including repeated visits.
- Only states back at city 1 may become answers.
- Unreachable states must use a sentinel and be skipped before addition.
- Day 1000 is included; days beyond it cannot beat zero.
- Use `long long` for `C * day * day`.
