# `SparseTable`
Implementation of a [sparse table](https://brilliant.org/wiki/sparse-table/#:~:text=Sparse%20Table%20is%20a%20data,compared%20to%20other%20data%20structures.).

## Methods
### `new`
```rust
fn new(v: &[i64], n: usize) -> SparseTable
```

Constructs a sparse table for the vector $v$ with length $n$.

**Constraints** 
- $n \le 4 \times 10^{6}$

**Time Complexity**
- $O(n \log n)$

### `query`
```rust
fn query(&self, l: usize, r: usize) -> i64
```

Returns the minimum value among $v[l], v[l + 1], \dots, v[r]$.

**Constraints**
- $0 \le l \le r < n$

**Time Complexity**
- $O(1)$

## Code
```rust
// returns the position of the most significant bit of n
// (i.e., the largest i such that 2^i ≤ n)
fn msb(n: usize) -> usize {
	let mut exponent = 0;
	while (1 << exponent) <= n {
		exponent += 1;
	}
	exponent - 1
}

struct SparseTable {
	table: Vec<Vec<i64>>,
}

impl SparseTable {
	fn new(v: &[i64], n: usize) -> SparseTable {
		let m = msb(n);
		let mut table = vec![vec![0; n]; m + 1];
		for j in 0..n {
			table[0][j] = v[j];
		}
		for i in 1..=m {
			for j in 0..n {
				table[i][j] = table[i - 1][j];
				if j + (1 << (i - 1)) < n {
					table[i][j] = table[i][j].min(table[i - 1][j + (1 << (i - 1))]);
				}
			}
		}
		SparseTable { table }
	}
	fn query(&self, l: usize, r: usize) -> i64 {
		let b = msb(r - l + 1);
		let answer = self.table[b][l].min(self.table[b][r + 1 - (1 << b)]);
		answer
	}
}
```

## Example
```rust
let v = vec![10, 2, 4, 6, 9, 1, 7, 5, 3, 8];
let table = SparseTable::new(&v, 10);

println!("{}", table.query(0, 3));
//     i  |   0   1   2   3
//   v[i] |  10   2   4   6
// outputs: 2

println!("{}", table.query(2, 7));
//     i  |   2   3   4   5   6   7
//   v[i] |   4   6   9   1   7   5
// outputs: 1

println!("{}", table.query(4, 4));
// v[4] = 9
// outputs: 9
```

## Notes
- `min` can be replaced with `max` to handle maximum queries instead

## Verification
- [CSES Problem Set | Static Range Minimum Queries](https://cses.fi/problemset/task/1647/)
- [Library Checker | Static RMQ](https://judge.yosupo.jp/problem/staticrmq) ([submission link](https://judge.yosupo.jp/submission/94179))