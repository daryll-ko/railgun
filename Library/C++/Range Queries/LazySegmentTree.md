# `LazySegmentTree`
Implementation of an iterative [lazy segment tree](https://cp-algorithms.com/data_structures/segment_tree.html#range-updates-lazy-propagation).

## Methods

## Code
```cpp
template <class T, class U, class F = function<T(T, T)>, class G = function<U(U, U)>, class M = function<T(U, T)>>
struct LazySegmentTree {

	int n, tree_offset, log;

	vector<T> tree;
	T id;
	F op;
	
	vector<U> lazy;
	U id_lazy;
	G op_lazy;
	
	M mapping;

	LazySegmentTree
	(
		vector<T> v,
		int n,
		T id,
		F op,
		U id_lazy,
		G op_lazy,
		M mapping
	) :
		n(n),
		id(id),
		op(op),
		id_lazy(id_lazy),
		op_lazy(op_lazy),
		mapping(mapping)
	{
		for (tree_offset = 1; tree_offset < n; tree_offset *= 2);
		log = __builtin_ctz(tree_offset);
		tree.assign(2 * tree_offset, id);
		lazy.assign(tree_offset, id_lazy);
		for (int i = 0; i < n; ++i) {
			tree[i + tree_offset] = v[i];
		}
		for (int i = tree_offset - 1; i >= 1; --i) {
			pull(i);
		}
	}

	void pull(int i) {
		tree[i] = op(tree[2 * i], tree[2 * i + 1]);
	}

	void apply(int i, U y) {
		tree[i] = mapping(y, tree[i]);
		if (i < tree_offset) {
			lazy[i] = op_lazy(y, lazy[i]);
		}
	}

	void push(int i) {
		apply(2 * i, lazy[i]);
		apply(2 * i + 1, lazy[i]);
		lazy[i] = id_lazy;
	}

	void push(int l, int r) {
		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l) {
				push(l >> i);
			}
			if (((r >> i) << i) != r) {
				push((r - 1) >> i);
			}
		}
	}

	T get(int i) {
		assert(0 <= i && i < n);
		i += tree_offset;
		for (int j = log; j >= 1; j--) {
			push(i >> j);
		}
		return tree[i];
	}

	void set(int i, T x) {
		assert(0 <= i && i < n);
		i += tree_offset;
		for (int j = log; j >= 1; j--) {
			push(i >> j);
		}
		tree[i] = x;
		for (int j = 1; j <= log; j++) {
			pull(i >> j);
		}
	}

	void update(int l, int r, U y) {
		assert(0 <= l && l <= r && r < n);
		l += tree_offset;
		r += tree_offset + 1;
		push(l, r);
		int l2 = l, r2 = r;
		while (l2 < r2) {
			if (l2 % 2 == 1) {
				apply(l2++, y);
			}
			if (r2 % 2 == 1) {
				apply(--r2, y);
			}
			l2 /= 2;
			r2 /= 2;
		}
		for (int i = 1; i <= log; i++) {
			if (((l >> i) << i) != l) {
				pull(l >> i);
			}
			if (((r >> i) << i) != r) {
				pull((r - 1) >> i);
			}
		}
	}

	T query_all() {
		return tree[1];
	}

	T query(int l, int r) {
		assert(0 <= l && l <= r && r < n);
		l += tree_offset;
		r += tree_offset + 1;
		push(l, r);
		T left = id, right = id;
		for (; l < r; l /= 2, r /= 2) {
			if (l % 2 == 1) {
				left = op(left, tree[l++]);
			}
			if (r % 2 == 1) {
				right = op(tree[--r], right);
			}
		}
		return op(left, right);
	}

};
```

## Example
```

```

## References

## Verification
