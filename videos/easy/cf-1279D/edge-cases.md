# Edge-case checklist

- [x] One child and one gift produces probability one.
- [x] All child lists are nonempty, so every modular inverse exists.
- [x] A gift appearing on many lists contributes its full frequency.
- [x] Disjoint lists produce only self-recipient successes.
- [x] Different list sizes receive different `1/k_x` weights.
- [x] No list repeats a gift, matching the meaning of the frequency count.
- [x] Total list size up to one million fits the stored vectors.
- [x] 64-bit products are reduced modulo `998,244,353`.
