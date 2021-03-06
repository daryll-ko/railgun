# `SparseTable`
Implementation of a [sparse table](https://brilliant.org/wiki/sparse-table/#:~:text=Sparse%20Table%20is%20a%20data,compared%20to%20other%20data%20structures.).

## Methods
### `SparseTable`
```cpp
SparseTable(vector<T> v, int n)
```

Constructs a sparse table for the vector $v$ with length $n$.

**Constraints** 
- $n \le 4 \times 10^{6}$

**Time Complexity**
- $O(n \log n)$

### `query`
```cpp
T query(int l, int r)
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

	T query(int l, int r) {
		int b = msb(r - l + 1);
		return min(table[b][l], table[b][r + 1 - (1 << b)]);
	}
};
```

## Example
```cpp
vector<int> v = {10, 2, 4, 6, 9, 1, 7, 5, 3, 8};
SparseTable<int> table(v, 10);

printf("%d\n", table.query(0, 3));
//     i  |   0   1   2   3
//   v[i] |  10   2   4   6
// outputs: 2

printf("%d\n", table.query(2, 7));
//     i  |   2   3   4   5   6   7
//   v[i] |   4   6   9   1   7   5
// outputs: 1

printf("%d\n", table.query(4, 4));
// v[4] = 9
// outputs: 9
```

## Notes
- `min` can be replaced with `max` to handle maximum queries instead

## Verification
- [CSES Problem Set | Static Range Minimum Queries](https://cses.fi/problemset/task/1647/)
- [Library Checker | Static RMQ](https://judge.yosupo.jp/problem/staticrmq) ([submission link](https://judge.yosupo.jp/submission/94483))