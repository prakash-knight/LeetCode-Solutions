# 1752. Check if Array Is Sorted and Rotated

[Link to LeetCode Problem](https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/)

---

## 1. 📝 Problem Statement

Given an array `nums`, return `true` if the array was originally sorted in **non-decreasing order** and then **rotated** some number of positions (including zero).

In simple words: Can this array be turned into a sorted array by rotating it?

### Example

```
Input:  nums = [3, 4, 5, 1, 2]
Output: true
Explanation: Sorted = [1, 2, 3, 4, 5], rotated 3 times → [3, 4, 5, 1, 2]

Input:  nums = [2, 1, 3, 4]
Output: false
Explanation: No rotation of a sorted array can produce [2, 1, 3, 4]

Input:  nums = [1, 2, 3]
Output: true
Explanation: Already sorted (rotated 0 times)
```

### Constraints
- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

---

## 2. 💡 Intuition

### How should I think about this problem?

A sorted-and-rotated array has a very specific structure:
- It's **sorted**, then at most **one "break point"** where the value drops.
- After the break, the values are sorted again, and the last element must be ≤ the first element (to "wrap around").

### Key Observations

1. **Count the "breaks"**: A "break" is where `nums[i] > nums[i+1]`. In a sorted-rotated array, there can be **at most 1 break**.

2. **Wrap-around check**: If there is a break, the array must also satisfy `nums[n-1] <= nums[0]` (the end wraps back to the beginning).

3. **Combine**: Count breaks (including the wrap-around from last to first). If total breaks ≤ 1, it's a valid sorted-rotated array.

```
[3, 4, 5, 1, 2]   → break at 5→1 (1 break)
                   → wrap: nums[4]=2 <= nums[0]=3 ✅
                   → Valid!

[2, 1, 3, 4]      → break at 2→1 (1 break)
                   → wrap: nums[3]=4 > nums[0]=2 (another break!)
                   → 2 breaks → Invalid!
```

---

## 3. 🐢 Brute Force Approach

### Idea
Try all `n` possible rotations. For each rotation, check if the result is sorted.

```cpp
class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        
        for (int r = 0; r < n; r++) {          // try each rotation
            bool sorted = true;
            for (int i = 0; i < n - 1; i++) {
                int idx = (i + r) % n;
                int nextIdx = (i + r + 1) % n;
                if (nums[idx] > nums[nextIdx]) {
                    sorted = false;
                    break;
                }
            }
            if (sorted) return true;
        }
        return false;
    }
};
```

### Complexity
- **Time**: `O(n²)` — n rotations × n checks each.
- **Space**: `O(1)`.

### Why is it bad?
Unnecessarily checks all rotations when we can detect the answer in one pass.

---

## 4. 🚀 Optimal Approach — Count Breaks

### Logic (Step-by-Step)

1. **Initialize `breakCount = 0`**.
2. **Iterate i from 0 to n-1**:
   - Compare `nums[i]` with `nums[(i+1) % n]` (using modulo to wrap around).
   - If `nums[i] > nums[(i+1) % n]` → increment `breakCount`.
3. **Return `breakCount <= 1`**.

### Why does it work?

A sorted array has **0 breaks**. A sorted-then-rotated array has **exactly 1 break** (the rotation point). The `% n` handles the wrap-around comparison between the last and first elements.

If there are **2 or more breaks**, no rotation of a sorted array can produce this — it's inherently unsorted.

### 🔍 Dry Run

```
Input: nums = [3, 4, 5, 1, 2]     n = 5

i=0: nums[0]=3 vs nums[1]=4 → 3 ≤ 4 → no break
i=1: nums[1]=4 vs nums[2]=5 → 4 ≤ 5 → no break
i=2: nums[2]=5 vs nums[3]=1 → 5 > 1 → breakCount = 1
i=3: nums[3]=1 vs nums[4]=2 → 1 ≤ 2 → no break
i=4: nums[4]=2 vs nums[0]=3 → 2 ≤ 3 → no break  (wrap-around via % n)

breakCount = 1 ≤ 1 → return true ✅
```

```
Input: nums = [2, 1, 3, 4]     n = 4

i=0: nums[0]=2 vs nums[1]=1 → 2 > 1 → breakCount = 1
i=1: nums[1]=1 vs nums[2]=3 → 1 ≤ 3 → no break
i=2: nums[2]=3 vs nums[3]=4 → 3 ≤ 4 → no break
i=3: nums[3]=4 vs nums[0]=2 → 4 > 2 → breakCount = 2

breakCount = 2 > 1 → return false ✅
```

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();          // total elements
        int breakCount = 0;           // number of "drops" in the array
        
        for (int i = 0; i < n; i++) {
            // compare current with next (wrap around using % n)
            if (nums[i] > nums[(i + 1) % n]) {
                breakCount++;          // found a break point
            }
        }
        
        return breakCount <= 1;       // at most 1 break = valid rotation
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `n` | Size of the array |
| `breakCount` | Number of positions where `nums[i] > nums[i+1]` (including wrap-around) |
| `i` | Loop index |
| `(i+1) % n` | Next index with wrap-around (last element compares with first) |

### Why `% n`?

When `i = n-1` (last element), `(i+1) % n = 0`. This compares the last element with the first — checking if the array "wraps around" correctly.

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Array Observation / Counting Inversions**

This is a **property-checking** pattern where you look for structural violations.

### When to use:
- "Is this array a rotation of a sorted array?"
- "Is this a valid permutation/arrangement?"
- Checking array invariants in one pass.

| Pattern | How it applies |
|---------|---------------|
| **Array Manipulation** | Circular comparison using modulo |
| **Counting / Observation** | Count breaks to detect structure |
| **Circular Array** | `% n` for wrap-around logic |

> 🧠 **Mental Model**: "A sorted-rotated array is a circle with at most one 'step down'. Count the step-downs."

---

## 7. ⚠️ Common Mistakes

### ❌ Forgetting the wrap-around check
```cpp
// WRONG: only checks adjacent pairs, misses last→first
for (int i = 0; i < n - 1; i++) {
    if (nums[i] > nums[i + 1]) breakCount++;
}
// This would say [2, 1] is valid (1 break) but miss that [4, 5, 1, 2, 6] is invalid

// CORRECT: include wrap-around
for (int i = 0; i < n; i++) {
    if (nums[i] > nums[(i + 1) % n]) breakCount++;
}
```

### ❌ Using `>=` instead of `>`
```cpp
// WRONG: [1, 1, 1] would count breaks for equal elements
if (nums[i] >= nums[(i + 1) % n])

// CORRECT: only count strict decreases
if (nums[i] > nums[(i + 1) % n])
```
Duplicates are allowed (non-decreasing order).

### ❌ Special-casing arrays of size 1 or 2
The general solution handles them correctly — no need for special cases.

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "Find the rotation count (the index of the minimum element)?"
**Answer**: The break point is the rotation index. When `nums[i] > nums[i+1]`, then `i+1` is the minimum element's index (= rotation count).

### Q2: "How would you search in a sorted-rotated array?" (LeetCode 33)
**Answer**: Use **modified binary search**. Determine which half is sorted, then decide which half to search.

### Q3: "What if there are duplicates?" (LeetCode 81)
**Answer**: Binary search becomes harder — worst case O(n) because duplicates make it impossible to determine the sorted half.

### Q4: "Find the minimum in a rotated sorted array?" (LeetCode 153)
**Answer**: Binary search — compare `mid` with `right`. If `nums[mid] > nums[right]`, min is in the right half.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Single pass through the array. Each element checked once.

### Space Complexity: `O(1)`
- Only one integer variable (`breakCount`).

---
