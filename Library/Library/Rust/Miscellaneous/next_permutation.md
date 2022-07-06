# `next_permutation`
Given a slice $v$:
- if $v$ is not in reverse sorted order, returns `true` and mutates $v$ to its next permutation.
- otherwise, returns `false` and mutates $v$ to sorted order (i.e., its first permutation).

The elements of the slice may be any type `T` that implements the `Ord` trait.

## Code
```rust
fn next_permutation<T>(v: &mut [T]) -> bool
where
    T: std::cmp::Ord,
{
    use std::cmp::Ordering;

    let n = v.len();
    let mut j = n;
    for i in (1..n).rev() {
        if v[i - 1] < v[i] {
            j = i - 1;
            break;
        }
    }

    if j == n {
        v.reverse();
        return false;
    }

    let k = v[(j + 1)..]
        .binary_search_by(|n| match v[j].cmp(n) {
            Ordering::Equal => Ordering::Greater,
            ord => ord,
        })
        .unwrap_err();
    v.swap(j, j + k);
    v[(j + 1)..].reverse();
    true
}
```

## Example
```rust
let mut v = vec![1, 2, 3];
loop {
    println!("{:?}", v);
    if !next_permutation(&mut v) {
        break;
    }
}
// outputs:
//    [1, 2, 3]
//    [1, 3, 2]
//    [2, 1, 3]
//    [2, 3, 1]
//    [3, 1, 2]
//    [3, 2, 1]
```

## Notes
- This is built-in to C++ as `next_permutation`.

## References
- [Rust implementation of next-permutation](https://codereview.stackexchange.com/questions/259168/rust-implementation-of-next-permutation)

## Verification
- [CSES Problem Set | Creating Strings](https://cses.fi/problemset/task/1622/)