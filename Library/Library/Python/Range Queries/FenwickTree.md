# `FenwickTree`
Implementation of a [Fenwick tree](https://en.wikipedia.org/wiki/Fenwick_tree).

## Methods
All methods below are **1-indexed**.

### `new`
```python
def __init__(self, v: List[int], n: int) -> None
```

Constructs a Fenwick tree from the vector $v$ with length $n$.

**Constraints**
- $n \le 4 \times 10^{6}$ 

**Time Complexity**
- $O(n \log n)$

### `add`
```python
def add(self, i: int, x: int) -> None
```

Adds $x$ to $v[i]$.

**Constraints**
- $1 \le i \le n$

**Time Complexity**
- $O(\log n)$

### `update`
```python
def update(self, i: int, x: int) -> None
```

Sets $v[i]$ to $x$.

**Constraints**
- $1 \le i \le n$

**Time Complexity**
- $O(\log n)$

### `prefix_query`
```python
def prefix_query(self, r: int) -> int
```

Returns $v[1] + v[2] + \dots + v[r]$.

**Constraints**
- $1 \le r \le n$

**Time Complexity**
- $O(\log n)$

### `query`
```python
def query(self, l: int, r: int) -> int
```

Returns $v[l] + v[l + 1] + \dots + v[r]$.

**Constraints**
- $1 \le l \le r \le n$

**Time Complexity**
- $O(\log n)$

### `cumulative_lower_bound`
```python
def cumulative_lower_bound(self, sum: int) -> int
```

Returns the first index $r$ such that $v[1] + v[2] + \dots + v[r] \ge sum$.

Returns $n + 1$ If $sum > v[1] + v[2] + \dots + v[n]$.

If we treat $v$ as a multiset $S$ which contains the counts of numbers $1$ through $n$, then `cumulative_lower_bound`  returns the $sum^{\text{th}}$ smallest element in $S$.

**Constraints**
- All elements of $v$ are nonnegative.

**Time Complexity**
- $O(\log n)$

## Code
```python
from dataclasses import dataclass
from typing import List
```

```python
@dataclass
class FenwickTree:

    def __init__(self, v: List[int], n: int) -> None:
        tree = [0 for _ in range(n + 1)]
        for i in range(1, n + 1):
            tree[i] = v[i - 1]
            j = lsb(i) >> 1
            while j > 0:
                tree[i] += tree[i - j]
                j >>= 1
        self.tree = tree
        self.n = n

    def add(self, i: int, x: int) -> None:
        assert 1 <= i <= self.n
        while i <= self.n:
            self.tree[i] += x
            i += lsb(i)

    def update(self, i: int, x: int) -> None:
        assert 1 <= i <= self.n
        previous_value = self.query(i, i)
        self.add(i, x - previous_value)

    def prefix_query(self, r: int) -> int:
        assert 0 <= r <= self.n
        sum = 0
        while r > 0:
            sum += self.tree[r]
            r -= lsb(r)
        return sum

    def query(self, l: int, r: int) -> int:
        assert 1 <= l <= r <= self.n
        return self.prefix_query(r) - self.prefix_query(l - 1)

    def cumulative_lower_bound(self, sum: int) -> int:
        position = 0
        power = 1 << 23
        while power > 0:
            if position + power <= self.n and self.tree[position + power] < sum:
                position += power
                sum -= self.tree[position]
            power >>= 1
        return position + 1
```

## Notes
- To repeat myself: all methods are **1-indexed**.

## References
- [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/1D%20Range%20Queries%20(9.2)/BIT.h)

## Verification
- [CSES Problem Set | Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648)
- [Yosupo Library Checker | Point Add Range Sum](https://judge.yosupo.jp/problem/point_add_range_sum) ([submission link](https://judge.yosupo.jp/submission/94590))