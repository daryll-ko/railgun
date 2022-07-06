# `SparseTable`
Implementation of a [sparse table](https://brilliant.org/wiki/sparse-table/#:~:text=Sparse%20Table%20is%20a%20data,compared%20to%20other%20data%20structures.).

## Methods
### `new`
```python
def __init__(self, v: List[int], n: int)
```

Constructs a sparse table for the vector $v$ with length $n$.

**Constraints** 
- $n \le 4 \times 10^{6}$

**Time Complexity**
- $O(n \log n)$

### `query`
```python
def query(self, l: int, r: int) -> int
```

Returns the minimum value among $v[l], v[l + 1], \dots, v[r]$.

**Constraints**
- $0 \le l \le r < n$

**Time Complexity**
- $O(1)$

## Code
```python
# returns the position of the most significant bit of n
# (i.e., the largest i such that 2^i ≤ n)
def msb(n: int) -> int:
    exponent = 0
    while (1 << exponent) <= n:
        exponent += 1
    return exponent - 1


@dataclass
class SparseTable:

    def __init__(self, v: List[int], n: int):
        m = msb(n)
        table = [[0 for _ in range(n)] for _ in range(m + 1)]
        for j in range(n):
            table[0][j] = v[j]
        for i in range(1, m + 1):
            for j in range(n):
                table[i][j] = table[i - 1][j]
                if j + (1 << (i - 1)) < n:
                    table[i][j] = min(
                        table[i][j], table[i - 1][j + (1 << (i - 1))]
                    )
        self.table = table

    def query(self, l: int, r: int) -> int:
        b = msb(r - l + 1)
        answer = min(self.table[b][l], self.table[b][r + 1 - (1 << b)])
        return answer
```

## Example
```rust

```

## Notes
- `min` can be replaced with `max` to handle maximum queries instead

## Verification
- [CSES Problem Set | Static Range Minimum Queries](https://cses.fi/problemset/task/1647/)
- [Yosupo Library Checker | Static RMQ](https://judge.yosupo.jp/problem/staticrmq) ([submission link](https://judge.yosupo.jp/submission/94658)