# `Factorial`
Gives access to values of $k!$, $k^{-1}$, and $k!^{-1}$ modulo $m$ for $k = 1, 2, \dots, n$.

## Methods
### `__init__`
```python
def __init__(self, n: int, m: int) -> None
```

Computes the values of $k!$, $k^{-1}$, and $k!^{-1}$ modulo $m$ for $k = 1, 2, \dots, n$.

**Constraints**
- $n \le 10^{8}$

**Time Complexity**
- $O(n)$

### `c`
```python
def c(self, n: int, k: int) -> int
```

Computes $\binom{n}{k}~(\text{mod}~m)$.

**Constraints**
- $0 \le k$
- $0 \le n \le n_{\text{init}}$

**Time Complexity**
- $O(1)$

### `catalan`
```python
def catalan(self, n: int) -> int
```

Computes the $n^{\text{th}}$ [Catalan number](https://en.wikipedia.org/wiki/Catalan_number).

**Constraints**
- $0 \le n \le \left\lfloor\dfrac{n_{\text{init}}}{2}\right\rfloor$

**Time Complexity**
- $O(1)$

## Code
```python
from dataclasses import dataclass
```

```python
@dataclass
class Factorial:

	def __init__(self, n: int, m: int) -> None:
		factorial = [1 for _ in range(n + 1)]
		inverse = [1 for _ in range(n + 1)]
		inverse_factorial = [1 for _ in range(n + 1)]

		for i in range(2, n + 1):
			factorial[i] = (i * factorial[i - 1]) % m
			inverse[i] = ((m // i) * -inverse[m % i]) % m
			inverse_factorial[i] = (inverse[i] * inverse_factorial[i - 1]) % m

		self.n = n
		self.m = m
		self.factorial = factorial
		self.inverse = inverse
		self.inverse_factorial = inverse_factorial

	def c(self, n: int, k: int) -> int:
		if n < k:
			return 0
		assert(0 <= k <= n <= self.n)
		return (self.factorial[n] * self.inverse_factorial[n - k] * self.inverse_factorial[k]) % self.m

	def catalan(self, n: int) -> int:
		assert(0 <= 2 * n <= self.n)
		return (self.c(2 * n, n) * self.inverse[n + 1]) % self.m
```

## Example
```

```

## Verification
- [CSES Problem Set | Binomial Coefficients](https://cses.fi/problemset/task/1079)
- [CSES Problem Set | Bracket Sequences I](https://cses.fi/problemset/task/2064)