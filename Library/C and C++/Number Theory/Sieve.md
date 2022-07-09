# `Sieve`
Implementation of the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).

## Methods
### `new`
```cpp
Sieve(int n)
```

Initializes a new sieve for the positive integers $1$ to $n$.

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
```cpp
struct Sieve {
    bitset<30000001> is_prime;
    vector<int> primes;
    vector<int> mobius;

    Sieve(int n) {
        is_prime.set();
        mobius.resize(n + 1);
        is_prime[0] = is_prime[1] = false;
        mobius[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                mobius[i] = -1;
            }
            for (int p : primes) {
                if (i * p > n) {
                    break;
                }
                is_prime[i * p] = false;
                if (i % p == 0) {
                    mobius[i * p] = 0;
                    break;
                } else {
                    mobius[i * p] = mobius[i] * mobius[p];
                }
            }
        }
    }
};
```

## Example
```cpp
Sieve sieve(20);
for (int p : sieve.primes) {
	printf("%d ", p);
}
printf("\n");
// outputs: 2 3 5 7 11 13 17 19
```

## Verification
- [CSES Problem Set | Counting Coprime Pairs](https://cses.fi/problemset/task/2417/)
- [Library Checker | Enumerate Primes](https://judge.yosupo.jp/problem/enumerate_primes) ([submission link](https://judge.yosupo.jp/submission/94186))