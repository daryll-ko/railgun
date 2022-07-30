# `Factorial`
Gives access to values of $k!$, $k^{-1}$, and $k!^{-1}$ modulo $m$ for $k = 1, 2, \dots, n$.

## Methods
### `Factorial`
```cpp
Factorial(int n, i64 m)
```

Computes the values of $k!$, $k^{-1}$, and $k!^{-1}$ modulo $m$ for $k = 1, 2, \dots, n$.

**Constraints**
- $n \le 10^{8}$

**Time Complexity**
- $O(n)$

### `c`
```cpp
i64 c(int n, int k)
```

Computes $\binom{n}{k}~(\text{mod}~m)$.

**Constraints**
- $0 \le k$
- $0 \le n \le n_{\text{init}}$

**Time Complexity**
- $O(1)$

### `catalan`
```cpp
i64 catalan(int n)
```

Computes the $n^{\text{th}}$ [Catalan number](https://en.wikipedia.org/wiki/Catalan_number).

**Constraints**
- $0 \le n \le \left\lfloor\dfrac{n_{\text{init}}}{2}\right\rfloor$

**Time Complexity**
- $O(1)$

## Code
```cpp
using i64 = int64_t;
```

```cpp
struct Factorial {
	int n;
	i64 m;
	vector<i64> factorial, inverse, inverse_factorial;

	Factorial(int n, i64 m): n(n), m(m) {
		factorial.assign(n + 1, 1);
		inverse.assign(n + 1, 1);
		inverse_factorial.assign(n + 1, 1);

		for (int i = 2; i <= n; ++i) {
			factorial[i] = i * factorial[i - 1] % m;
			inverse[i] = ((m / i) * -inverse[m % i] % m + m) % m;
			inverse_factorial[i] = inverse[i] * inverse_factorial[i - 1] % m;
		}
	}

	i64 c(int n, int k) {
		if (n < k) {
			return 0;
		}
		assert(0 <= k <= n <= this->n);
		return factorial[n] * inverse_factorial[k] % m * inverse_factorial[n - k] % m;
	}

	i64 catalan(int n) {
		assert(0 <= n && n <= this->n);
		return c(2 * n, n) * inverse[n + 1] % m;
	}
};
```

## Example
```

```

## Verification
- [CSES Problem Set | Binomial Coefficients](https://cses.fi/problemset/task/1079)
- [CSES Problem Set | Bracket Sequences I](https://cses.fi/problemset/task/2064)