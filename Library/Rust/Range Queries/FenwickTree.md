# `FenwickTree`
Implementation of a [Fenwick tree](https://en.wikipedia.org/wiki/Fenwick_tree).

## Methods
All methods below are **1-indexed**.

### `new`
```rust
fn new(v: &[i64], n: usize) -> FenwickTree
```

Constructs a Fenwick tree from the vector $v$ with length $n$.

**Constraints**
- $n \le 4 \times 10^{6}$ 

**Time Complexity**
- $O(n \log n)$

### `add`
```rust
fn add(&mut self, mut i: usize, x: i64)
```

Adds $x$ to $v[i]$.

**Constraints**
- $1 \le i \le n$

**Time Complexity**
- $O(\log n)$

### `update`
```rust
fn update(&mut self, i: usize, x: i64)
```

Sets $v[i]$ to $x$.

**Constraints**
- $1 \le i \le n$

**Time Complexity**
- $O(\log n)$

### `prefix_query`
```rust
fn prefix_query(&self, mut r: usize) -> i64
```

Returns $v[1] + v[2] + \dots + v[r]$.

**Constraints**
- $1 \le r \le n$

**Time Complexity**
- $O(\log n)$

### `query`
```rust
fn query(&self, l: usize, r: usize) -> i64
```

Returns $v[l] + v[l + 1] + \dots + v[r]$.

**Constraints**
- $1 \le l \le r \le n$

**Time Complexity**
- $O(\log n)$

### `cumulative_lower_bound`
```rust
fn cumulative_lower_bound(&self, mut sum: i64) -> usize
```

Returns the first index $r$ such that $v[1] + v[2] + \dots + v[r] \ge sum$.

Returns $n + 1$ If $sum > v[1] + v[2] + \dots + v[n]$.

If we treat $v$ as a multiset $S$ which contains the counts of numbers $1$ through $n$, then `cumulative_lower_bound`  returns the $sum^{\text{th}}$ smallest element in $S$.

**Constraints**
- All elements of $v$ are nonnegative.

**Time Complexity**
- $O(\log n)$

## Code
```rust
fn lsb(n: usize) -> usize {
    (n as i32 & -(n as i32)) as usize
}

struct FenwickTree {
    n: usize,
    tree: Vec<i64>,
}

impl FenwickTree {
    fn new(v: &[i64], n: usize) -> FenwickTree {
        let mut tree = vec![0; n + 1];
        for i in 1..=n {
            tree[i] = v[i - 1];
            let mut j = lsb(i) >> 1;
            while j > 0 {
                tree[i] += tree[i - j];
                j >>= 1;
            }
        }
        FenwickTree { n, tree }
    }
    fn add(&mut self, mut i: usize, x: i64) {
        while i <= self.n {
            self.tree[i] += x;
            i += lsb(i);
        }
    }
    fn update(&mut self, i: usize, x: i64) {
        let previous_value = self.query(i, i);
        self.add(i, x - previous_value);
    }
    fn prefix_query(&self, mut r: usize) -> i64 {
        let mut sum = 0;
        while r > 0 {
            sum += self.tree[r];
            r -= lsb(r);
        }
        sum
    }
    fn query(&self, l: usize, r: usize) -> i64 {
        self.prefix_query(r) - self.prefix_query(l - 1)
    }
    fn cumulative_lower_bound(&self, mut sum: i64) -> usize {
        let mut position = 0;
        let mut power = 1 << 23;
        while power > 0 {
            if position + power <= self.n && self.tree[position + power] < sum {
                position += power;
                sum -= self.tree[position];
            }
            power >>= 1;
        }
        position + 1
    }
}
```

## Example
```rust
let mut tree = FenwickTree::new(&vec![0; 8], 8);
println!("{}", tree.n);
// outputs: 8
tree.add(7, 11);
tree.add(3, 14);
println!("{}", tree.query(3, 7));
//      i  |  3   4   5   6    7
// tree[i] | 14 + 0 + 0 + 0 + 11 = 25
// outputs: 25
tree.add(4, 6);
tree.update(3, 12);
println!("{}", tree.query(3, 7));
//      i  |  3   4   5   6    7
// tree[i] | 12 + 6 + 0 + 0 + 11 = 29
// outputs: 29
println!("{}", tree.prefix_query(4));
//      i  |  1   2    3   4
// tree[i] |  0 + 0 + 12 + 6 = 18
// outputs: 18
tree.add(5, 7);
println!("{}", tree.cumulative_lower_bound(20));
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
- [Library Checker | Point Add Range Sum](https://judge.yosupo.jp/problem/point_add_range_sum) ([submission link](https://judge.yosupo.jp/submission/94479))