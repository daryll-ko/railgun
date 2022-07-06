# `mod_pow`
Given $a$, $b$, and $m$, computes $a^{b}~(\text{mod}~m)$.

**Constraints**
- $b \ge 0$
- $m > 0$

**Time Complexity**
- $O(\log b)$

## Code
```c
long mod_pow(long a, long b, long m) {
  long answer = 1;
  for (; b > 0; b /= 2, a = (a * a) % m) {
    if (b % 2 == 1) {
      answer = (answer * a) % m;
    }
  }
  return answer;
}
```

## Example
```c
const long MOD = 998244353;

printf("%d", mod_pow(2022, 2022, MOD));
// outputs: 867641484
```

## Notes
- replace `long` with `long long` when using C++ instead of C
- `mod_pow` is built-in for Python as `pow(a, b, m)`.

## Verification
- [CSES Problem Set | Exponentiation](https://cses.fi/problemset/task/1095/)
- [CSES Problem Set | Exponentiation II](https://cses.fi/problemset/task/1712/)