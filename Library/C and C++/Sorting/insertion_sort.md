# `insertion_sort`
Given an array $A$ and its length $n$, sorts $A$ in-place.

**Constraints**
- $n \le 10^{4}$
- the array's contents may be of any type that has a [weak partial order](https://eli.thegreenplace.net/2018/partial-and-total-orders/#:~:text=While%20a%20partial%20order%20lets,all%20elements%20in%20a%20set.).

**Time Complexity**
- $O(n^{2})$

## Code
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

## Example
```cpp
long double ratings[5] = {9.25, 9.75, 9.5, 10, 9};
insertion_sort(ratings, 5);
for (long double rating : ratings) {
	printf("%Lf ", rating);
}
// outputs: 9 9.25 9.5 9.75 10
```

## Notes
- this is just for demonstration purposes; please don't use this for actual sorting!

## References
- [Introduction to Algorithms, 4th Edition](https://mitpress.mit.edu/books/introduction-algorithms-fourth-edition)