# `Sieve`
Implementation of the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).

## Methods
### `new`
```cpp
Sieve(int n)
```

**Constraints**
- $n \le 3 \times 10^{7}$

**Time Complexity**
- $O(n \log \log n)$

## Code
### Vanilla
```cpp
struct Sieve {
    bitset<30000001> is_prime;
    vector<int> primes;

    Sieve(int n) {
        is_prime.set();
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                for (int64_t j = (int64_t)i * i; j <= (int64_t)n; j += (int64_t)i) {
                    is_prime[j] = false;
                }
            }
        }
    }
};
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

```

## Verification
- [CSES Problem Set | Counting Coprime Pairs](https://cses.fi/problemset/task/2417/)
- [Library Checker | Enumerate Primes](https://judge.yosupo.jp/problem/enumerate_primes) ([submission link](https://judge.yosupo.jp/submission/94186))