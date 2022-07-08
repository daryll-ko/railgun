# `SegmentTree`
Implementation of an iterative [segment tree](https://en.wikipedia.org/wiki/Segment_tree).

Suppose we have a [monoid](https://mathworld.wolfram.com/Monoid.html#:~:text=A%20monoid%20is%20a%20set,contain%20at%20least%20one%20element.) $M$ with operation $op$ and identity element $id$. A segment tree allows us to answer queries about an array $A$ of $M$'s elements in the form

$$
query(l, r) = op(A[l], A[l + 1], \dots, A[r]).
$$

For example, if $M = (op, id) = (+, 0)$, then

$$
query(l, r) = A[l] + A[l + 1] + \dots + A[r].
$$

if $M = (op, id) = (\max, -\infty)$, then

$$
query(l, r) = \max(A[l], A[l + 1], \dots, A[r]).
$$

A list of common pairs $(op, id)$ is include in the **Code** section below for convenience.

## Methods
`update` and `query` below assume that `op` runs in $O(1)$ time. If that's not the case, then just multiply their listed time complexities with `op`'s runtime.

For example, if `op` is matrix multiplication, which runs in $O(k^{3})$ time, then `update` and `query` take $O(k^{3}\log n)$ time instead of $O(\log n)$ time.

### `SegmentTree`
```rust
fn new(v: &[T], n: usize, id: T, op: F) -> SegmentTree<T, F>
```

Constructs a segment tree from the vector $v$ with length $n$, where $v$ has elements of the monoid $M = (op, id)$.

**Constraints**
- $n \le 4 \times 10^{6}$
- `op` is of the form `|&a, &b| f(a, b)`

**Time Complexity**
- $O(n)$

### `get_value`
```rust
fn get_value(&self, i: usize) -> T
```

Returns $v[i]$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $O(1)$

### `update`
```rust
fn update(&mut self, mut i: usize, x: T)
```

Sets $v[i]$ to $x$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $O(\log n)$

### `query_all`
```rust
fn query_all(&self) -> T
```

Returns $op(v[0], v[1], \dots, v[n - 1])$.

**Time Complexity**
- $O(1)$

### `query`
```rust
fn query(&self, mut l: usize, mut r: usize) -> T
```

Returns $op(v[l], v[l + 1], \dots, v[r])$.

**Constraints**
- $0 \le l \le r < n$

**Time Complexity**
- $O(\log n)$

## Code
**Common $(op, id)$ pairs**

| $op$                    | $id$                                                  | Time Complexity                                    |
| ----------------------- | ----------------------------------------------------- | -------------------------------------------------- |
| $a + b$                 | $0$                                                   | $O(1)$                                             |
| $ab$                    | $1$                                                   | $O(1)$                                             |
| $\min(a, b)$            | $\infty$ (maximum value of numerical data type used)  | $O(1)$                                             |
| $\max(a, b)$            | $-\infty$ (minimum value of numerical data type used) | $O(1)$                                             |
| $\gcd(a, b)$            | 0                                                     | $O(1)$                                                   |
| $a + b$ (strings)       | $\varepsilon$ (`""`)                                  | $O(len(a))$ |
| $a \times b$ (matrices) | $I_{k}$ ($k \times k$ identity matrix)                | $O(k^{3})$                                         |

```rust
struct SegmentTree<T, F> {
    n: usize,
    tree_offset: usize,
    tree: Vec<T>,
    id: T,
    op: F,
}
 
impl<T: Clone, F: Fn(&T, &T) -> T> SegmentTree<T, F> {
    fn new(v: &[T], n: usize, id: T, op: F) -> SegmentTree<T, F> {
        let mut tree_offset = 1;
        while tree_offset < n {
            tree_offset *= 2;
        }
        let mut tree = vec![id.clone(); 2 * tree_offset];
        for i in 0..n {
            tree[i + tree_offset] = v[i].clone();
        }
        for i in (1..tree_offset).rev() {
            tree[i] = op(&tree[2 * i], &tree[2 * i + 1]);
        }
        SegmentTree {
            n,
            tree_offset,
            tree,
            id,
            op,
        }
    }
    fn pull(&mut self, i: usize) {
        self.tree[i] = (self.op)(&self.tree[2 * i], &self.tree[2 * i + 1]);
    }
    fn get_value(&self, i: usize) -> T {
        self.tree[i + self.tree_offset].clone()
    }
    fn update(&mut self, mut i: usize, x: T) {
        self.tree[i + self.tree_offset] = x;
        i = (i + self.tree_offset) / 2;
        while i > 0 {
            self.pull(i);
            i /= 2;
        }
    }
    fn query_all(&self) -> T {
        self.tree[1].clone()
    }
    fn query(&self, mut l: usize, mut r: usize) -> T {
        let mut left = self.id.clone();
        let mut right = self.id.clone();
        l += self.tree_offset;
        r += self.tree_offset + 1;
        while l < r {
            if l % 2 == 1 {
                left = (self.op)(&left, &self.tree[l]);
                l += 1;
            }
            if r % 2 == 1 {
                r -= 1;
                right = (self.op)(&self.tree[r], &right);
            }
            l /= 2;
            r /= 2;
        }
        (self.op)(&left, &right)
    }
}
```

## Example
```
```

## References
* [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/1D%20Range%20Queries%20(9.2)/SegTree%20(9.2).h)
* [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h)
* [AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp)

## Verification
* [CSES Problem Set | Dynamic Range Minimum Queries](https://cses.fi/problemset/task/1649)