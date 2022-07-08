# `extended_euclid`
Given integers $a$ and $b$, gives one solution to the equation $ax + by = \gcd(a, b)$. Such a solution's existence is guaranteed by [Bezout's lemma](https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity).

## Methods
### `extended_euclid`
```rust
fn extended_euclid(a: i64, b: i64) -> (i64, i64)
```

Returns an integer pair $(x, y)$ such that $ax + by = \gcd(a, b)$.

$x$ and $y$ satisfy the inequalities

$$
|x| \le \left|\dfrac{b}{\gcd(a, b)}\right|,~|y| \le \left|\dfrac{a}{\gcd(a, b)}\right|.
$$

All solutions of the equation $ax + by = \gcd(a, b)$ are of the form

$$
\left(x - k \cdot \dfrac{b}{\gcd(a, b)},~y + k \cdot \dfrac{a}{\gcd(a, b)}\right).
$$

**Time Complexity**
- $O(\log(\min(a, b)))$

### `get_inverse`
```rust
fn get_inverse(a: i64, b: i64) -> i64
```

Returns the smallest positive integer $x$ such that $ax \equiv 1~(\text{mod}~b)$.

**Constraints**
- $\gcd(a, b) = 1$

**Time Complexity**
- $O(\log(\min(a, b)))$

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

fn get_inverse(a: i64, b: i64) -> i64 {
    let (x, _) = extended_euclid(a, b);
    if x >= 0 {
        x
    } else {
        x + b
    }
}
```

## Example
```

```

## References
 - [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/number-theory%20(11.1)/Euclid/Euclid.h)
- [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/euclid.h)

## Verification
