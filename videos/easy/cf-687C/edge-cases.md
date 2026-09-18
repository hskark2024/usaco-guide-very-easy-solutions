# Edge-case checklist

- [ ] Include inside sums zero and K.
- [ ] Treat equal values as distinct physical coins.
- [ ] A coin above K cannot fit any positive-valued payment.
- [ ] Process payment rows downward to prevent reuse.
- [ ] A marked coin must also be part of the payment.
- [ ] Read only the final payment row K; do not union unrelated rows.
- [ ] The statement guarantees a valid payment; implementation also handles none by printing zero.
- [ ] K=500 fits bit indices 0 through 500.
