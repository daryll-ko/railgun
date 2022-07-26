# `Dinitz`
Implementation of [Dinitz' algorithm](https://en.wikipedia.org/wiki/Dinic%27s_algorithm).

## Methods
### `Dinitz`
```cpp
Dinitz(int n)
```

Initializes a flow network with $n$ vertices.

**Constraints**
- $n \le 100$ (depends on the number of edges, but this is a relatively safe bound)

**Time Complexity**
- $O(n)$

### `compute_flow`
```cpp
F compute_flow(int s, int t)
```

Computes the maximum flow from the source $s$ to the sink $t$.

**Time Complexity**
- $O(n^{2}m)$ in general
- $O(\min(n^{2/3}m, m^{3/2}))$ if all capacities are $1$

## Code
```cpp
using i64 = int64_t;
```

```cpp
template <class F = i64>
struct Dinitz {
	struct Edge {
		int v, index;
		F capacity;
	};

	int n;
	vector<vector<Edge>> a;

	Dinitz(int n): n(n) {
		a.resize(n);
	}

	pair<int, int> add_edge(int u, int v, F capacity, F reverse_capacity = 0) {
		assert(min(capacity, reverse_capacity) >= 0);
		a[u].push_back({v, (int)a[v].size(), capacity});
		a[v].push_back({u, (int)a[u].size() - 1, reverse_capacity});
		return make_pair(v, (int)a[v].size() - 1);
	}

	F get_flow(pair<int, int> edge) {
		const Edge& e = a[edge.first][edge.second];
		return a[e.v][e.index].capacity;
	}

	vector<int> level, pointer;

	bool bfs(int s, int t) {
		level = pointer = vector<int>(n);
		level[s] = 1;
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (auto& e : a[u]) {
				if (e.capacity > 0 && level[e.v] == 0) {
					q.push(e.v);
					level[e.v] = level[u] + 1;
					if (e.v == t) {
						return true;
					}
				}
			}
		}
		return false;
	}

	F dfs(int u, int t, F current_flow) {
		if (u == t) {
			return current_flow;
		}
		for (int& i = pointer[u]; i < (int)a[u].size(); ++i) {
			Edge& e = a[u][i];
			if (level[e.v] != level[u] + 1 || e.capacity == 0) {
				continue;
			}
			F next_flow = dfs(e.v, t, min(current_flow, e.capacity));
			if (next_flow > 0) {
				e.capacity -= next_flow;
				a[e.v][e.index].capacity += next_flow;
				return next_flow;
			}
		}
		return 0;
	}

	F compute_flow(int s, int t) {
		F flow = 0;
		while (bfs(s, t)) {
			F next_flow;
			do {
				next_flow = dfs(s, t, numeric_limits<F>::max());
				flow += next_flow;
			} while (next_flow > 0);
		}
		return flow;
	}
};
```

## Example
```

```

## Notes
- unless the constraints are glaringly large, just assume that `compute_flow`'s complexity is $O(\verb|passes time limit|)$
- once `compute_flow` has been called, the **minimum cut** consists of all edges `e = a[u][_]` such that:
	- `level[u] != 0`
	- `level[e.v] == 0`
	- `e.capacity == 0`

## References
- [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Flows%20(12.3)/Dinic.h)
- [Maximum flow - Dinic's algorithm | Algorithms for Competitive Programming](https://cp-algorithms.web.app/graph/dinic.html)

## Verification
