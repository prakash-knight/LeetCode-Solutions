# 2149. Rearrange Array Elements by Sign

[Link to LeetCode Problem](https://leetcode.com/problems/rearrange-array-elements-by-sign/)

---

## 📝 Problem Statement

You are given a **0-indexed** integer array `nums` of **even** length consisting of an **equal** number of positive and negative integers.

Return the array after rearranging such that:
- Every **consecutive pair** of integers has **opposite signs**.
- Positive integers are at **even indices**, and negative integers are at **odd indices**.
- The **relative order** of positives and negatives is preserved.

### Example

```cpp
Input:  nums = [3,1,-2,-5,2,-4]
Output: [3,-2,1,-5,2,-4]
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Separate positives and negatives into two arrays, then interleave them.

### Why it works but is slightly verbose?

```cpp
O(n) time, O(n) space
```

Requires two extra arrays.

---

## 2. Optimized Approach (Two-Pointer Placement)

### Pattern Used

```cpp
Two separate index pointers for even (positive) and odd (negative) positions
```

### Main Idea

Use two pointers `j = 0` (next even index for positives) and `k = 1` (next odd index for negatives). Iterate through `nums` once and place each element directly into its correct position in the answer array.

---

## Step-by-Step Logic

1. Create `ans` of size `n`, initialized to 0.
2. Initialize `j = 0` (even slots) and `k = 1` (odd slots).
3. For each element in `nums`:
   - If positive → `ans[j] = nums[i]`, then `j += 2`.
   - If negative → `ans[k] = nums[i]`, then `k += 2`.
4. Return `ans`.

---

### Dry Run

```cpp
nums = [3, 1, -2, -5, 2, -4]

i=0: nums[0]=3  → ans[0]=3,  j=2
i=1: nums[1]=1  → ans[2]=1,  j=4
i=2: nums[2]=-2 → ans[1]=-2, k=3
i=3: nums[3]=-5 → ans[3]=-5, k=5
i=4: nums[4]=2  → ans[4]=2,  j=6
i=5: nums[5]=-4 → ans[5]=-4, k=7

ans = [3, -2, 1, -5, 2, -4] ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Single pass through the array.

---

## Space Complexity

```cpp
O(n)
```

Because:
- Output array `ans` of size `n`.

---

# 💻 Code

```cpp
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 0);
        int j = 0, k = 1;

        for (int i = 0; i < n; i++) {
            if (nums[i] < 0) {
                ans[k] = nums[i];
                k += 2;
            } else {
                ans[j] = nums[i];
                j += 2;
            }
        }
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ All positives before all negatives in input:

```cpp
nums = [1, 2, -1, -2]
// Output: [1, -1, 2, -2]
```

---

✅ Alternating input already:

```cpp
nums = [1, -1, 2, -2]
// Output: [1, -1, 2, -2]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Use **two separate index pointers** (`j` for even, `k` for odd) and directly place each element — no sorting or extra passes needed.

---

## Common Mistakes

❌ Forgetting that the problem guarantees **equal counts** of positives and negatives — otherwise `j` and `k` could go out of bounds.

---

## Related Problems

- 905 — Sort Array By Parity
- 75 — Sort Colors

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Place elements at specific even/odd indices
- Interleave two groups while preserving order

Think:

```cpp
Two index pointers — one for even slots, one for odd slots
```

---
