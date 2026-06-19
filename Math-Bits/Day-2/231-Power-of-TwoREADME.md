# 231. Power of Two

[Link to LeetCode Problem](https://leetcode.com/problems/power-of-two/)

---

## 📝 Problem Statement

Given an integer `n`, return `true` if it is a power of two, otherwise return `false`.

An integer `n` is a power of two if there exists an integer `x` such that `n == 2ˣ`.

### Example

```
Input:  n = 1    → Output: true   (2⁰ = 1)
Input:  n = 16   → Output: true   (2⁴ = 16)
Input:  n = 3    → Output: false
Input:  n = -1   → Output: false
```

---

# 💡 Intuition & Approach

## Bit Trick: `n & (n - 1) == 0`

Powers of two in binary have **exactly one `1` bit**:

```
1  → 0001
2  → 0010
4  → 0100
8  → 1000
```

Subtracting 1 flips all bits from that position downward:

```
8  → 1000
7  → 0111
8 & 7 = 0000 → power of two ✅

6  → 0110
5  → 0101
6 & 5 = 0100 ≠ 0 → NOT a power of two ✗
```

## The Full Condition

```cpp
n > 0 && (n & (n - 1)) == 0
```

- `n > 0` guards against `0` and negative numbers (which are never powers of two)
- `n & (n-1)` clears the lowest set bit — for powers of two this gives `0`

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(1)
```

- Single bitwise operation

## Space Complexity

```
O(1)
```

---

# 💻 Code

```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n > 0 && (n & (n - 1)) == 0) {
            return 1;
        } else
            return 0;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ `n = 0` → `0 > 0` fails → returns `false`

✅ `n = 1` → `1 & 0 = 0` → returns `true` (2⁰ = 1)

✅ Negative numbers → `n > 0` fails → returns `false`

✅ `INT_MIN` → negative, handled by `n > 0`

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
n > 0 && (n & (n-1)) == 0
```

`n & (n-1)` removes the lowest set bit. If only one bit was set (power of two), result is 0.

## Common Mistakes

❌ Forgetting `n > 0` guard → `n = 0` would incorrectly return `true` since `0 & (-1) = 0`.

❌ Using `%` or loop division → works but is O(log n), not O(1).

---

## Related Problems

- 191. Number of 1 Bits (Hamming Weight)
- 342. Power of Four
- 326. Power of Three

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Is this number a power of 2?
- Does this number have exactly one set bit?

Think:

```
n & (n-1) == 0  (with n > 0 guard)
```
