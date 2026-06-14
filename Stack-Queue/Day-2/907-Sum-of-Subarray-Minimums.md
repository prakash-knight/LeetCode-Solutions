# 907. Sum of Subarray Minimums

[Link to LeetCode Problem](https://leetcode.com/problems/sum-of-subarray-minimums/)

---

## 1. 📝 Problem Statement

Given an array of integers `arr`, find the **sum of min(b)** over every (contiguous) subarray `b` of `arr`. Return the answer modulo `10⁹ + 7`.

### Example

```
Input:  arr = [3,1,2,4]
Output: 17

Explanation:
Subarrays: [3]=3, [1]=1, [2]=2, [4]=4
           [3,1]=1, [1,2]=1, [2,4]=2
           [3,1,2]=1, [1,2,4]=1
           [3,1,2,4]=1
Sum = 3+1+2+4+1+1+2+1+1+1 = 17
```

### Constraints
- `1 <= arr.length <= 3 × 10⁴`
- `1 <= arr[i] <= 3 × 10⁴`

---

## 2. 💡 Intuition

### How should I think about this problem?

Instead of iterating over all subarrays (O(n²) or O(n³)), think about the **contribution of each element** as a minimum.

### Key Insight: Contribution Technique

For each element `arr[i]`, count **how many subarrays have `arr[i]` as their minimum**. Multiply by `arr[i]` and sum all contributions.

### How to count subarrays where `arr[i]` is minimum?

For `arr[i]` to be the minimum of a subarray `[l, r]`:
- The subarray must include index `i`.
- All elements to the left of `i` (within the subarray) must be `≥ arr[i]`.
- All elements to the right of `i` (within the subarray) must be `> arr[i]` (strict, to avoid double counting).

Define:
- `left[i]` = index of the **previous smaller element** (strictly smaller). Use `-1` if none.
- `right[i]` = index of the **next smaller or equal element**. Use `n` if none.

Then:
- Number of valid left endpoints: `i - left[i]`
- Number of valid right endpoints: `right[i] - i`
- **Contribution** of `arr[i]` = `arr[i] × (i - left[i]) × (right[i] - i)`

> **Why strict vs non-strict?** To avoid double-counting when equal elements exist. If `arr[j] == arr[i]`, only one of them should be counted as the minimum — use `>` on one side and `≥` on the other.

### Visualization

```
arr = [3, 1, 2, 4]
       0  1  2  3

For i=1 (arr[1]=1):
  left[1] = -1   (no smaller element to the left)
  right[1] = 4   (no smaller/equal element to the right)

  Contribution = 1 × (1-(-1)) × (4-1) = 1 × 2 × 3 = 6
  → 1 is the min of 6 subarrays: [1],[1,2],[1,2,4],[3,1],[3,1,2],[3,1,2,4] ✅
```

---

## 3. 🐢 Brute Force Approach

Generate all subarrays, find the minimum of each, sum them up.

```cpp
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        long long ans = 0;
        const int MOD = 1e9 + 7;
        for (int i = 0; i < n; i++) {
            int mn = arr[i];
            for (int j = i; j < n; j++) {
                mn = min(mn, arr[j]);
                ans = (ans + mn) % MOD;
            }
        }
        return ans;
    }
};
```

- **Time**: `O(n²)`
- **Space**: `O(1)`

---

## 4. 🚀 Optimal Approach — Contribution Technique + Monotonic Stack

### Logic (Step-by-Step)

**Step 1**: Compute `minl[i]` = index of previous strictly smaller element (or -1).
- Traverse left to right with a monotonic **increasing** stack.
- Pop while `nums[top] >= nums[i]`, then `minl[i] = top` (or -1 if empty).

**Step 2**: Compute `minr[i]` = index of next smaller-or-equal element (or n).
- Traverse right to left with a monotonic **increasing** stack.
- Pop while `nums[top] > nums[i]` (strict, for dedup), then `minr[i] = top` (or n if empty).

**Step 3**: For each `i`:
```
contribution = arr[i] * (i - minl[i]) * (minr[i] - i)
ans = (ans + contribution) % MOD
```

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    int sumSubarrayMins(vector<int>& nums) {
        int n = nums.size();
        vector<int> minl(n);
        vector<int> minr(n);
        stack<int> st1;
        stack<int> st2;

        // Previous strictly smaller element
        for (int i = 0; i < n; i++) {
            while (!st1.empty() && nums[st1.top()] > nums[i]) {
                st1.pop();
            }
            if (st1.empty()) minl[i] = -1;
            else minl[i] = st1.top();
            st1.push(i);
        }

        // Next smaller or equal element
        for (int i = n - 1; i >= 0; i--) {
            while (!st2.empty() && nums[st2.top()] >= nums[i]) {
                st2.pop();
            }
            if (st2.empty()) minr[i] = n;
            else minr[i] = st2.top();
            st2.push(i);
        }

        long long ans = 0;
        const int MOD = 1e9 + 7;
        for (int i = 0; i < n; i++) {
            long long left = i - minl[i];
            long long right = minr[i] - i;
            ans = (ans + nums[i] * left % MOD * right) % MOD;
        }
        return ans;
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `minl[i]` | Index of previous strictly smaller element for `i` |
| `minr[i]` | Index of next smaller-or-equal element for `i` |
| `st1, st2` | Monotonic stacks for left and right boundary computation |
| `left, right` | Count of valid left/right endpoints for `arr[i]` as minimum |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Contribution Technique + Monotonic Stack**

### When to use:
- "Sum of subarray minimums/maximums."
- Any problem asking you to compute aggregate over all subarrays involving min/max.

| Pattern | How it applies |
|---------|---------------|
| **Contribution Technique** | Count how many subarrays each element dominates |
| **Monotonic Stack** | Efficiently find prev/next smaller boundaries |
| **Deduplication trick** | Use `>` vs `>=` on left vs right to avoid double-counting |

> 🧠 **Mental Model**: "Don't iterate subarrays. Ask: for each element, in how many subarrays is it the minimum? The answer is the product of its reach left × reach right."

---

## 7. ⚠️ Common Mistakes

### ❌ Using same comparison on both sides (double counting)
If two equal elements exist, using `>=` on both sides counts the same subarray twice. Use `>` (strict) on one side and `>=` on the other.

### ❌ Forgetting modulo during intermediate multiplication
```cpp
// WRONG: overflow
ans += nums[i] * left * right;

// CORRECT: apply MOD at each step
ans = (ans + (long long)nums[i] * left % MOD * right) % MOD;
```

### ❌ Using wrong boundary defaults
- `minl[i] = -1` when no previous smaller exists (not 0!).
- `minr[i] = n` when no next smaller exists (not n-1!).

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "Can you extend this to Sum of Subarray Maximums?"
**Answer**: Yes — find previous greater and next greater elements instead.

### Q2: "What about Sum of Subarray Ranges (max - min)?" (LeetCode 2104)
**Answer**: Compute sum of maxes and sum of mins separately, subtract.

### Q3: "Why does the contribution technique work?"
**Answer**: Every subarray has exactly one minimum. We partition all subarrays by their minimum. Summing contributions over all elements covers each subarray exactly once.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Three passes: left boundary, right boundary, contribution sum.
- Each element pushed/popped at most once from each stack.

### Space Complexity: `O(n)`
- `minl[]`, `minr[]` arrays and two stacks.
