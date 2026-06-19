# 260. Single Number III

[Link to LeetCode Problem](https://leetcode.com/problems/single-number-iii/)

---

## 📝 Problem Statement

Given an integer array `nums` where exactly **two elements appear only once** and all the other elements appear **exactly twice**, find the two elements that appear only once. Return them in any order.

### Example

```
Input:  nums = [1,2,1,3,2,5]  → Output: [3,5]
Input:  nums = [-1,0]          → Output: [-1,0]
```

---

# 💡 Intuition & Approach

## Step 1 — XOR All Numbers

XOR of all elements cancels pairs. What remains is `x = a XOR b` where `a` and `b` are the two singles.

```
[1,2,1,3,2,5] → XOR all → 1^2^1^3^2^5 = 3^5 = 110^101 = 011 = ... wait
3 = 011, 5 = 101 → XOR = 110 = 6
x = 6 (= 3 XOR 5)
```

## Step 2 — Find a Differentiating Bit

Find the **lowest set bit** of `x`. This bit is set in one of `a` or `b` but not both.

```cpp
unsigned int i = ((unsigned int)x & ~((unsigned int)x - 1));
```

This isolates the lowest set bit (e.g. `6 = 110` → lowest set bit = `010 = 2`).

## Step 3 — Partition and XOR

Split all numbers into two groups:
- Numbers where that bit is `0` → XOR gives `f`
- Numbers where that bit is `1` → XOR gives `s`

Since pairs cancel, `f` and `s` are the two singles.

### Trace for [1, 2, 1, 3, 2, 5]

```
x = 3 XOR 5 = 011 XOR 101 = 110 = 6
lowest set bit of 6: 010 = 2

Bit 1 (value 2) check:
  1 (001) & 2 = 0 → group f
  2 (010) & 2 ≠ 0 → group s
  1 (001) & 2 = 0 → group f
  3 (011) & 2 ≠ 0 → group s
  2 (010) & 2 ≠ 0 → group s
  5 (101) & 2 = 0 → group f

group f: 1^1^5 = 5
group s: 2^3^2 = 3

Result: [5, 3] ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(n)
```

- Two passes through the array

## Space Complexity

```
O(1)
```

---

# 💻 Code

```cpp
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int x = 0;
        for (auto n : nums) {
            x = x ^ n;
        }

        int f = 0, s = 0;
        unsigned int i = ((unsigned int)x & ~((unsigned int)x - 1));

        for (auto n : nums) {
            if ((n & i) == 0) {
                f = f ^ n;
            } else
                s = s ^ n;
        }

        return {f, s};
    }
};
```

> **Note**: `unsigned int` cast ensures correct behavior for the lowest-bit isolation when `x` might be negative.

---

# 🔍 Edge Cases Handled

✅ Negative numbers → handled via unsigned cast in bit isolation

✅ Two adjacent singles → differentiating bit will be found correctly

✅ `[-1, 0]` → XOR = -1 XOR 0 = -1, lowest bit = 1 → partitions correctly

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
1. XOR all → get a^b
2. Isolate lowest set bit of (a^b)
3. Partition array by that bit → XOR each partition → gives a and b
```

## Lowest Set Bit Formula

```cpp
lowest_set_bit = x & (~x + 1)   // equivalent to x & -x for signed
// or safely:
unsigned int bit = (unsigned int)x & ~((unsigned int)x - 1);
```

## Common Mistakes

❌ Forgetting unsigned cast → signed overflow when `x = INT_MIN`.

❌ Using `(n & i) != 0` instead of `== 0` for grouping — the partition direction doesn't matter, just be consistent.

---

## Related Problems

- 136. Single Number (one single → XOR all)
- 137. Single Number II (one single, rest appear 3×)
- 191. Number of 1 Bits

---

# 🧠 Revision Notes

## Pattern Recognition

| Problem | Strategy |
|---------|----------|
| One single (rest ×2) | XOR all |
| One single (rest ×3) | Bit count % 3 |
| Two singles (rest ×2) | XOR all → isolate diff bit → partition → XOR each group |

```
Two singles: XOR → lowest set bit → partition → done
```
