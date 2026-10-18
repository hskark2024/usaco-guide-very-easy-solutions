# Edge-case checklist

- One hotel and one group.
- A request exactly equals a hotel's capacity.
- Every hotel is too small, so output zero.
- Several hotels work; choose the first.
- Earlier hotels become too small after previous groups.
- Capacities and requests may reach one billion.
- The internal power-of-two tree has unused leaves.
- Output spacing remains valid for one or many groups.
