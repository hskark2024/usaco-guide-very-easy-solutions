# Algorithm derivation

1. For each visit `(a,b)`, append event `(a,+1)` and event `(b,-1)`.
2. Sort the events by timestamp.
3. Initialize `current=0` and `answer=0`.
4. For every event, add its change to `current`.
5. Set `answer=max(answer,current)`.
6. Print `answer`.

At every sweep position, `current` equals processed arrivals minus processed departures, which is the number of active visits.
