# Algorithm derivation

1. Reset `D`, `K`, and ratio frequencies for each test case.
2. Extend the current prefix by one character.
3. Increment its corresponding character count.
4. Divide both counts by their gcd to obtain a primitive ratio.
5. Increment the frequency of that reduced pair.
6. Print the new frequency as the current prefix answer.
