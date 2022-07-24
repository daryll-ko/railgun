# `merge_sort`

Given a vector $v$ of length $n$, returns the sorted version of $v$ and the inversion index (i.e., number of inversions) of $v$.

**Constraints**
- $n \le 4 \times 10^{6}$

**Time Complexity**
- $O(n \log n)$

## Code
```python
from typing import List, Tuple
```

```python
def merge(a: List[int], a_inversions: int, b: List[int], b_inversions: int) -> Tuple[List[int], int]:
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


def merge_sort(v: List[int]) -> Tuple[List[int], int]:
	n = len(v)
	if n == 1:
		return v, 0
	else:
		return merge(*merge_sort(v[:(n // 2)]), *merge_sort(v[(n // 2):]))
```

## Example
```python
v = [31, 41, 59, 26, 5]
sorted_v, inversions = merge_sort(v)
print(sorted_v)
print(inversions)
# outputs:
#    [5, 26, 31, 41, 59]
#    7
```

## Notes
- This is a bit slower than simply using `.sort()`.

## Verification
- [Distinct Numbers](https://cses.fi/problemset/task/1621/)