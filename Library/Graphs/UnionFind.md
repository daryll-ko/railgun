# `UnionFind`
Implementation of a [union-find data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure).

Includes the following methods:

```rust
fn new(n: usize) -> UnionFind
```

Creates a new instance of the data structure for a graph with $n$ vertices. Takes $O(n)$ time.

```rust
fn get_leader(&mut self, i: usize) -> usize
```

Returns the leader of vertex $i$. Takes $\alpha(n)$ time, where $\alpha(n)$ is the [inverse Ackermann function](https://en.wikipedia.org/wiki/Ackermann_function#Inverse) (tl;dr $O(1)$).

```rust
fn same_leader(&mut self, a: usize, b: usize) -> bool
```

Checks if vertices $a$ and $b$ have the same leader (i.e., they belong to the same component). Takes $\alpha(n)$ time.

```rust
fn unite(&mut self, mut a: usize, mut b: usize)
```

Unites the components of vertices $a$ and $b$. Takes $\alpha(n)$ time. Nothing happens if $a$ and $b$ are already in the same component.

## Code
### Rust
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
	    if !same_leader(a, b) {
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

### Python
```python
from dataclasses import dataclass
```

```python
@dataclass
class UnionFind:

    def __init__(self, n: int) -> None:
        self.link = list(range(n))
        self.size = [1 for _ in range(n)]
        self.number_of_components = n
        self.largest_component = 1

    def get_leader(self, i: int) -> int:
        if i == self.link[i]:
            return i
        else:
            answer = self.get_leader(self.link[i])
            self.link[i] = answer
            return answer

    def same_leader(self, a: int, b: int) -> bool:
        return self.get_leader(a) == self.get_leader(b)

    def unite(self, a: int, b: int) -> None:
        if not self.same_leader(a, b):
            a = self.get_leader(a)
            b = self.get_leader(b)
            if self.size[a] < self.size[b]:
                a, b = b, a
            self.size[a] += self.size[b]
            self.link[b] = a
            self.number_of_components -= 1
            self.largest_component = max(self.largest_component, self.size[a])
```

## Examples
### Rust
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

### Python
```python
graph = UnionFind(5)
graph.unite(0, 2)
graph.unite(1, 3)
print(graph.number_of_components)
# outputs: 3
graph.unite(1, 4)
print(graph.same_leader(0, 4))
# outputs: False
print(graph.same_leader(3, 4))
# outputs: True
```

## Constraints
- $n \le 10^{8}$

## Notes
- vertex indices are $0$-indexed; be careful!

## Verification
- [Road Reparation](https://cses.fi/problemset/task/1675/)
- [Road Construction](https://cses.fi/problemset/task/1676/)