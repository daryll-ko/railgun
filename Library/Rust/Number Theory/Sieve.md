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

### With Möbius function
```rust
struct Sieve {
    is_prime: Vec<bool>,
    primes: Vec<usize>,
    mobius: Vec<i64>,
}

impl Sieve {
    fn new(n: usize) -> Sieve {
        let mut is_prime = vec![true; n + 1];
        let mut primes = vec![];
        let mut mobius = vec![0; n + 1];
        is_prime[0] = false;
        is_prime[1] = false;
        mobius[1] = 1;
        for i in 2..=n {
            if is_prime[i] {
                primes.push(i);
                mobius[i] = -1;
            }
            for &p in &primes {
                if i * p > n {
                    break;
                }
                is_prime[i * p] = false;
                if i % p == 0 {
                    mobius[i * p] = 0;
                    break;
                } else {
                    mobius[i * p] = mobius[i] * mobius[p];
                }
            }
        }
        Sieve {
            is_prime,
            primes,
            mobius,
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

## Verification
- [CSES Problem Set | Counting Coprime Pairs](https://cses.fi/problemset/task/2417/)
- [Library Checker | Enumerate Primes](https://judge.yosupo.jp/problem/enumerate_primes) 
	- Vanilla: [submission link](https://judge.yosupo.jp/submission/94186)
	- Segmented: [submission link](https://judge.yosupo.jp/submission/95500)