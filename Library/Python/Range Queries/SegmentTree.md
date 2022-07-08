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

### `__init__`
```python
def __init__(self, v: List[T], n: int, id: T, op: F) -> None
```

Constructs a segment tree from the vector $v$ with length $n$, where $v$ has elements of the monoid $M = (op, id)$.

**Constraints**
- $n \le 4 \times 10^{6}$
- `op` is of the form `|&a, &b| f(a, b)`

**Time Complexity**
- $O(n)$

### `get_value`
```python
def get_value(self, i: int) -> T
```

Returns $v[i]$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $O(1)$

### `update`
```python
def update(self, i: int, x: T) -> None
```

Sets $v[i]$ to $x$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $O(\log n)$

### `query_all`
```python
def query_all(self) -> T
```

Returns $op(v[0], v[1], \dots, v[n - 1])$. Equivalent to `query(0, n - 1)`.

**Time Complexity**
- $O(1)$

### `query`
```python
def query(self, l: int, r: int) -> T
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

```python
from dataclasses import dataclass
from typing import Callable, List, Generic, TypeVar
from copy import deepcopy
```

```python
T = TypeVar("T")
F = Callable[[T, T], T]


@dataclass
class SegmentTree(Generic[T]):

    def __init__(self, v: List[T], n: int, id: T, op: F) -> None:
        tree_offset = 1
        while tree_offset < n:
            tree_offset *= 2
        tree = [deepcopy(id) for _ in range(2 * tree_offset)]
        for i in range(n):
            tree[i + tree_offset] = deepcopy(v[i])
        for i in range(tree_offset - 1, 0, -1):
            tree[i] = op(tree[2 * i], tree[2 * i + 1])
        self.n = n
        self.tree_offset = tree_offset
        self.tree = tree
        self.id = id
        self.op = op

    def pull(self, i: int) -> None:
        self.tree[i] = (self.op)(self.tree[2 * i], self.tree[2 * i + 1])

    def get_value(self, i: int) -> T:
        return deepcopy(self.tree[i + self.tree_offset])

    def update(self, i: int, x: T) -> None:
        self.tree[i + self.tree_offset] = x
        i = (i + self.tree_offset) // 2
        while i > 0:
            self.pull(i)
            i //= 2

    def query_all(self) -> T:
        return deepcopy(self.tree[1])

    def query(self, l: int, r: int) -> T:
        left = deepcopy(self.id)
        right = deepcopy(self.id)
        l += self.tree_offset
        r += self.tree_offset + 1
        while l < r:
            if l % 2 == 1:
                left = (self.op)(left, self.tree[l])
                l += 1
            if r % 2 == 1:
                r -= 1
                right = (self.op)(self.tree[r], right)
            l //= 2
            r //= 2
        return (self.op)(left, right)
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