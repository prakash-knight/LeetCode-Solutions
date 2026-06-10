# 31. Next Permutation

[Link to LeetCode Problem](https://leetcode.com/problems/next-permutation/)

---

## 📝 Problem Statement

A **permutation** of an array of integers is an arrangement of its members into a sequence or linear order.

Given an array of integers `nums`, find the **next permutation** of `nums`.

The replacement must be **in place** and use only constant extra memory.

### Example

```cpp
Input:  nums = [1, 2, 3]
Output: [1, 3, 2]

Input:  nums = [3, 2, 1]
Output: [1, 2, 3]  // wraps around to smallest permutation
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Generate all permutations, sort them, and find the next one.

### Why is it inefficient?

```cpp
O(n! * n)
```

Too slow for large `n`.

---

## 2. Optimized Approach (3-Step Algorithm)

### Pattern Used

```cpp
Find breakpoint → swap with next greater → reverse suffix
```

### Main Idea

To find the next permutation:
1. Find the rightmost index `idx` where `nums[idx] < nums[idx+1]` — this is the **breakpoint**.
2. If no breakpoint exists, the array is the **largest permutation** — just reverse the whole thing.
3. Otherwise, find the rightmost element greater than `nums[idx]` and swap them.
4. Reverse the suffix starting at `idx + 1`.

---

## Step-by-Step Logic

1. Traverse from right to left to find `idx` where `nums[idx] < nums[idx+1]`.
2. If `idx == -1`, reverse the entire array and return.
3. Traverse from right to find the first element greater than `nums[idx]`; swap them.
4. Reverse `nums[idx+1 .. n-1]`.

---

### Dry Run

```cpp
nums = [1, 3, 5, 4, 2]

Step 1: Find breakpoint → nums[1]=3 < nums[2]=5 → idx=1
         (but continue scanning right for a later breakpoint)
         nums[2]=5 > nums[3]=4, nums[3]=4 > nums[4]=2 → idx=1 ✅

Step 2: Find rightmost > nums[1]=3 → nums[3]=4 → swap
        nums = [1, 4, 5, 3, 2]

Step 3: Reverse suffix after idx=1 → reverse [5, 3, 2] → [2, 3, 5]
        nums = [1, 4, 2, 3, 5] ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Each of the 3 steps (scan, swap, reverse) is O(n).

---

## Space Complexity

```cpp
O(1)
```

Because:
- In-place modifications only.

---

# 💻 Code

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int idx = -1;

        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        for (int i = n - 1; i > idx; i--) {
            if (nums[i] > nums[idx]) {
                swap(nums[i], nums[idx]);
                break;
            }
        }

        reverse(nums.begin() + idx + 1, nums.end());
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Largest permutation (descending order):

```cpp
nums = [3, 2, 1]
// Output: [1, 2, 3]  → full reverse
```

---

✅ Single element:

```cpp
nums = [1]
// Output: [1]
```

---

✅ Already the next permutation is just a swap:

```cpp
nums = [1, 2]
// Output: [2, 1]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

The **suffix after the breakpoint** is always in **descending order**. That's why a simple reverse (not a full sort) converts it to ascending — the next smallest arrangement.

---

## Common Mistakes

❌ Scanning from left instead of right for the breakpoint — you want the **rightmost** dip.

❌ Forgetting the full reverse when `idx == -1` (the array is the largest permutation).

---

## Related Problems

- 46 — Permutations
- 47 — Permutations II
- 60 — Permutation Sequence

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Next/previous permutation in lexicographic order
- In-place rearrangement to get the next sequence

Think:

```cpp
Find breakpoint (nums[i] < nums[i+1]) → swap with next-greater → reverse suffix
```

---
