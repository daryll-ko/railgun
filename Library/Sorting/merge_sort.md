# `merge_sort`

Given a vector of length $n$ and a mutable variable `answer`, returns a sorted version of the vector and sets `answer`'s value to the inversion index (i.e., number of inversions) of the original vector.

For the Python implementation, `merge_sort` itself returns the inversion index, so there's no need to pass in a second variable.

Runs in $O(n \log n)$ time.

## Code
### Rust
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

### Python
```python
def merge(a: list[int], a_inversions: int, b: list[int], b_inversions: int) -> tuple[list[int], int]:
    result = []
    i, j = 0, 0
    merge_inversions = 0
    while i < len(a) and j < len(b):
        if a[i] <= b[j]:
            merge_inversions += j
            result.append(a[i])
            i += 1
        else:
            result.append(b[j])
            j += 1
    while i < len(a):
        merge_inversions += j
        result.append(a[i])
        i += 1
    while j < len(b):
        result.append(b[j])
        j += 1
    return result, a_inversions + b_inversions + merge_inversions


def merge_sort(v: list[int]) -> tuple[list[int], int]:
    n = len(v)
    if n == 1:
        return v, 0
    else:
        return merge(*merge_sort(v[:(n // 2)]), *merge_sort(v[(n // 2):]))
```

## Examples
### Rust
```rust
let pi = vec![31, 41, 59, 26, 5];
let mut inversions = 0;
let sorted_pi = merge_sort(&pi, &mut inversions);
println!("{:?}\n{}", sorted_pi, inversions);
// outputs:
//    [5, 26, 31, 41, 59]
//    7
```

### Python
```python
v = [31, 41, 59, 26, 5]
sorted_v, inversions = merge_sort(v)
print(sorted_v)
print(inversions)
# outputs:
#    [5, 26, 31, 41, 59]
#    7
```

## Constraints
- $n \le 4 \times 10^{6}$
- `i64` can be replaced with any **integer** type.

## Notes
- This is a bit slower than simply using `.sort()`.

## Verification
- [Distinct Numbers](https://cses.fi/problemset/task/1621/)