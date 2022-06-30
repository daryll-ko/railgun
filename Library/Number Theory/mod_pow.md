# `mod_pow`
Given $a$, $b$, and $m$, computes $a^{b}~(\text{mod}~m)$.

Runs in $O(\log b)$ time.

## Code
### Rust
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

## Examples
### Rust
```rust
static MOD: i64 = 998_244_353;

println!("{}", mod_pow(2022, 2022, MOD));
// outputs: 867641484
```

### C
```c
const long MOD = 998244353;

printf("%d", mod_pow(2022, 2022, MOD));
```

## Constraints
- $b \ge 0$ and $m > 0$.

## Notes
- replace `long` with `long long` when using C++ instead of C
- `mod_pow` is built-in for Python as `pow(a, b, m)`.

## Verification
- [Exponentiation](https://cses.fi/problemset/task/1095/)
- [Exponentiation II](https://cses.fi/problemset/task/1712/)