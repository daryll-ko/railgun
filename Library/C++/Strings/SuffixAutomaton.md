# `SuffixAutomaton`
Implementation of a [suffix automaton](https://cp-algorithms.com/string/suffix-automaton.html).

## Methods
### `SuffixAutomaton`
```cpp
SuffixAutomaton(string s)
```

Constructs the suffix automaton for the given string $s$.

**Constraints**
- $|s| \le 10^{8}$

**Time Complexity**
- $O(|s|)$

### `distinct_substrings`
```cpp
i64 distinct_substrings()
```

Returns the number of distinct substrings of $s$ (including the empty string $\varepsilon$).

**Time Complexity**
- $O(|s|)$

### `kth_substring`
```cpp
string kth_substring(i64 k)
```

Returns the $k^{\text{th}}$ lexicographically smallest **distinct** substring of $s$ (where the smallest substring is the empty string $\varepsilon$).

**Constraints**
- $1 \le k \le \verb|distinct_substrings(|s\verb|)|$

**Time Complexity**
- $O(|t|)$, where $t$ is the answer

## Code
```cpp
using i64 = int64_t;
```

```cpp
struct SuffixAutomaton {
	int n = 1;
	vector<int> link = {-1}, length = {0}, position = {-1};
	vector<map<char, int>> next{1};
	vector<bool> is_clone = {false};
	vector<vector<int>> inverse_links;

	SuffixAutomaton(string s) {
		int last = 0;
		for (char c : s) {
			last = add(last, c);
		}
		fill_inverse_links();
	}

	int add(int u, char c) {
		auto get_next = [&]() {
			if (u == -1) {
				return 0;
			}
			int v = next[u][c];
			if (length[u] + 1 == length[v]) {
				return v;
			}
			int clone = n++;
			link.push_back(link[v]);
			link[v] = clone;
			length.push_back(length[u] + 1);
			next.push_back(next[v]);
			position.push_back(position[u]);
			is_clone.push_back(true);
			for (; ~u && next[u][c] == v; u = link[u]) {
				next[u][c] = clone;
			}
			return clone;
		};

		int current = n++;
		link.emplace_back();
		length.push_back(length[u] + 1);
		next.emplace_back();
		position.push_back(position[u] + 1);
		is_clone.push_back(false);
		for (; ~u && !next[u].count(c); u = link[u]) {
			next[u][c] = current;
		}
		link[current] = get_next();
		return current;
	}

	void fill_inverse_links() {
		inverse_links.resize(n);
		for (int i = 1; i < n; ++i) {
			inverse_links[link[i]].push_back(i);
		}
	}

	// applications

	i64 paths_starting_at[200'005] = {};
	bitset<200'005> visited;

	void dfs(int u) {
		visited[u] = true;
		paths_starting_at[u] = 1;
		for (auto& [_, v] : next[u]) {
			if (!visited[v]) {
				dfs(v);
			}
			paths_starting_at[u] += paths_starting_at[v];
		}
	}

	i64 distinct_substrings() {
		if (!visited[0]) {
			dfs(0);
		}
		return paths_starting_at[0];
	}

	string kth_substring(i64 k) {
		if (!visited[0]) {
			dfs(0);
		}
		string answer = "";
		int u = 0;
		while (k > 1) {
			--k;
			for (int i = 0; i < 26; ++i) {
				if (next[u].count((char)('a' + i))) {
					int v = next[u][(char)('a' + i)];
					if (paths_starting_at[v] < k) {
						k -= paths_starting_at[v];
					} else {
						answer += (char)('a' + i);
						u = v;
						break;
					}
				}
			}
		}
		return answer;
	}
};
```

## Example
```

```

## References
- [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/strings%20(14)/Heavy/SuffixAutomaton.h)
- [Suffix Automaton | Algorithms for Competitive Programming](https://cp-algorithms.com/string/suffix-automaton.html)

## Verification
- [CSES Problem Set | Distinct Substrings](https://cses.fi/problemset/task/2105)
- [CSES Problem Set | Substring Order I](https://cses.fi/problemset/task/2108)