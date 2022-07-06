# `UnionFind`
Implementation of a [union-find data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure).

## Methods
### `new`
```cpp
UnionFind(int n)
```

Constructs a union-find data structure for a graph with $n$ vertices.

**Constraints**
- $n \le 10^{8}$

**Time Complexity**
- $O(n)$

### `get_leader`
```cpp
int get_leader(int i)
```

Returns the leader of vertex $i$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $a(n)$, where $a(n)$ is the [inverse Ackermann function](https://en.wikipedia.org/wiki/Ackermann_function#Inverse)

### `same_leader`
```cpp
bool same_leader(int a, int b)
```

Checks if vertices $a$ and $b$ have the same leader (i.e., they belong to the same component).

**Constraints**
- $0 \le a, b < n$

**Time Complexity**
- $a(n)$

### `unite`
```cpp
void unite(int a, int b)
```

Unites the components of vertices $a$ and $b$. Nothing happens if $a$ and $b$ are already in the same component.

**Constraints**
- $0 \le a, b < n$

**Time Complexity**
- $a(n)$

## Code
```cpp
struct UnionFind {
    vector<int> link;
    vector<int> size;
    int number_of_components;
    int largest_component;

    UnionFind(int n) {
        link = vector<int>(n);
        iota(link.begin(), link.end(), 0);
        size = vector<int>(n, 1);
        number_of_components = n;
        largest_component = 1;
    }

    int get_leader(int i) {
        return i == link[i] ? i : link[i] = get_leader(link[i]);
    }

    bool same_leader(int a, int b) {
        return get_leader(a) == get_leader(b);
    }

    void unite(int a, int b) {
        if (!same_leader(a, b)) {
            a = get_leader(a), b = get_leader(b);
            if (size[a] < size[b]) {
                swap(a, b);
            }
            size[a] += size[b];
            link[b] = a;
            number_of_components--;
            largest_component = max(largest_component, size[a]);
        }
    }
};
```

## Example
```cpp
UnionFind graph(5);
// graph:  2   0
//
//         4   1   3
graph.unite(0, 2);
graph.unite(1, 3);
// graph:  2———0
//
//         4   1———3
printf("%d\n", graph.number_of_components);
// outputs: 3
graph.unite(1, 4);
// graph:  2———0
//
//         4———1———3
printf("%s\n", graph.same_leader(0, 4) ? "true" : "false");
// outputs: false
printf("%s\n", graph.same_leader(3, 4) ? "true" : "false");
// outputs: true
```

## Verification
- [CSES Problem Set | Road Reparation](https://cses.fi/problemset/task/1675/)
- [CSES Problem Set | Road Construction](https://cses.fi/problemset/task/1676/)
- [Library Checker | Unionfind](https://judge.yosupo.jp/problem/unionfind) ([submission link](https://judge.yosupo.jp/submission/94675))