# 137. Single Number II

[Link to LeetCode Problem](https://leetcode.com/problems/single-number-ii/)

---

## 📝 Problem Statement

Given an integer array `nums` where every element appears **three times** except for one, which appears exactly **once**. Find and return that single element.

Must run in `O(n)` time and `O(1)` extra space.

### Example

```
Input:  nums = [2,2,3,2]   → Output: 3
Input:  nums = [0,1,0,1,0,1,99]  → Output: 99
```

---

# 💡 Intuition & Approach

## Bit Count mod 3

For each of the 32 bit positions:
- Count how many numbers have that bit set
- If `count % 3 != 0`, then the **single number** has that bit set

This works because every triplet contributes exactly 3 (or 0) to each bit's count. The remainder after `% 3` is the single number's bit.

### Trace for [2, 2, 3, 2]

```
Bit 0:  2=0, 2=0, 3=1, 2=0 → count=1 → 1%3=1 → single has bit 0 set
Bit 1:  2=1, 2=1, 3=1, 2=1 → count=4 → 4%3=1 → single has bit 1 set
→ single = 0b11 = 3 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(32 × n) = O(n)
```

- 32 outer iterations (constant), n inner iterations

## Space Complexity

```
O(1)
```

- Only `ans` and `count` variables

---

# 💻 Code

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            int count = 0;
            for (auto n : nums) {
                if ((n & (1U << i)) != 0) {
                    count++;
                }
            }
            if (count % 3 != 0)
                ans = ans | (1U << i);
        }
        return ans;
    }
};
```

> **Note**: `1U` (unsigned) is used to safely handle bit 31 (sign bit) without undefined behavior from signed overflow.

---

# 🔍 Edge Cases Handled

✅ Negative numbers → handled correctly via `1U << i` (unsigned shift)

✅ Single element array → that element appears once, returned correctly

✅ Bit 31 (sign bit) → `1U << 31` avoids signed overflow

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
For each bit: count % 3 != 0 → the single number has that bit set
```

## Common Mistakes

❌ Using `1 << i` for `i = 31` → signed overflow (undefined behavior). Use `1U << i`.

❌ Trying to use XOR like Single Number I — XOR only works for "appears twice" logic, not three times.

---

## Related Problems

- 136. Single Number (appears twice → XOR all)
- 260. Single Number III (two singles → XOR + partition)
- 191. Number of 1 Bits

---

# 🧠 Revision Notes

## Pattern Recognition

| Appears | Trick |
|---------|-------|
| Twice (rest once) | XOR all → cancels pairs |
| Three times (rest once) | Bit count `% 3` per position |
| Twice — two singles | XOR all → XOR of two singles, then partition |

```
count % 3 != 0 → set that bit in answer
```
