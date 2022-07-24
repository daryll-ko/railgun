# `FenwickTree`
Implementation of a [Fenwick tree](https://en.wikipedia.org/wiki/Fenwick_tree).

## Methods
All methods below are **1-indexed**.

### `FenwickTree`
```cpp
FenwickTree(vector<T> v, int n)
```

Constructs a Fenwick tree from the vector $v$ with length $n$.

**Constraints**
- $n \le 4 \times 10^{6}$ 

**Time Complexity**
- $O(n \log n)$

### `add`
```cpp
void add(int i, T x)
```

Adds $x$ to $v[i]$.

**Constraints**
- $1 \le i \le n$

**Time Complexity**
- $O(\log n)$

### `update`
```cpp
void update(int i, T x)
```

Sets $v[i]$ to $x$.

**Constraints**
- $1 \le i \le n$

**Time Complexity**
- $O(\log n)$

### `query`
```cpp
T query(int r) // (1)
```

```cpp
T query(int l, int r) // (2)
```

(1) Returns $v[1] + v[2] + \dots + v[r]$.

(2) Returns $v[l] + v[l + 1] + \dots + v[r]$.

**Constraints**

(1)
- $1 \le r \le n$

(2)
- $1 \le l \le r \le n$

**Time Complexity**
- $O(\log n)$

### `cumulative_lower_bound`
```cpp
int cumulative_lower_bound(T sum)
```

Returns the first index $r$ such that $v[1] + v[2] + \dots + v[r] \ge sum$.

Returns $n + 1$ If $sum > v[1] + v[2] + \dots + v[n]$.

If we treat $v$ as a multiset $S$ which contains the counts of numbers $1$ through $n$, then `cumulative_lower_bound`  returns the $sum^{\text{th}}$ smallest element in $S$.

**Constraints**
- All elements of $v$ are nonnegative.

**Time Complexity**
- $O(\log n)$

## Code
```cpp
int lsb(int n) {
	return n & -n;
}

template <class T>
struct FenwickTree {
	int n;
	vector<T> tree;

	FenwickTree(vector<T> v, int n): n(n) {
		tree.assign(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			tree[i] = v[i - 1];
			for (int j = lsb(i) >> 1; j > 0; j >>= 1) {
				tree[i] += tree[i - j];
			}
		}
	}

	void add(int i, T x) {
		assert(1 <= i && i <= n);
		for (; i <= n; i += lsb(i)) {
			tree[i] += x;
		}
	}

	void update(int i, T x) {
		assert(1 <= i && i <= n);
		T previous_value = query(i, i);
		add(i, x - previous_value);
	}

	T query(int r) {
		assert(0 <= r && r <= n);
		T sum = 0;
		for (; r > 0; r -= lsb(r)) {
			sum += tree[r];
		}
		return sum;
	}

	T query(int l, int r) {
		assert(1 <= l && l <= r && r <= n);
		return query(r) - query(l - 1);
	}

	int cumulative_lower_bound(T sum) {
		int position = 0;
		for (int power = 1 << 23; power > 0; power >>= 1) {
			if (position + power <= n && tree[position + power] < sum) {
				position += power;
				sum -= tree[position];
			}
		}
		return position + 1;
	}
};
```

## Example
```cpp
FenwickTree tree(vector<int>(8, 0), 8);

printf("%d\n", tree.n);
// outputs: 8

tree.add(7, 11);
tree.add(3, 14);

printf("%d\n", tree.query(3, 7));
//      i  |  3   4   5   6    7
// tree[i] | 14 + 0 + 0 + 0 + 11 = 25
// outputs: 25

tree.add(4, 6);
tree.update(3, 12);

printf("%d\n", tree.query(3, 7));
//      i  |  3   4   5   6    7
// tree[i] | 12 + 6 + 0 + 0 + 11 = 29
// outputs: 29

printf("%d\n", tree.query(4));
//      i  |  1   2    3   4
// tree[i] |  0 + 0 + 12 + 6 = 18
// outputs: 18

tree.add(5, 7);

printf("%d\n", tree.cumulative_lower_bound(20));
//             i  |  1   2   3   4   5   6    7  8
//        tree[i] |  0   0  12   6   7   0   11  0
//     cumulative |  0   0  12  18  25  25   36 36
// compared to 20 |  <   <   <   <   >   >    >  >   
// outputs: 5
```

## Notes
- To repeat myself: all methods are **1-indexed**.

## References
- [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/1D%20Range%20Queries%20(9.2)/BIT.h)

## Verification
- [CSES Problem Set | Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648)
- [Library Checker | Point Add Range Sum](https://judge.yosupo.jp/problem/point_add_range_sum) ([submission link](https://judge.yosupo.jp/submission/94470))