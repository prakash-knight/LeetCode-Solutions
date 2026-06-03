# 26. Remove Duplicates from Sorted Array

[Link to LeetCode Problem](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)

---

## 1. 📝 Problem Statement

Given a **sorted** integer array `nums` (non-decreasing order), remove the duplicates **in-place** so each unique element appears only **once**.

Return `k` — the number of unique elements. The first `k` elements of `nums` should hold the unique values in order.

### Example

```
Input:  nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
Output: k = 5, nums = [0, 1, 2, 3, 4, _, _, _, _, _]
```

### Constraints
- `1 <= nums.length <= 3 × 10⁴`
- `-100 <= nums[i] <= 100`
- `nums` is sorted in non-decreasing order.

---

## 2. 💡 Intuition

### How should I think about this problem?

Since the array is **sorted**, all duplicates are **adjacent**. You never have `[1, 3, 1]`.

### Key Observations

1. **Sorted = duplicates are neighbors**: They always cluster like `[1, 1, 1, 2, 2, 3]`.
2. **Two-pointer technique**: Use a **write pointer** (`i`) to track where the next unique element should go, and a **read pointer** (`j`) to scan every element.
3. **Overwrite strategy**: When `nums[j] != nums[i]`, we found a new unique value → write it at `i+1`.

```
nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
        i  j
j scans forward. When nums[j] ≠ nums[i]:
    → increment i
    → copy nums[j] to nums[i]
```

---

## 3. 🐢 Brute Force Approach

### Idea
Use a set to collect unique elements, then copy them back.

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        set<int> unique(nums.begin(), nums.end());
        int i = 0;
        for (int val : unique) {
            nums[i++] = val;
        }
        return unique.size();
    }
};
```

### Complexity
- **Time**: `O(n log n)` — set insertion is O(log n).
- **Space**: `O(n)` — extra set.

### Why is it bad?
Uses extra space (problem requires in-place) and has unnecessary overhead.

---

## 4. 🚀 Optimal Approach — Two Pointers

### Logic (Step-by-Step)

1. **Initialize `i = 0`**: Points to the last placed unique element.
2. **Scan with `j` from index 1 to n-1**.
3. **Compare `nums[j]` with `nums[i]`**:
   - **Different** → found new unique: `i++`, then `nums[i] = nums[j]`.
   - **Same** → skip (duplicate).
4. **Return `i + 1`**.

### Why does it work?

- `i` always points to the last placed unique element.
- Since the array is sorted, `nums[j] != nums[i]` means `nums[j]` is the **next** unique value.
- We overwrite duplicates in-place.

### 🔍 Dry Run

```
Input: nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
                i

j=1: nums[1]=0 == nums[0]=0  → skip
j=2: nums[2]=1 != nums[0]=0  → i=1, nums[1]=1
     [0, 1, 1, 1, 1, 2, 2, 3, 3, 4]
         i
j=3: nums[3]=1 == nums[1]=1  → skip
j=4: nums[4]=1 == nums[1]=1  → skip
j=5: nums[5]=2 != nums[1]=1  → i=2, nums[2]=2
     [0, 1, 2, 1, 1, 2, 2, 3, 3, 4]
            i
j=6: skip
j=7: nums[7]=3 != nums[2]=2  → i=3, nums[3]=3
     [0, 1, 2, 3, 1, 2, 2, 3, 3, 4]
               i
j=8: skip
j=9: nums[9]=4 != nums[3]=3  → i=4, nums[4]=4
     [0, 1, 2, 3, 4, 2, 2, 3, 3, 4]
                  i

Return i + 1 = 5 ✅
```

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();       // total number of elements
        
        if (n == 0) return 0;      // edge case: empty array
        
        int i = 0;                 // write pointer — last unique position
        
        for (int j = 1; j < n; j++) {      // read pointer scans from 1 to end
            if (nums[j] != nums[i]) {       // found a new unique element
                i++;                         // advance write position
                nums[i] = nums[j];          // place the unique element
            }
            // if equal → j moves forward, i stays (skip duplicate)
        }
        
        return i + 1;             // count = 0-based index + 1
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `n` | Size of the array |
| `i` | Write pointer — index of last placed unique element |
| `j` | Read pointer — scans every element |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Two Pointers (Read-Write / Slow-Fast)**

- **Read pointer (`j`)**: Scans every element.
- **Write pointer (`i`)**: Only advances when a valid element is found.

### When to use:
- Remove elements in-place from a sorted/unsorted array.
- Filter elements based on a condition.
- Deduplicate while preserving order.

| Pattern | How it applies |
|---------|---------------|
| **Two Pointers (Slow-Fast)** | `i` moves slowly, `j` moves fast |
| **In-place Operations** | No extra array; overwrite in position |

> 🧠 **Mental Model**: "Two pointers diverge: one reads everything, the other writes only the keepers."

---

## 7. ⚠️ Common Mistakes

### ❌ Starting j from 0 instead of 1
```cpp
// WRONG: comparing nums[0] with nums[0] — always equal!
for (int j = 0; j < n; j++)
// CORRECT
for (int j = 1; j < n; j++)
```

### ❌ Forgetting to return i + 1
```cpp
// WRONG: returns index, not count
return i;
// CORRECT
return i + 1;
```

### ❌ Not handling empty array
```cpp
// WRONG: accessing nums[0] when empty → crash
// CORRECT: guard first
if (n == 0) return 0;
```

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "What if duplicates can appear at most twice?" (LeetCode 80)
**Answer**: Compare with `nums[i-1]` instead:
```cpp
int i = 1;
for (int j = 2; j < n; j++) {
    if (nums[j] != nums[i - 1]) { i++; nums[i] = nums[j]; }
}
```

### Q2: "What if the array is NOT sorted?"
**Answer**: Use a hash set to track seen elements, or sort first.

### Q3: "Extend this to remove a specific value?" (LeetCode 27)
**Answer**: Same pattern, different condition: `if (nums[j] != val)`.

### Q4: "What if you used erase() in a loop?"
**Answer**: O(n²) — `vector::erase` shifts all subsequent elements each time.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Single pass. Each element visited exactly once.

### Space Complexity: `O(1)`
- Only two integer variables (`i`, `j`). In-place.

---
