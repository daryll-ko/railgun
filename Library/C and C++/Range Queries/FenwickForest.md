# `FenwickForest`
Implementation of a multidimensional [Fenwick tree](https://en.wikipedia.org/wiki/Fenwick_tree), which I call a Fenwick forest.

## Methods
Like with `FenwickTree`, all methods below are **1-indexed**.

### `FenwickForest`
```cpp
FenwickForest(int n, A... ns)

// read as: FenwickForest(int n_1, int n_2, ..., int n_d)
```

Initializes a Fenwick forest with dimensions $[n_{1}, n_{2}, \dots, n_{d}]$.

**Constraints**
- $n_{1} \times n_{2} \times \dots \times n_{d} \le 10^{8}$

**Time Complexity**
- $O(n_{1} \times n_{2} \times \dots \times n_{d})$

### `add`
```cpp
void add(int i, A... is)

// read as: add(int i_1, int i_2, ..., int i_d, T x)
```

Increases the value of the point $(i_{1}, i_{2}, \dots, i_{d})$ by $x$.

**Constraints**
- $1 \le i_{k} \le n_{k}$ for $k = 1, 2, \dots, d$

**Time Complexity**
- $O(\log n_{1} \times \log n_{2} \times \dots \times \log n_{d})$

### `query`
```cpp
T query(int l, int r, A... lrs)

// read as: query(int l_1, int r_1, int l_2, int r_2, ..., int l_d, int r_d)
```

Returns the sum of the values of all points $(i_{1}, i_{2}, \dots, i_{d})$ that satisfy $l_{k} \le i_{k} \le r_{k}$ for $k = 1, 2, \dots, d$.

**Constraints**
- $1 \le l_{k} \le r_{k} \le n_{k}$ for $k = 1, 2, \dots, d$

**Time Complexity**
- $O(\log n_{1} \times \log n_{2} \times \dots \times \log n_{d})$

## Code
```cpp
int lsb(int n) {
    return n & -n;
}

template <class T>
struct FenwickForest {

    int n;
    vector<FenwickForest<T>> forest;
    T value = 0;

    // 1 dimension
	
    FenwickForest() {}

    void add(T x) {
        value += x;
    }

    T query() {
        return value;
    }

    // > 1 dimension

    template <class... A>
    FenwickForest(int n, A... ns): n(n) {
        forest.resize(n + 1, FenwickForest<T>(ns...));
    }

    template <class... A>
    void add(int i, A... is) {
        assert(1 <= i && i <= n);
        for (; i <= n; i += lsb(i)) {
            forest[i].add(is...);
        }
    }

    template <class... A>
    T prefix_query(int r, A... lrs) {
        assert(0 <= r && r <= n);
        T sum = 0;
        for (; r > 0; r -= lsb(r)) {
            sum += forest[r].query(lrs...);
        }
        return sum;
    }

    template <class... A>
    T query(int l, int r, A... lrs) {
        assert(1 <= l && l <= r && r <= n);
        return prefix_query(r, lrs...) - prefix_query(l - 1, lrs...);
    }

};
```

## Example
```cpp
FenwickForest<int> cuboid(3, 2, 2);
//         ____________
//        /⠡ 0/⠡ 0/⠡ 0/\      
//  z	 /__⠡/__⠡/__⠡/..\    y
//   \  /⠡  /⠡ 0/⠡ 0/\ 0/\  /
//    \/__⠡/__⠡/__⠡/..\/..\/
//     \0 ⠌\0 ⠌\0 ⠌\  /\  /
//      \⠌__\⠌__\⠌__\/..\/
//       \0  \0  \0  \  /
//        \___\___\___\/___x

cuboid.add(1, 2, 1, 7);
//      ____________
//     /⠡ 0/⠡ 0/⠡ 0/\
//    /__⠡/__⠡/__⠡/..\
//   /⠡  /⠡ 7/⠡ 0/\ 0/\
//  /__⠡/__⠡/__⠡/..\/..\
//  \0 ⠌\0 ⠌\0 ⠌\  /\  /
//   \⠌__\⠌__\⠌__\/..\/
//    \0  \0  \0  \  /
//     \___\___\___\/

cuboid.add(3, 2, 2, 5);
//      ____________
//     /⠡ 0/⠡ 0/⠡ 5/\
//    /__⠡/__⠡/__⠡/..\
//   /⠡  /⠡ 7/⠡ 0/\ 0/\
//  /__⠡/__⠡/__⠡/..\/..\
//  \0 ⠌\0 ⠌\0 ⠌\  /\  /
//   \⠌__\⠌__\⠌__\/..\/
//    \0  \0  \0  \  /
//     \___\___\___\/

cuboid.add(2, 1, 1, 3);
//      ____________
//     /⠡ 0/⠡ 0/⠡ 5/\
//    /__⠡/__⠡/__⠡/..\
//   /⠡  /⠡ 7/⠡ 0/\ 0/\
//  /__⠡/__⠡/__⠡/..\/..\
//  \0 ⠌\0 ⠌\0 ⠌\  /\  /
//   \⠌__\⠌__\⠌__\/..\/
//    \0  \3  \0  \  /
//     \___\___\___\/

printf("%d\n", cuboid.query(1, 1, 1, 2, 1, 2));
//      ____
//     /⠡ 0/\
//    /__⠡/..\
//   /⠡  /\ 7/\
//  /__⠡/..\/..\
//  \0 ⠌\  /\  /
//   \⠌__\/..\/
//    \0  \  /
//     \___\/
//
// outputs: 7

printf("%d\n", cuboid.query(2, 3, 1, 2, 1, 2));
//      ________
//     /⠡ 0/⠡ 5/\
//    /__⠡/__⠡/..\
//   /⠡  /⠡ 0/\ 0/\
//  /__⠡/__⠡/..\/..\
//  \0 ⠌\0 ⠌\  /\  /
//   \⠌__\⠌__\/..\/
//    \3  \0  \  /
//     \___\___\/
//
// outputs: 8
```

## References
- [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/data-structures/1D%20Range%20Queries%20(9.2)/BitNd.h)

## Verification
- [CSES Problem Set | Forest Queries II](https://cses.fi/problemset/task/1739)
