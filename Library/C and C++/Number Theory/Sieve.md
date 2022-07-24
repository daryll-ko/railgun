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
Runs in about 4 seconds for $n \approx 5 \times 10^{8}$.

```cpp
struct Sieve {
	bitset<30'000'001> is_prime;
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

### Segmented
Fast version of Vanilla. Runs in just under 1.5 seconds for $n \approx 5 \times 10^{8}$.

```cpp
struct Sieve {
	bitset<30'000'001> is_prime;
	vector<int> primes;

	Sieve(int n) {
		if (n >= 2) {
			primes.push_back(2);
			primes.reserve((int)(n / log(n) * 1.1));
		}
		int s = (int)floor(sqrt(n));
		int r = (n + 1) / 2;
		vector<bool> sieve(s + 1);
		vector<pair<int, int>> cp;
		for (int i = 3; i <= s; i += 2) {
			if (!sieve[i]) {
				cp.emplace_back(i, i * i / 2);
				for (int j = i * i; j <= s; j += 2 * i) {
					sieve[j] = true;
				}
			}
		}
		for (int l = 1; l <= r; l += s) {
			vector<bool> block(s);
			for (auto &[p, index] : cp) {
				for (int i = index; i < l + s; index = (i += p)) {
					block[i - l] = true;
				}
			}
			for (int i = 0; i < min(s, r - l); ++i) {
				if (!block[i]) {
					primes.push_back((l + i) * 2 + 1);
				}
			}
		}
		for (int p : primes) {
			is_prime[p] = true;
		}
	}
};
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

```cpp
struct Sieve {
	bitset<30'000'001> is_prime;
	vector<int> primes;
	vector<int> m;

	Sieve(int n) {
		is_prime.set();
		m.resize(n + 1);
		vector<int> s(n + 1);
		is_prime[0] = is_prime[1] = false;
		m[1] = 1;
		for (int i = 2; i <= n; ++i) {
			if (is_prime[i]) {
				primes.push_back(i);
				m[i] = // fp(i); —> change as necessary
				s[i] = 1;
			}
			for (int p : primes) {
				if (i * p > n) {
					break;
				}
				is_prime[i * p] = false;
				if (i % p == 0) {
					m[i * p] = // fip(i); —> change as necessary
					s[i * p] = s[i] + 1;
					break;
				} else {
					m[i * p] = m[i] * m[p];
					s[i * p] = 1;
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

## References
- [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/FastEratosthenes.h)
- [[Tutorial] Math note — linear sieve](https://codeforces.com/blog/entry/54090)

## Verification
- [CSES Problem Set | Counting Coprime Pairs](https://cses.fi/problemset/task/2417/)
- [Library Checker | Enumerate Primes](https://judge.yosupo.jp/problem/enumerate_primes)
	- Vanilla: [submission link](https://judge.yosupo.jp/submission/94663)
	- Segmented: [submission link](https://judge.yosupo.jp/submission/95553)