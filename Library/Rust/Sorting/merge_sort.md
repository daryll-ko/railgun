# `merge_sort`

Given a vector $v$ of length $n$ and a mutable variable `answer`, returns the sorted version of $v$ and sets `answer`'s value to the inversion index (i.e., number of inversions) of $v$.

**Constraints**
- $n \le 4 \times 10^{6}$

**Time Complexity**
- $O(n \log n)$

## Code
```rust
fn merge(a: &[i64], b: &[i64], answer: &mut usize) -> Vec<i64> {
    let mut result: Vec<i64> = vec![];
    let mut i = 0;
    let mut j = 0;
    while i < a.len() && j < b.len() {
        if a[i] <= b[j] {
            *answer += j;
            result.push(a[i]);
            i += 1;
        } else {
            result.push(b[j]);
            j += 1;
        }
    }
    while i < a.len() {
        *answer += j;
        result.push(a[i]);
        i += 1;
    }
    while j < b.len() {
        result.push(b[j]);
        j += 1;
    }
    result
}

fn merge_sort(v: &[i64], answer: &mut usize) -> Vec<i64> {
    let n = v.len();
    if n == 1 {
        v.to_vec()
    } else {
        merge(
            &merge_sort(&v[..(n / 2)], answer),
            &merge_sort(&v[(n / 2)..], answer),
            answer,
        )
    }
}
```

## Examples
```rust
let pi = vec![31, 41, 59, 26, 5];
let mut inversions = 0;
let sorted_pi = merge_sort(&pi, &mut inversions);
println!("{:?}\n{}", sorted_pi, inversions);
// outputs:
//    [5, 26, 31, 41, 59]
//    7
```

## Notes
- This is a bit slower than simply using `.sort()`.

## Verification
- [Distinct Numbers](https://cses.fi/problemset/task/1621/)