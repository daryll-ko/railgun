# `Sieve`
Implementation of the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes).

## Methods
### `new`
```python
def __init__(self, n: int) -> None
```

Initializes a new sieve for the positive integers $1$ to $n$.

**Constraints**
- $n \le 3 \times 10^{7}$

**Time Complexity**
- $O(n \log \log n)$

## Code
### Vanilla
```python
from dataclasses import dataclass
```

```python
@dataclass
class Sieve:

    def __init__(self, n: int) -> None:
        is_prime = [True for _ in range(n + 1)]
        primes = []
        is_prime[0] = is_prime[1] = False
        for i in range(2, n + 1):
            if is_prime[i]:
                primes.append(i)
                for j in range(i * i, n + 1, i):
                    is_prime[j] = False
        self.is_prime = is_prime
        self.primes = primes
```

### Segmented
A version that passes Library Checker! Runs in about 5.5 seconds for $n \approx 5 \times 10^{8}$.

`is_prime` nom-noms a lot of memory, so it's commented out by default.

```python
import math
from dataclasses import dataclass
```

```python
@dataclass
class Sieve:

    def __init__(self, n: int) -> None:
        # is_prime = [False for _ in range(n + 1)]
        primes = [2] if n >= 2 else []

        s = int(math.floor(math.sqrt(n)))
        r = (n + 1) // 2

        sieve = [False for _ in range(s + 1)]
        cp = []

        for i in range(3, s + 1, 2):
            if not sieve[i]:
                cp.append((i, i * i // 2))
                for j in range(i * i, s + 1, 2 * i):
                    sieve[j] = True

        for l in range(1, r + 1, s):
            block = [False for _ in range(s)]
            for i in range(len(cp)):
                p, index = cp[i]
                while index < l + s:
                    block[index - l] = True
                    index += p
                cp[i] = (p, index)
            for i in range(min(s, r - l)):
                if not block[i]:
                    primes.append((l + i) * 2 + 1)

        # self.is_prime = is_prime
        self.primes = primes
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

```python
from dataclasses import dataclass
```

```python
@dataclass
class Sieve:

    def __init__(self, n: int) -> None:
        is_prime = [True for _ in range(n + 1)]
        primes = []
        m = [0 for _ in range(n + 1)]
        s = [0 for _ in range(n + 1)]
        is_prime[0] = is_prime[1] = False
        m[1] = 1
        for i in range(2, n + 1):
            if is_prime[i]:
                primes.append(i)
                m[i] = # fp(i) —> change as necessary
                s[i] = 1
            for p in primes:
                if i * p > n:
                    break
                is_prime[i * p] = False
                if i % p == 0:
                    m[i * p] = # fip(i) —> change as necessary
                    s[i * p] = s[i] + 1
                    break
                else:
                    m[i * p] = m[i] * m[p]
                    s[i * p] = 1
        self.is_prime = is_prime
        self.primes = primes
        self.m = m
```

## Example
```python
sieve = Sieve(20)
for p in sieve.primes:
    print(p, end=' ')
print()
# outputs: 2 3 5 7 11 13 17 19
```

## References
- [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/FastEratosthenes.h)
- [[Tutorial] Math note — linear sieve](https://codeforces.com/blog/entry/54090)

## Verification
- [CSES Problem Set | Counting Coprime Pairs](https://cses.fi/problemset/task/2417/)
- [Library Checker | Enumerate Primes](https://judge.yosupo.jp/problem/enumerate_primes)
	- Segmented: [submission link](https://judge.yosupo.jp/submission/95568)