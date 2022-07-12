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
`update` and `query` below assume that `op` runs in $O(1)$ time. If that's not the case, then just multiply their listed time complexities with `op`'s runtime.

For example, if `op` is matrix multiplication, which runs in $O(k^{3})$ time, then `update` and `query` take $O(k^{3}\log n)$ time instead of $O(\log n)$ time.

### `SegmentTree`
```cpp
SegmentTree(vector<T> v, int n, T op, F id)
```

Constructs a segment tree from the vector $v$ with length $n$, where $v$ has elements of the monoid $M = (op, id)$.

**Constraints**
- $n \le 4 \times 10^{6}$
- `op` is of the form `[](int a, int b) { return f(a, b); }`

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
template <class T, class F = function<T(T, T)>>
struct SegmentTree {

    int n, tree_offset;
    vector<T> tree;
    T id;
    F op;

    SegmentTree(vector<T> v, int n, T id, F op): n(n), id(id), op(op) {
        for (tree_offset = 1; tree_offset < n; tree_offset *= 2);
        tree.assign(2 * tree_offset, id);
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
        T left = id, right = id;
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
```cpp
vector<int> v = {2, 8, 7, 5, 6, 4, 1, 3, 10, 9};

SegmentTree tree(v, 10, -2'000'000'000, [](int a, int b) { return max(a, b); } );
// (op, id) = max(a, b), -∞

tree.update(3, 11);
printf("%d\n", tree.query(0, 4));
//      i  |  0   1   2   3   4
// tree[i] |  2   8   7  11   6
//                        ^
// outputs: 11

tree.update(6, 314);
printf("%d\n", tree.query_all());
//      i  |  0   1   2   3   4   5    6   7   8   9
// tree[i] |  2   8   7  11   6   4  314   3  10   9
//                                     ^
// outputs: 314
```

## References
* [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/1D%20Range%20Queries%20(9.2)/SegTree%20(9.2).h)
* [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/SegmentTree.h)
* [AtCoder Library](https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp)

## Verification
* [CSES Problem Set | Dynamic Range Minimum Queries](https://cses.fi/problemset/task/1649)