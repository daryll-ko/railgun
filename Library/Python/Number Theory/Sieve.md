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

### With Möbius function
```python
from dataclasses import dataclass
```

```python
@dataclass
class Sieve:

    def __init__(self, n: int) -> None:
        is_prime = [True for _ in range(n + 1)]
        primes = []
        mobius = [0 for _ in range(n + 1)]
        is_prime[0] = is_prime[1] = False
        mobius[1] = 1
        for i in range(2, n + 1):
            if is_prime[i]:
                primes.append(i)
                mobius[i] = -1
            for p in primes:
                if i * p > n:
                    break
                is_prime[i * p] = False
                if i % p == 0:
                    mobius[i * p] = 0
                    break
                else:
                    mobius[i * p] = mobius[i] * mobius[p]
        self.is_prime = is_prime
        self.primes = primes
        self.mobius = mobius
```

## Example
```python
sieve = Sieve(20)
for p in sieve.primes:
    print(p, end=' ')
print()
# outputs: 2 3 5 7 11 13 17 19
```

## Verification
- [CSES Problem Set | Counting Coprime Pairs](https://cses.fi/problemset/task/2417/)