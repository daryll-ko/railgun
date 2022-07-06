# `custom_hash`
Custom hash for C++'s `unordered_map`.

## Code
```cpp
struct custom_hash {
    static uint64_t split_mix_64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(u_int64_t x) const {
        static const uint64_t r = std::chrono::steady_clock::now().time_since_epoch().count();
        return split_mix_64(x + r);
    }
};
```

## Example
```

```

## Notes

## References
- [Blowing up unordered_map, and how to stop getting hacked on it](https://codeforces.com/blog/entry/62393)

## Verification
- [Library Checker | Associative Array](https://judge.yosupo.jp/problem/associative_array) ([subission link](https://judge.yosupo.jp/submission/94673))