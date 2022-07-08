# `SegmentTree`
Implementation of an iterative [segment tree](https://en.wikipedia.org/wiki/Segment_tree).

Suppose we have a [monoid](https://mathworld.wolfram.com/Monoid.html#:~:text=A%20monoid%20is%20a%20set,contain%20at%20least%20one%20element.) $M$ with operation $op$ and identity element $id$. A segment tree allows us to answer queries about an array $A$ of $M$'s elements in the form

$$
query(l, r) = op(A[l], A[l + 1], \dots, A[r]).
$$

For example, if $M = (op, id) = (+, 0)$, then

$$
query(l, r) = A[l] + A[l + 1] + \dots + A[r].
$$

if $M = (op, id) = (\max, -\infty)$, then

$$
query(l, r) = \max(A[l], A[l + 1], \dots, A[r]).
$$

A list of common pairs $(op, id)$ is include in the **Code** section below for convenience.

## Methods
`add`, `update`, and `query` below assume that `op` runs in $O(1)$ time. If that's not the case, then just multiply their listed time complexities with `op`'s runtime.

For example, if `op` is matrix multiplication, which runs in $O(k^{3})$ time, then `add`, `update`, and `query` take $O(k^{3}\log n)$ time instead of $O(\log n)$ time.

### `SegmentTree`
```cpp
SegmentTree(vector<T> v, int n)
```

Constructs a segment tree from the vector $v$ with length $n$.

**Constraints**
- $n \le 4 \times 10^{6}$
- `T` is the type of element your monoid uses (e.g., `int64_t` for $M = (0, +)$ )

**Time Complexity**
- $O(n)$

### `get_value`
```cpp
T get_value(int i)
```

Returns $v[i]$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $O(1)$

### `add`
```cpp
void add(int i, T x)
```

Adds $x$ to $v[i]$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $O(\log n)$

### `update`
```cpp
void update(int i, T x)
```

Sets $v[i]$ to $x$.

**Constraints**
- $0 \le i < n$

**Time Complexity**
- $O(\log n)$

### `query_all`
```cpp
T query_all()
```

Returns $op(v[0], v[1], \dots, v[n - 1])$. Equivalent to `query(0, n - 1)`.

**Time Complexity**
- $O(1)$

### `query`
```cpp
T query(int l, int r)
```

Returns $op(v[l], v[l + 1], \dots, v[r])$.

**Constraints**
- $0 \le l \le r < n$

**Time Complexity**
- $O(\log n)$

## Code
**Common $(op, id)$ pairs**

| $op$                    | $id$                                                  | Time Complexity                                    |
| ----------------------- | ----------------------------------------------------- | -------------------------------------------------- |
| $a + b$                 | $0$                                                   | $O(1)$                                             |
| $ab$                    | $1$                                                   | $O(1)$                                             |
| $\min(a, b)$            | $\infty$ (maximum value of numerical data type used)  | $O(1)$                                             |
| $\max(a, b)$            | $-\infty$ (minimum value of numerical data type used) | $O(1)$                                             |
| $\gcd(a, b)$            | 0                                                     | $O(1)$                                                   |
| $a \times b$ (matrices) | $I_{k}$ ($k \times k$ identity matrix)                | $O(k^{3})$                                         |

```cpp
template <class T>
struct SegmentTree {
    
    // change ID and op as necessary:
    const T ID = 2000000000;

    T op(T a, T b) {
        return min(a, b);
    }

    int n, tree_offset;
    vector<T> tree;

    SegmentTree(vector<T> v, int n) {
        this->n = n;
        for (tree_offset = 1; tree_offset < n; tree_offset *= 2);
        tree.assign(2 * tree_offset, ID);
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

    T get_value(int i) {
        assert(0 <= i && i < n);
        return tree[i + tree_offset];
    }

    void add(int i, T x) {
        assert(0 <= i && i < n);
        tree[i += tree_offset] += x;
        for (i /= 2; i > 0; i /= 2) {
            pull(i);
        }
    }

    void update(int i, T x) {
        assert(0 <= i && i < n);
        tree[i += tree_offset] = x;
        for (i /= 2; i > 0; i /= 2) {
            pull(i);
        }
    }

    T query_all() {
        return tree[1];
    }

    T query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        T left = ID, right = ID;
        for (l += tree_offset, r += tree_offset + 1; l < r; l /= 2, r /= 2) {
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
* [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/1D%20Range%20Queries%20(9.2)/SegTree%20(9.2).h)
* [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h)
* [AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp)

## Verification
* [CSES Problem Set | Dynamic Range Minimum Queries](https://cses.fi/problemset/task/1649)