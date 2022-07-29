# `mod_pow`
Given $a$, $b$, and $m$, computes $a^{b}~(\text{mod}~m)$.

**Constraints**
- $b \ge 0$
- $m > 0$

**Time Complexity**
- $O(\log b)$

## Code
```rust
fn mod_pow(mut a: i64, mut b: i64, m: i64) -> i64 {
	let mut answer = 1;
	while b > 0 {
		if b % 2 == 1 {
			answer = (answer * a) % m;
		}
		b /= 2;
		a = (a * a) % m;
	}
	answer
}
```

## Example
```rust
static MOD: i64 = 998_244_353;

println!("{}", mod_pow(10, 9, MOD));
// 10^9 = 1_000_000_000
// 1_000_000_000 = 1 * 998_244_353 + 1_755_647
// outputs: 1755647
```

## Notes
- `mod_pow` is built-in for Python as `pow(a, b, m)`.

## Verification
- [CSES Problem Set | Exponentiation](https://cses.fi/problemset/task/1095/)
- [CSES Problem Set | Exponentiation II](https://cses.fi/problemset/task/1712/)