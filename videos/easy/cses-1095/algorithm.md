# Algorithm derivation

1. Express the exponent in binary.
2. Maintain the current power `a^(2^j)` as `base`.
3. When bit `j` is set, multiply that base power into `result`.
4. Square `base` after every bit and reduce modulo `1,000,000,007`.
5. Shift the exponent right to visit the next bit.
6. Start `result` at one so exponent zero is handled as the empty product.
7. Stop when no exponent bits remain.
