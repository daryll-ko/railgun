# `LazySegmentTree`
Implementation of an iterative [lazy segment tree](https://cp-algorithms.com/data_structures/segment_tree.html#range-updates-lazy-propagation).

Suppose we have a monoid $M$ with operation $op$ and identity element $id$. A lazy segment tree allows us to perform updates on an array $A$ of $M$'s elements of the form

$$
update(l,r): a[l],a[l+1],\dots,a[r] \mapsto f(a[l]),f(a[l+1]),\dots,f(a[r])
$$

 and answer queries of the form

$$
query(l, r) = op(a[l],a[l+1],\dots,a[r]).
$$

Here, $f$ must be part of a set of mappings $\mathcal{F}$ that has the following properties:
- $\mathcal{F}$ is closed under composition: if $f \in \mathcal{F}$ and $g \in \mathcal{F}$, then $f \circ g \in \mathcal{F}$.
- $\mathcal{F}$ contains the identity mapping $f(x) = x$.

For example, we can have $(op, id) = (+, 0)$ and $\mathcal{F} = \{f:=x+c~|~c \in \mathbb{Z}\}$. $\mathcal{F}$ has the required properties because of the following:
- if $f:=x+c \in \mathcal{F}$ and $g:=x+d \in \mathcal{F}$, then $f \circ g := x+(d+c) \in \mathcal{F}$
- when $c = 0$, $f := x$ is the identity mapping.

For this implementation, the user needs to provide several values to initialize a `LazySegmentTree`:
- $v$ - the vector to operate on
- $n$ - the size of $v$
- $id$ - the identity element of the monoid $M$ (typed as `T`)
- $op$ - the binary operator of the monoid $M$ (typed as `fn(&T, &T) -> T`)
- $id_{lazy}$ - the identity mapping of the set of mappings $\mathcal{F}$ (typed as `U`)
- $op_{lazy}$ - the composition function of the set of mappings $\mathcal{F}$ (typed as `fn(&U, &U) → U`)
- $mapping$ - a [functor](https://en.wikibooks.org/wiki/Haskell/The_Functor_class) that applies a function $f \in \mathcal{F}$ to a element of the monoid $M$ (typed as `fn(&U, &T) -> T`)

It's important to note that the type `U` here only contains **data** about the functions in $\mathcal{F}$. For example, if $f := x + c$, then `U` contains the value $c$, not the entire function.

The code needed for all common pairs $(M, \mathcal{F})$ is provided in the `Code` section for convenience.

## Methods
### `new`
```rust
fn new(
		v: &[T],
		n: usize,
		id: T,
		op: fn(&T, &T) -> T,
		id_lazy: U,
		op_lazy: fn(&U, &U) -> U,
		mapping: fn(&U, &T) -> T,
	) -> LazySegmentTree<T, U>
```

Constructs a lazy segment tree from the vector $v$ with length $n$.

**Constraints**
- $n \le 10^{8}$

**Time Complexity**
- $O(n)$

### `get`
```rust
fn get(&mut self, mut i: usize) -> T
```

Returns $v[i]$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $O(\log n)$

### `set`
```rust
fn set(&mut self, mut i: usize, x: T)
```

Sets $v[i]$ to $x$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $O(\log n)$

### `update`
```rust
fn update(&mut self, mut l: usize, mut r: usize, y: U)
```

Sets $a[l], a[l+1], \dots, a[r]$ to $f(a[l]), f(a[l + 1]), \dots, f(a[r])$, where $f$ is defined by the function data provided by $y$.

**Constraints**
- $0 \le l \le r < n$

**Time Complexity**
- $O(\log n)$

### `query_all`
```rust
fn query_all(&self) -> T
```

Returns $op(a[0], a[1], \dots, a[n - 1])$. Equivalent to `query(0, n - 1)`.

**Time Complexity**
- $O(1)$

### `query`
```rust
fn query(&mut self, mut l: usize, mut r: usize) -> T
```

Returns $op(a[l], a[l + 1], \dots, a[r])$.

**Constraints**
- $0 \le l \le r < n$

**Time Complexity**
- $O(\log n)$

## Code
### Struct code
```rust
struct LazySegmentTree<T, U> {
	n: usize,
	tree_offset: usize,
	log: usize,
	tree: Vec<T>,
	id: T,
	op: fn(&T, &T) -> T,
	lazy: Vec<U>,
	id_lazy: U,
	op_lazy: fn(&U, &U) -> U,
	mapping: fn(&U, &T) -> T,
}

impl<T: Clone, U: Clone> LazySegmentTree<T, U> {
	fn new(
		v: &[T],
		n: usize,
		id: T,
		op: fn(&T, &T) -> T,
		id_lazy: U,
		op_lazy: fn(&U, &U) -> U,
		mapping: fn(&U, &T) -> T,
	) -> LazySegmentTree<T, U> {
		let mut tree_offset: usize = 1;
		while tree_offset < n {
			tree_offset *= 2;
		}
		let log = tree_offset.trailing_zeros() as usize;
		let mut tree = vec![id.clone(); 2 * tree_offset];
		let lazy = vec![id_lazy.clone(); tree_offset];
		for i in 0..n {
			tree[i + tree_offset] = v[i].clone();
		}
		for i in (1..tree_offset).rev() {
			tree[i] = op(&tree[2 * i], &tree[2 * i + 1]);
		}
		LazySegmentTree {
			n,
			tree_offset,
			log,
			tree,
			id,
			op,
			lazy,
			id_lazy,
			op_lazy,
			mapping,
		}
	}
	fn pull(&mut self, i: usize) {
		self.tree[i] = (self.op)(&self.tree[2 * i], &self.tree[2 * i + 1]);
	}
	fn apply(&mut self, i: usize, y: U) {
		self.tree[i] = (self.mapping)(&y, &self.tree[i]);
		if i < self.tree_offset {
			self.lazy[i] = (self.op_lazy)(&y, &self.lazy[i]);
		}
	}
	fn push(&mut self, i: usize) {
		self.apply(2 * i, self.lazy[i].clone());
		self.apply(2 * i + 1, self.lazy[i].clone());
		self.lazy[i] = self.id_lazy.clone();
	}
	fn range_push(&mut self, l: usize, r: usize) {
		for i in (1..=self.log).rev() {
			if ((l >> i) << i) != l {
				self.push(l >> i);
			}
			if ((r >> i) << i) != r {
				self.push((r - 1) >> i);
			}
		}
	}
	fn get(&mut self, mut i: usize) -> T {
		assert!(i < self.n);
		i += self.tree_offset;
		for j in (1..=self.log).rev() {
			self.push(i >> j);
		}
		self.tree[i].clone()
	}
	fn set(&mut self, mut i: usize, x: T) {
		assert!(i < self.n);
		i += self.tree_offset;
		for j in (1..=self.log).rev() {
			self.push(i >> j);
		}
		self.tree[i] = x;
		for j in 1..=self.log {
			self.pull(i >> j);
		}
	}
	fn update(&mut self, mut l: usize, mut r: usize, y: U) {
		assert!(l <= r && r < self.n);
		l += self.tree_offset;
		r += self.tree_offset + 1;
		self.range_push(l, r);
		let mut l2 = l;
		let mut r2 = r;
		while l2 < r2 {
			if l2 % 2 == 1 {
				self.apply(l2, y.clone());
				l2 += 1;
			}
			if r2 % 2 == 1 {
				r2 -= 1;
				self.apply(r2, y.clone());
			}
			l2 /= 2;
			r2 /= 2;
		}
		for i in 1..=self.log {
			if ((l >> i) << i) != l {
				self.pull(l >> i);
			}
			if ((r >> i) << i) != r {
				self.pull((r - 1) >> i);
			}
		}
	}
	fn query_all(&self) -> T {
		self.tree[1].clone()
	}
	fn query(&mut self, mut l: usize, mut r: usize) -> T {
		assert!(l <= r && r < self.n);
		l += self.tree_offset;
		r += self.tree_offset + 1;
		self.range_push(l, r);
		let mut left = self.id.clone();
		let mut right = self.id.clone();
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

### Common setups
Range add, range sum: $(M, \mathcal{F}) = ((+,0), \{f:=x+c~|~c \in \mathbb{Z}\})$

```rust
```

Range add, range min: $(M, \mathcal{F}) = ((\min,\infty), \{f:=x+c~|~c \in \mathbb{Z}\})$

```rust
```

Range add, range max: $(M, \mathcal{F}) = ((\max,-\infty), \{f:=x+c~|~c \in \mathbb{Z}\})$

```rust
```

Range update, range sum: $(M, \mathcal{F}) = ((+,0), \{f:=c~|~c \in \mathbb{Z}\})$

```rust
```

Range update, range min: $(M, \mathcal{F}) = ((\min,\infty), \{f:=c~|~c \in \mathbb{Z}\})$

```rust
```

Range update, range max: $(M, \mathcal{F}) = ((\min,\infty), \{f:=c~|~c \in \mathbb{Z}\})$

```rust
```

## Example
```

```

## References
- [AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp)

## Verification
