# `miller_rabbin`
Performs a deterministic [Miller-Rabbin primality test](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test) for a given integer $n$.

## Methods
```cpp
bool is_prime(int64_t n)
```

Returns whether or not $n$ is prime.

**Time Complexity**
- $O(\log n)$

## Code
```cpp
int64_t mod_mul(int64_t a, int64_t b, int64_t m) {
    return (int64_t)(((__int128_t)a * (__int128_t)b) % (__int128_t)m);
}

int64_t mod_pow(int64_t a, int64_t b, int64_t m) {
    int64_t answer = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            answer = mod_mul(answer, a, m);
        }
        b /= 2;
        a = mod_mul(a, a, m);
    }
    return answer;
}

// returns the pair (s, d) such that n = 2^s × d and d is odd
pair<int64_t, int64_t> decompose(int64_t n) {
    int64_t s = __builtin_ctzll(n);
    int64_t d = n >> s;
    return make_pair(s, d);
}

bool is_prime(int64_t n) {
    if (n == 0 || n == 1) {
        return false;
    } else if (n == 2 || n == 3) {
        return true;
    } else if (!(n % 6 == 1 || n % 6 == 5)) {
        return false;
    } else {
        vector<int64_t> bases = {2, 325, 9'375, 28'178, 450'775, 9'780'504, 1'795'265'022};
        auto [s, d] = decompose(n - 1);
        for (int64_t base : bases) {
            int64_t x = mod_pow(base, d, n);
            if (x == 1 || x == n - 1) {
                continue;
            }
            bool proceed_to_next_base = false;
            int64_t r = 1;
            while (r <= s - 1) {
                x = mod_mul(x, x, n);
                if (x == n - 1) {
                    proceed_to_next_base = true;
                    break;
                }
                r++;
            }
            if (proceed_to_next_base) {
                continue;
            } else {
                return false;
            }
        }
        return true;
    }
}
```

## Example
```cpp
int64_t p = 33'478'742'787'241;
printf("%s\n", is_prime(p) ? "true" : "false");
// (...trust me, that's prime)
// outputs: true

int64_t c = 52'069'326'617'183;
printf("%s\n", is_prime(c) ? "true" : "false");
// outputs: false
```

## References
- [Miller-Rabin primality test](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test)
- [Deterministic variants of the Miller-Rabin primality test](https://miller-rabin.appspot.com/)
- [Benjamin Qi's implementation](https://github.com/bqi343/USACO/blob/master/Implementations/content/number-theory%20(11.1)/Primality/MillerRabin.h)
- [KACTL](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/MillerRabin.h)

## Verification
