# `insertion_sort`
Given an array $A$ and its length $n$, sorts $A$ in-place.

Runs in $O(n^{2})$ time and takes $O(1)$ space.

## Code
### Rust
```rust
fn insertion_sort(a: &mut [i32], n: usize) {
    for i in 1..n {
        let value = a[i];
        let mut j = i;
        while j > 0 && a[j - 1] > value {
            a[j] = a[j - 1];
            j -= 1;
        }
        a[j] = value;
    }
}
```

### C
```c
void insertion_sort(int a[], int n) {
  for (int i = 1; i < n; ++i) {
    int value = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > value) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = value;
  }
}
```

### Python
```python
def insertion_sort(a: list[int], n: int) -> None:
    for i in range(1, n):
        value = a[i]
        j = i - 1
        while j >= 0 and a[j] > value:
            a[j + 1] = a[j]
            j -= 1
        a[j + 1] = value
```

## Examples
### Rust
```rust
let mut ratings = vec![9.25, 9.75, 9.5, 10., 9.];
insertion_sort(&mut ratings, 5);
println!("{:?}", ratings);
// outputs: [9, 9.25, 9.5, 9.75, 10]
```

### Python
```python
ratings = [9.25, 9.75, 9.5, 10, 9]
insertion_sort(ratings, 5)
print(ratings)
# outputs: [9, 9.25, 9.5, 9.75, 10]
```

## Constraints
- $n \le 10^{4}$
- The contents of a list can be any type that has a [weak partial order](https://eli.thegreenplace.net/2018/partial-and-total-orders/#:~:text=While%20a%20partial%20order%20lets,all%20elements%20in%20a%20set.).

## Notes
- implementation in Rust stumped me for a bit, since `usize` is restrictive
	- the key was just to shift indices
	- this is a recurring challenge, especially with graph problems
- for demonstration purposes; please don't use this for actual sorting

## References
- [Introduction to Algorithms, 4th Edition](https://mitpress.mit.edu/books/introduction-algorithms-fourth-edition)