# `miller_rabbin`
Performs a deterministic [Miller-Rabbin primality test](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test) for a given integer $n$.

## Methods
```python
def is_prime(n: int) -> bool
```

Returns whether or not $n$ is prime.

**Time Complexity**
- $O(\log n)$

## Code
```python
from typing import Tuple
```

```python
# returns the pair (s, d) such that n = 2^s × d and d is odd
def decompose(n: int) -> Tuple[int, int]:
    s = len(bin(n)) - len(bin(n).rstrip('0'))
    d = n >> s
    return s, d


def is_prime(n: int) -> bool:
    if n == 0 or n == 1:
        return False
    elif n == 2 or n == 3:
        return True
    elif not(n % 6 == 1 or n % 6 == 5):
        return False
    else:
        bases = [2, 325, 9_375, 28_178, 450_775, 9_780_504, 1_795_265_022]
        s, d = decompose(n - 1)
        for base in bases:
            x = pow(base, d, n)
            if x == 1 or x == n - 1:
                continue
            proceed_to_next_base = False
            r = 1
            while r <= s - 1:
                x = (x * x) % n
                if x == n - 1:
                    proceed_to_next_base = True
                    break
                r += 1
            if proceed_to_next_base:
                continue
            else:
                return False
        return True
```

## Example
```python
p = 33_478_742_787_241
print(is_prime(p))
# (...trust me, that's prime)
# outputs: True

c = 52_069_326_617_183
print(is_prime(c))
# c = 5379061 × 9680003
# outputs: False
```

## References
- [Miller-Rabin primality test](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)
- [Deterministic variants of the Miller-Rabin primality test](https://miller-rabin.appspot.com/)
- [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/number-theory%20(11.1)/Primality/MillerRabin.h)
- [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/MillerRabin.h)

## Verification
