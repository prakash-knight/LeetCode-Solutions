# 283. Move Zeroes

[Link to LeetCode Problem](https://leetcode.com/problems/move-zeroes/)

---

## 1. 📝 Problem Statement

Given an integer array `nums`, move all `0`s to the **end** of the array while maintaining the **relative order** of the non-zero elements.

**Must be done in-place** without making a copy of the array.

### Example

```
Input:  nums = [0, 1, 0, 3, 12]
Output: [1, 3, 12, 0, 0]

Input:  nums = [0]
Output: [0]
```

### Constraints
- `1 <= nums.length <= 10⁴`
- `-2³¹ <= nums[i] <= 2³¹ - 1`

---

## 2. 💡 Intuition

### How should I think about this problem?

Don't think about "moving zeroes to the end." Instead, think about **bringing all non-zero elements to the front**. The zeroes will naturally end up at the back.

### Key Observations

1. **Focus on non-zeroes, not zeroes**: If you place all non-zero elements at the front in order, the remaining positions are just zeroes.

2. **Two-pointer (read-write)**: Same pattern as "Remove Duplicates" — one pointer writes, one reads.

3. **Preserve relative order**: We can't just swap any zero with any non-zero. The non-zero elements must keep their original relative order.

```
[0, 1, 0, 3, 12]
 i  j
 
j finds non-zero → swap with i → advance both
i always points to the leftmost zero (or next write position)
```

---

## 3. 🐢 Brute Force Approach

### Idea
Use a temporary array: collect all non-zeroes first, then fill the rest with zeroes.

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        vector<int> temp;
        for (int x : nums) {
            if (x != 0) temp.push_back(x);   // collect non-zeroes
        }
        int i = 0;
        for (int x : temp) {
            nums[i++] = x;                    // place non-zeroes at front
        }
        while (i < nums.size()) {
            nums[i++] = 0;                    // fill rest with zeroes
        }
    }
};
```

### Complexity
- **Time**: `O(n)` — Two passes.
- **Space**: `O(n)` — Extra array for non-zeroes.

### Why is it bad?
Uses O(n) extra space. Problem asks for in-place.

---

## 4. 🚀 Optimal Approach — Two Pointers (Swap)

### Logic (Step-by-Step)

1. **Initialize `i = 0`**: Write pointer — points to where the next non-zero should go.
2. **Scan with `j` from 0 to n-1**.
3. **If `nums[j] != 0`**:
   - Swap `nums[i]` and `nums[j]`.
   - Increment `i`.
4. After the loop, all non-zeroes are at the front, all zeroes are at the back.

### Why does it work?

- `i` always points to the **leftmost zero** (or the next available position for a non-zero).
- When `j` finds a non-zero, swapping it with `nums[i]` places it at the correct front position.
- Since `j >= i` always, the swap is safe.
- Relative order of non-zeroes is preserved because `j` scans left-to-right.

### 🔍 Dry Run

```
Input: nums = [0, 1, 0, 3, 12]

i=0, j=0: nums[0]=0 → skip
          [0, 1, 0, 3, 12]
           i

i=0, j=1: nums[1]=1 ≠ 0 → swap(nums[0], nums[1]), i=1
          [1, 0, 0, 3, 12]
              i

i=1, j=2: nums[2]=0 → skip
          [1, 0, 0, 3, 12]
              i

i=1, j=3: nums[3]=3 ≠ 0 → swap(nums[1], nums[3]), i=2
          [1, 3, 0, 0, 12]
                 i

i=2, j=4: nums[4]=12 ≠ 0 → swap(nums[2], nums[4]), i=3
          [1, 3, 12, 0, 0]
                    i

Output: [1, 3, 12, 0, 0] ✅
```

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();       // total elements
        int i = 0;                 // write pointer — next position for non-zero
        
        for (int j = 0; j < n; j++) {       // read pointer scans everything
            if (nums[j] != 0) {              // found a non-zero element
                swap(nums[i], nums[j]);      // place it at write position
                i++;                          // advance write pointer
            }
            // if nums[j] == 0, just skip — j moves, i stays
        }
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `n` | Size of the array |
| `i` | Write pointer — points to leftmost zero / next non-zero slot |
| `j` | Read pointer — scans every element |

### Why swap instead of just copy?

If we only copy `nums[i] = nums[j]`, we'd need a second pass to fill zeroes at the end. Swapping handles both in one pass — the zero moves to `j`'s old position (which is behind `i`, so it'll stay at the end).

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Two Pointers (Read-Write / Partitioning)**

This is the **partition** variant of two pointers:
- **Read pointer (`j`)**: Scans every element.
- **Write pointer (`i`)**: Only advances for valid (non-zero) elements.

### When to use:
- Move/separate elements based on a condition.
- Partition array into two groups in-place.
- "Remove element" type problems.

| Pattern | How it applies |
|---------|---------------|
| **Two Pointers (Slow-Fast)** | `i` is slow, `j` is fast |
| **In-place Operations** | No extra space, swap-based |
| **Array Partitioning** | Non-zeroes on left, zeroes on right |

> 🧠 **Mental Model**: "Bring the good elements to the front; the bad ones settle at the back automatically."

---

## 7. ⚠️ Common Mistakes

### ❌ Forgetting to swap (just assigning)
```cpp
// WRONG: doesn't clear old position
nums[i] = nums[j];
i++;
// Now you need a second pass to fill zeroes

// CORRECT: swap handles both sides
swap(nums[i], nums[j]);
```

### ❌ Starting j from i+1 instead of 0
```cpp
// WRONG: misses the case where i itself is non-zero
for (int j = i + 1; j < n; j++)
// CORRECT
for (int j = 0; j < n; j++)
```
Note: Starting `j` from 0 is fine because when `i == j`, swapping an element with itself is a no-op.

### ❌ Not preserving relative order
Using a "swap first and last zero/non-zero" approach may break order. Always scan left-to-right.

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "Can you minimize the number of operations?"
**Answer**: If element at `i` is already non-zero, we can skip the swap:
```cpp
if (i != j) swap(nums[i], nums[j]);
```

### Q2: "What if you need to move a specific value (not just zero)?"
**Answer**: Same approach — change condition to `if (nums[j] != val)`. This is LeetCode 27 (Remove Element).

### Q3: "What if you need to keep zeroes at the front?"
**Answer**: Scan from right to left instead. Or: move non-zeroes to the end.

### Q4: "Can you do it without swap?"
**Answer**: Yes — two passes. First pass: overwrite front with non-zeroes. Second pass: fill remaining with zeroes.
```cpp
int i = 0;
for (int j = 0; j < n; j++)
    if (nums[j] != 0) nums[i++] = nums[j];
while (i < n) nums[i++] = 0;
```

### Q5: "What is the minimum number of swaps needed?"
**Answer**: Equal to the number of non-zero elements that appear after a zero. Each such element needs exactly one swap.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Single pass through the array. Each element visited once.

### Space Complexity: `O(1)`
- Only two integer variables. In-place swaps.

---
