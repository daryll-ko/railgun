# `Factorial`
Gives access to values of $k!$, $k^{-1}$, and $k!^{-1}$ modulo $m$ for $k = 1, 2, \dots, n$.

## Methods
### `new`
```rust
fn new(n: usize, m: i64) -> Factorial
```

Computes the values of $k!$, $k^{-1}$, and $k!^{-1}$ modulo $m$ for $k = 1, 2, \dots, n$.

**Constraints**
- $n \le 10^{8}$

**Time Complexity**
- $O(n)$

### `c`
```rust
fn c(&self, n: usize, k: usize) -> i64
```

Computes $\binom{n}{k}~(\text{mod}~m)$.

**Constraints**
- $0 \le k$
- $0 \le n \le n_{\text{init}}$

**Time Complexity**
- $O(1)$

### `catalan`
```rust
fn catalan(&self, n: usize) -> i64
```

Computes the $n^{\text{th}}$ [Catalan number](https://en.wikipedia.org/wiki/Catalan_number).

**Constraints**
- $0 \le n \le \left\lfloor\dfrac{n_{\text{init}}}{2}\right\rfloor$

**Time Complexity**
- $O(1)$

## Code
```rust
struct Factorial {
	n: usize,
	m: i64,
	factorial: Vec<i64>,
	inverse: Vec<i64>,
	inverse_factorial: Vec<i64>,
}

impl Factorial {
	fn new(n: usize, m: i64) -> Factorial {
		let mut factorial = vec![1; n + 1];
		let mut inverse = vec![1; n + 1];
		let mut inverse_factorial = vec![1; n + 1];
		for i in 2..=n {
			factorial[i] = (i as i64) * factorial[i - 1] % m;
			inverse[i] = ((m / (i as i64)) * -inverse[(m % (i as i64)) as usize] % m + m) % m;
			inverse_factorial[i] = inverse[i] * inverse_factorial[i - 1] % m;
		}
		Factorial {
			n,
			m,
			factorial,
			inverse,
			inverse_factorial,
		}
	}

	fn c(&self, n: usize, k: usize) -> i64 {
		if n < k {
			0
		} else {
			assert!(k <= n && n <= self.n);
			self.factorial[n] * self.inverse_factorial[k] % self.m * self.inverse_factorial[n - k]
				% self.m
		}
	}

	fn catalan(&self, n: usize) -> i64 {
		assert!(2 * n <= self.n);
		self.c(2 * n, n) * self.inverse[n + 1] % self.m
	}
}
```

## Example
```

```

## Verification
- [CSES Problem Set | Binomial Coefficients](https://cses.fi/problemset/task/1079)
- [CSES Problem Set | Bracket Sequences I](https://cses.fi/problemset/task/2064)