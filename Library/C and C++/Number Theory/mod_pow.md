# `mod_pow`
Given $a$, $b$, and $m$, computes $a^{b}~(\text{mod}~m)$.

**Constraints**
- $b \ge 0$
- $m > 0$

**Time Complexity**
- $O(\log b)$

## Code
### C
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

### C++
```cpp
using i64 = int64_t;
```

```cpp
i64 mod_pow(i64 a, i64 b, i64 m) {
	i64 answer = 1;
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

printf("%d\n", mod_pow(2022, 2022, MOD));
// 10^9 = 1_000_000_000
// 1_000_000_000 = 1 * 998_244_353 + 1_755_647
// outputs: 1755647
```

## Notes
- `mod_pow` is built-in for Python as `pow(a, b, m)`.

## Verification
- [CSES Problem Set | Exponentiation](https://cses.fi/problemset/task/1095/)
- [CSES Problem Set | Exponentiation II](https://cses.fi/problemset/task/1712/)