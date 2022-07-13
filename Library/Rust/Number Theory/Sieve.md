# `Sieve`
Implementation of the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).

## Methods
### `new`
```rust
fn new(n: usize) -> Sieve
```

Initializes a new sieve for the positive integers $1$ to $n$.

**Constraints**
- $n \le 3 \times 10^{7}$

**Time Complexity**
- $O(n \log \log n)$

## Code
### Vanilla
Runs in just under 10 seconds for $n \approx 5 \times 10^{8}$.

```rust
struct Sieve {
    is_prime: Vec<bool>,
    primes: Vec<usize>,
}

impl Sieve {
    fn new(n: usize) -> Sieve {
        let mut is_prime = vec![true; n + 1];
        let mut primes = vec![];
        is_prime[0] = false;
        is_prime[1] = false;
        for i in 2..=n {
            if is_prime[i] {
                primes.push(i);
                for j in ((i * i)..=n).step_by(i) {
                    is_prime[j] = false;
                }
            }
        }
        Sieve { is_prime, primes }
    }
}
```

### Segmented
Fast version of Vanilla. Runs in just under 2 seconds for $n \approx 5 \times 10^{8}$.

```rust
struct Sieve {
    is_prime: Vec<bool>,
    primes: Vec<usize>,
}

impl Sieve {
    fn new(n: usize) -> Sieve {
        let mut is_prime = vec![false; n + 1];
        let mut primes = if n >= 2 { vec![2] } else { vec![] };

        let s = (n as f64).sqrt().floor() as usize;
        let r = (n + 1) / 2;

        let mut sieve = vec![false; s + 1];
        let mut cp = vec![];

        for i in (3..=s).step_by(2) {
            if !sieve[i] {
                cp.push((i, i * i / 2));
                for j in ((i * i)..=s).step_by(2 * i) {
                    sieve[j] = true;
                }
            }
        }

        // each block covers [l, l + s), which refers to the odd numbers in the range [l * 2 + 1, (l + s) * 2 + 1)
        for l in (1..=r).step_by(s) {
            let mut block = vec![false; s];
            for (p, index) in &mut cp {
                while *index < l + s {
                    block[*index - l] = true;
                    *index += *p;
                }
            }
            for i in 0..s.min(r - l) {
                if !block[i] {
                    primes.push((l + i) * 2 + 1);
                }
            }
        }

        for &p in &primes {
            is_prime[p] = true;
        }

        Sieve { is_prime, primes }
    }
}
```

### Multiplicative
The Sieve of Eratosthenes also comes in handy for computing [multiplicative functions](https://en.wikipedia.org/wiki/Multiplicative_function).

Each function $m$ is given by a pair $(f_{p}, f_{i \times p})$:
- $f_{p}$ returns the value of $m(p)$ for primes $p$.
- $f_{i \times p}$ returns the value of $m(c)$ when $c$ is of the form $i \times p$, where $p$ is $c$'s smallest prime factor and $p~|~i$.

A list of pairs for common $m$ is given in the table below. $s(i)$ denotes the exponent of $i$'s smallest prime factor.

| $m$          | Name                     | $f_{p}$ | $f_{i \times p}$                     |
| ------------ | ------------------------ | ------- | ------------------------------------ |
| $\phi$       | Euler's totient function | $p - 1$ | $m(i) \times p$                      |
| $\mu$        | Möbius function          | $-1$    | $0$                                  |
| $\sigma_{0}$ | number of divisors       | $2$     | $m(i) \times \dfrac{s(i) + 2}{s(i) + 1}$ |
| $\sigma_{1}$  | sum of divisors          | $p + 1$ | $m(i) \times \dfrac{p^{s[i] + 2} - 1}{p^{s[i] + 1} - 1}$                                      |

```rust
struct Sieve {
    is_prime: Vec<bool>,
    primes: Vec<usize>,
    m: Vec<i64>,
}

impl Sieve {
    fn new(n: usize) -> Sieve {
        let mut is_prime = vec![true; n + 1];
        let mut primes = vec![];
        let mut m = vec![0; n + 1];
        let mut s = vec![0; n + 1];
        is_prime[0] = false;
        is_prime[1] = false;
        m[1] = 1;
        for i in 2..=n {
            if is_prime[i] {
                primes.push(i);
                m[i] = // fp(i); —> change as necessary
                s[i] = 1;
            }
            for &p in &primes {
                if i * p > n {
                    break;
                }
                is_prime[i * p] = false;
                if i % p == 0 {
                    m[i * p] = // fip(m[i], p); —> change as necessary
                    s[i * p] = s[i] + 1;
                    break;
                } else {
                    m[i * p] = m[i] * m[p];
                    s[i * p] = 1;
                }
            }
        }
        Sieve {
            is_prime,
            primes,
            m,
        }
    }
}
```

## Example
```rust
let sieve = Sieve::new(20);
for &p in &sieve.primes {
    print!("{} ", p);
}
println!();
// outputs: 2 3 5 7 11 13 17 19
```

## References
- [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/FastEratosthenes.h)
- [[Tutorial] Math note — linear sieve](https://codeforces.com/blog/entry/54090)

## Verification
- [CSES Problem Set | Counting Coprime Pairs](https://cses.fi/problemset/task/2417/)
- [Library Checker | Enumerate Primes](https://judge.yosupo.jp/problem/enumerate_primes) 
	- Vanilla: [submission link](https://judge.yosupo.jp/submission/94186)
	- Segmented: [submission link](https://judge.yosupo.jp/submission/95500)