# `SparseTable`
Implementation of a [sparse table](https://brilliant.org/wiki/sparse-table/#:~:text=Sparse%20Table%20is%20a%20data,compared%20to%20other%20data%20structures.).

## Methods
### `SparseTable`
```rust
SparseTable(vector<T> v, int n)
```

Constructs a sparse table for the vector $v$ with length $n$.

**Constraints** 
- $n \le 4 \times 10^{6}$

**Time Complexity**
- $O(n \log n)$

### `query`
```rust
int query(int l, int r)
```

Returns the minimum value among $v[l], v[l + 1], \dots, v[r]$.

**Constraints**
- $0 \le l \le r < n$

**Time Complexity**
- $O(1)$

## Code
```cpp
// returns the position of the most significant bit of n
// (i.e., the largest i such that 2^i ≤ n)
int msb(int n) {
    return 31 - __builtin_clz(n);
}
 
template <class T>
struct SparseTable {
    vector<vector<T>> table;
 
    SparseTable(vector<T> v, int n) {
        int m = msb(n);
        vector<vector<T>> table(m + 1, vector<T>(n));
        for (int j = 0; j < n; ++j) {
            table[0][j] = v[j];
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 0; j < n; ++j) {
                table[i][j] = table[i - 1][j];
                if (j + (1 << (i - 1)) < n) {
                    table[i][j] = min(table[i][j], table[i - 1][j + (1 << (i - 1))]);
                }
            }
        }
        this->table = table;
    }
 
    int query(int l, int r) {
        int b = msb(r - l + 1);
        return min(table[b][l], table[b][r + 1 - (1 << b)]);
    }
};
```

## Example
```rust

```

## Notes
- `min` can be replaced with `max` to handle maximum queries instead

## Verification
- [CSES Problem Set | Static Range Minimum Queries](https://cses.fi/problemset/task/1647/)
- [Library Checker | Static RMQ](https://judge.yosupo.jp/problem/staticrmq) ([submission link](https://judge.yosupo.jp/submission/94483))