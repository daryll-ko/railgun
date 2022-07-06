# `UnionFind`
Implementation of a [union-find data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure).

## Methods
### `new`
```rust
fn new(n: usize) -> UnionFind
```

Constructs a union-find data structure for a graph with $n$ vertices.

**Constraints**
- $n \le 10^{8}$

**Time Complexity**
- $O(n)$

### `get_leader`
```rust
fn get_leader(&mut self, i: usize) -> usize
```

Returns the leader of vertex $i$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $a(n)$, where $a(n)$ is the [inverse Ackermann function](https://en.wikipedia.org/wiki/Ackermann_function#Inverse)

### `same_leader`
```rust
fn same_leader(&mut self, a: usize, b: usize) -> bool
```

Checks if vertices $a$ and $b$ have the same leader (i.e., they belong to the same component).

**Constraints**
- $0 \le a, b < n$

**Time Complexity**
- $a(n)$

### `unite`
```rust
fn unite(&mut self, mut a: usize, mut b: usize)
```

Unites the components of vertices $a$ and $b$. Nothing happens if $a$ and $b$ are already in the same component.

**Constraints**
- $0 \le a, b < n$

**Time Complexity**
- $a(n)$

## Code
```rust
struct UnionFind {
    link: Vec<usize>,
    size: Vec<usize>,
    number_of_components: usize,
    largest_component: usize,
}

impl UnionFind {
    fn new(n: usize) -> UnionFind {
        UnionFind {
            link: (0..n).collect(),
            size: vec![1; n],
            number_of_components: n,
            largest_component: 1,
        }
    }
    fn get_leader(&mut self, i: usize) -> usize {
        if i == self.link[i] {
            i
        } else {
            let answer = self.get_leader(self.link[i]);
            self.link[i] = answer;
            answer
        }
    }
    fn same_leader(&mut self, a: usize, b: usize) -> bool {
        self.get_leader(a) == self.get_leader(b)
    }
    fn unite(&mut self, mut a: usize, mut b: usize) {
	    if !self.same_leader(a, b) {
	        a = self.get_leader(a);
	        b = self.get_leader(b);
	        if self.size[a] < self.size[b] {
	            let c = a;
	            a = b;
	            b = c;
	        }
	        self.size[a] += self.size[b];
	        self.link[b] = a;
	        self.number_of_components -= 1;
	        self.largest_component = self.largest_component.max(self.size[a]);
        }
    }
}
```

## Examples
```rust
let mut graph = UnionFind::new(5);
graph.unite(0, 2);
graph.unite(1, 3);
println!("{}", graph.number_of_components);
// outputs: 3
graph.unite(1, 4);
println!("{}", graph.same_leader(0, 4));
// outputs: false
println!("{}", graph.same_leader(3, 4));
// outputs: true
```

## Verification
- [CSES Problem Set | Road Reparation](https://cses.fi/problemset/task/1675/)
- [CSES Problem Set | Road Construction](https://cses.fi/problemset/task/1676/)
- [Library Checker | Unionfind](https://judge.yosupo.jp/problem/unionfind) ([submission link](https://judge.yosupo.jp/submission/94676))