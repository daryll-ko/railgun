# `insertion_sort`
Given an array $A$ and its length $n$, sorts $A$ in-place.

**Constraints**
- $n \le 10^{4}$
- the array's contents may be of any type that has a [weak partial order](https://eli.thegreenplace.net/2018/partial-and-total-orders/#:~:text=While%20a%20partial%20order%20lets,all%20elements%20in%20a%20set.).

**Time Complexity**
- $O(n^{2})$

## Code
```python
from typing import List
```

```python
def insertion_sort(a: List[int], n: int) -> None:
    for i in range(1, n):
        value = a[i]
        j = i - 1
        while j >= 0 and a[j] > value:
            a[j + 1] = a[j]
            j -= 1
        a[j + 1] = value
```

## Examples
```python
ratings = [9.25, 9.75, 9.5, 10, 9]
insertion_sort(ratings, 5)
print(ratings)
# outputs: [9, 9.25, 9.5, 9.75, 10]
```

## Notes
- this is just for demonstration purposes; please don't use this for actual sorting!

## References
- [Introduction to Algorithms, 4th Edition](https://mitpress.mit.edu/books/introduction-algorithms-fourth-edition)