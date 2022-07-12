# `miller_rabbin`
Performs a deterministic [Miller-Rabbin primality test](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test) for a given integer $n$.

## Methods
```rust
fn is_prime(n: i64) -> bool
```

Returns whether or not $n$ is prime.

**Time Complexity**
- $O(\log n)$

## Code
```rust
fn mod_mul(a: i64, b: i64, m: i64) -> i64 {
    ((a as i128) * (b as i128) % (m as i128)) as i64
}

fn mod_pow(mut a: i64, mut b: i64, m: i64) -> i64 {
    let mut answer = 1;
    while b > 0 {
        if b % 2 == 1 {
            answer = mod_mul(answer, a, m);
        }
        b /= 2;
        a = mod_mul(a, a, m);
    }
    answer
}

// returns the pair (s, d) such that n = 2^s × d and d is odd
fn decompose(n: i64) -> (i64, i64) {
    let s = n.trailing_zeros() as i64;
    let d = n >> s;
    (s, d)
}

fn is_prime(n: i64) -> bool {
    if n == 0 || n == 1 {
        false
    } else if n == 2 || n == 3 {
        true
    } else if !(n % 6 == 1 || n % 6 == 5) {
        false
    } else {
        let bases = [2, 325, 9_375, 28_178, 450_775, 9_780_504, 1_795_265_022];
        let (s, d) = decompose(n - 1);
        for base in bases {
            let mut x = mod_pow(base, d, n);
            if x == 1 || x == n - 1 {
                continue;
            }
            let mut proceed_to_next_base = false;
            let mut r = 1;
            while r <= s - 1 {
                x = mod_mul(x, x, n);
                if x == n - 1 {
                    proceed_to_next_base = true;
                    break;
                }
                r += 1;
            }
            if proceed_to_next_base {
                continue;
            } else {
                return false;
            }
        }
        true
    }
}
```

## Example
```rust
let p = 33_478_742_787_241;
println!("{}", is_prime(p));
// (...trust me, that's prime)
// outputs: true

let c = 52_069_326_617_183;
println!("{}", is_prime(c));
// c = 5379061 × 9680003
// outputs: false
```

## References
- [Miller-Rabin primality test](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)
- [Deterministic variants of the Miller-Rabin primality test](https://miller-rabin.appspot.com/)
- [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/number-theory%20(11.1)/Primality/MillerRabin.h)
- [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/MillerRabin.h)

## Verification
