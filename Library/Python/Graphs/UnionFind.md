# `UnionFind`
Implementation of a [union-find data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure).

## Methods
### `__init__`
```python
def __init__(self, n: int) -> None
```

Constructs a union-find data structure for a graph with $n$ vertices.

**Constraints**
- $n \le 10^{8}$

**Time Complexity**
- $O(n)$

### `get_leader`
```python
def get_leader(self, i: int) -> int
```

Returns the leader of vertex $i$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $a(n)$, where $a(n)$ is the [inverse Ackermann function](https://en.wikipedia.org/wiki/Ackermann_function#Inverse)

### `same_leader`
```python
def same_leader(self, a: int, b: int) -> bool
```

Checks if vertices $a$ and $b$ have the same leader (i.e., they belong to the same component).

**Constraints**
- $0 \le a, b < n$

**Time Complexity**
- $a(n)$

### `unite`
```python
def unite(self, a: int, b: int) -> None
```

Unites the components of vertices $a$ and $b$. Nothing happens if $a$ and $b$ are already in the same component.

**Constraints**
- $0 \le a, b < n$

**Time Complexity**
- $a(n)$

## Code
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

## Verification
- [CSES Problem Set | Road Reparation](https://cses.fi/problemset/task/1675/)
- [CSES Problem Set | Road Construction](https://cses.fi/problemset/task/1676/)
- [Library Checker | Unionfind](https://judge.yosupo.jp/problem/unionfind) ([submission link](https://judge.yosupo.jp/submission/94677))