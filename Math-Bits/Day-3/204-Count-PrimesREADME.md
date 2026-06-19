# 204. Count Primes

[Link to LeetCode Problem](https://leetcode.com/problems/count-primes/)

---

## 📝 Problem Statement

Given an integer `n`, return the number of prime numbers that are **strictly less than** `n`.

### Example

```
Input:  n = 10  → Output: 4   (primes: 2, 3, 5, 7)
Input:  n = 0   → Output: 0
Input:  n = 1   → Output: 0
```

---

# 💡 Intuition & Approach

## Sieve of Eratosthenes

Instead of checking each number individually (O(n√n)), the Sieve eliminates all multiples of every prime found, running in near-linear time.

### Algorithm

1. Create a boolean array `prime[0..n-1]`, initialized to `true`
2. Set `prime[0] = prime[1] = false` (0 and 1 are not prime)
3. For each `i` from `2` to `√n`:
   - If `prime[i]` is still `true` → it's prime
   - Mark all multiples of `i` starting from `i*i` as `false`
4. Count all remaining `true` entries from `2` to `n-1`

### Why start marking from `i*i`?

All smaller multiples of `i` (like `2i`, `3i`, ..., `(i-1)*i`) have already been crossed out by smaller primes.

### Trace for n = 10

```
Initial: [F, F, T, T, T, T, T, T, T, T]
         [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

i=2: mark 4,6,8 → [F,F,T,T,F,T,F,T,F,T]
i=3: mark 9     → [F,F,T,T,F,T,F,T,F,F]

Count trues from 2..9 = 2,3,5,7 → 4 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(n log log n)
```

- The sieve runs in O(n log log n) due to the harmonic series of prime reciprocals

## Space Complexity

```
O(n)
```

- Boolean array of size `n`

---

# 💻 Code

```cpp
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return 0;

        vector<bool> prime(n, true);
        prime[0] = prime[1] = false;

        for (long long i = 2; i * i < n; i++) {
            if (prime[i]) {
                for (long long j = i * i; j < n; j += i) {
                    prime[j] = false;
                }
            }
        }

        int count = 0;
        for (int i = 2; i < n; i++) {
            if (prime[i]) count++;
        }
        return count;
    }
};
```

> **Note**: `long long` for loop variables avoids integer overflow when `i * i` exceeds `INT_MAX` for large `n`.

---

# 🔍 Edge Cases Handled

✅ `n <= 2` → no primes below 2, return `0` directly

✅ `n = 3` → only checks `2`, returns `1`

✅ Large `n` → `long long` prevents `i * i` overflow

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Sieve: for each prime i, mark all multiples i*i, i*i+i, i*i+2i, ... as composite
```

## Why `i * i < n` (not `i < n`) in outer loop?

Any composite number ≤ n has a prime factor ≤ √n. So we only need to sieve up to √n.

## Common Mistakes

❌ Starting inner loop from `2*i` instead of `i*i` → correct but slower (redundant marking).

❌ Using `int` for `i * i` → overflow for large `n` (use `long long`).

❌ Marking `prime[0]` and `prime[1]` as true → must explicitly set to `false`.

---

## Related Problems

- 231. Power of Two
- 263. Ugly Number
- 279. Perfect Squares

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Count primes below N
- Check if a number is prime for many values

Think:

```
Sieve of Eratosthenes → O(n log log n) preprocessing
```

Template:
```
prime = [true] * n
prime[0] = prime[1] = false
for i in 2..√n:
    if prime[i]: mark i*i, i*i+i, ... as false
count trues from 2..n-1
```
