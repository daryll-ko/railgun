# `chinese_remainder`
Implementation of the [Chinese remainder theorem](https://en.wikipedia.org/wiki/Chinese_remainder_theorem).

## Methods
### `chinese_remainder`
```rust
fn chinese_remainder(r: &[i64], m: &[i64]) -> (i64, i64)
```

Suppose we have the system of equations

$$
\begin{align}
x & \equiv r_{1}~(\text{mod}~m_{1}) \\
x & \equiv r_{2}~(\text{mod}~m_{2}) \\
& \vdots \\
x & \equiv r_{n}~(\text{mod}~m_{n}).
\end{align}
$$

If a solution for $x$ exists, returns $(x, \text{lcm}(m_{1}, m_{2}, \dots, m_{n}))$. Otherwise, returns $(0, 0)$.

**Constraints**
- $\verb|len(|r\verb|)| = \verb|len(|m\verb|)|$
- $m_{i} \ge 1$ for $1 \le i \le n$

**Time Complexity**
- $n \log \text{lcm}(m_{1}, m_{2}, \dots, m_{n})$

## Code
```rust
fn extended_euclid(a: i64, b: i64) -> (i64, i64) {
	if b == 0 {
		(1, 0)
	} else {
		let (x, y) = extended_euclid(b, a % b);
		(y, x - (a / b) * y)
	}
}

fn gcd(a: i64, b: i64) -> i64 {
	if b == 0 {
		a
	} else {
		gcd(b, a % b)
	}
}

fn safe_mod(r: i64, m: i64) -> i64 {
	(r % m + m) % m
}

fn chinese_remainder(r: &[i64], m: &[i64]) -> (i64, i64) {
	assert_eq!(r.len(), m.len());
	let n = r.len();
	let mut r_answer = 0;
	let mut m_answer = 1;
	for i in 0..n {
		assert!(m[i] >= 1);
		let mut r_current = safe_mod(r[i], m[i]);
		let mut m_current = m[i];
		if m_answer < m_current {
			std::mem::swap(&mut r_answer, &mut r_current);
			std::mem::swap(&mut m_answer, &mut m_current);
		}
		if m_answer % m_current == 0 {
			if r_answer % m_current != r_current {
				return (0, 0);
			}
			continue;
		}
		let (x, _) = extended_euclid(m_answer, m_current);
		let g = gcd(m_answer, m_current);
		m_current /= g;
		if (r_current - r_answer) % g != 0 {
			return (0, 0);
		}
		let k = (r_current - r_answer) / g % m_current * x % m_current;
		r_answer += k * m_answer;
		m_answer *= m_current;
		r_answer = safe_mod(r_answer, m_answer)
	}
	(r_answer, m_answer)
}
```

## Example
```
```

## References
- [AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/math.hpp)

## Verification
- [Kattis | chineseremainder](https://open.kattis.com/problems/chineseremainder)
- [Kattis | generalchineseremainder](https://open.kattis.com/problems/generalchineseremainder)