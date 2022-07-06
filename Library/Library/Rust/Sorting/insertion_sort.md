# `insertion_sort`
Given an array $A$ and its length $n$, sorts $A$ in-place.

**Constraints**
- $n \le 10^{4}$
- the array's contents may be of any type that has a [weak partial order](https://eli.thegreenplace.net/2018/partial-and-total-orders/#:~:text=While%20a%20partial%20order%20lets,all%20elements%20in%20a%20set.).

**Time Complexity**
- $O(n^{2})$

## Code
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

## Examples
```rust
let mut ratings = vec![9.25, 9.75, 9.5, 10., 9.];
insertion_sort(&mut ratings, 5);
println!("{:?}", ratings);
// outputs: [9, 9.25, 9.5, 9.75, 10]
```

## Notes
- implementation stumped me for a bit, since `usize` is restrictive
	- the key was just to shift indices!
	- this is a recurring challenge, especially with graph problems
- this is just for demonstration purposes; please don't use this for actual sorting!

## References
- [Introduction to Algorithms, 4th Edition](https://mitpress.mit.edu/books/introduction-algorithms-fourth-edition)