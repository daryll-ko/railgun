# `LazySegmentTree`
Implementation of an iterative [lazy segment tree](https://cp-algorithms.com/data_structures/segment_tree.html#range-updates-lazy-propagation).

## Methods

## Code
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

## Example
```

```

## References

## Verification
