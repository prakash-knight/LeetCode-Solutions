# 81. Search in Rotated Sorted Array II

[Link to LeetCode Problem](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)

---

## 📝 Problem Statement

There is an integer array `nums` sorted in non-decreasing order (with **duplicate values**). The array was possibly rotated at an unknown pivot.

Given the array `nums` (after rotation) and a target value `tar`, return `true` if `tar` is in `nums`, or `false` if it is not.

### Example

```cpp
Input:  nums = [2,5,6,0,0,1,2], target = 0
Output: true

Input:  nums = [2,5,6,0,0,1,2], target = 3
Output: false
```

---

# 💡 Intuition & Approach

## 1. Linear Search

Simply scan the array — O(n). Doesn't use the sorted+rotated property.

---

## 2. Optimized Approach (Modified Binary Search)

### Pattern Used

```cpp
Binary Search on rotated array with duplicate handling
```

### Main Idea

Standard binary search on a rotated sorted array (LC 33) breaks when duplicates are present at `nums[s] == nums[mid] == nums[e]` — we can't determine which half is sorted.

**Handle duplicates**: when `nums[s] == nums[mid] == nums[e]`, simply do `s++; e--` (shrink both ends by 1) and continue.

Otherwise, use the standard rotated-binary-search logic.

---

## Step-by-Step Logic

1. `s = 0`, `e = n - 1`
2. While `s <= e`:
   - `mid = s + (e - s) / 2`
   - If `nums[mid] == tar` → return `true`
   - **Ambiguous case**: `nums[s] == nums[mid] == nums[e]` → `s++; e--`
   - **Left half sorted** (`nums[s] <= nums[mid]`):
     - If `nums[s] <= tar < nums[mid]` → `e = mid - 1`
     - Else → `s = mid + 1`
   - **Right half sorted**:
     - If `nums[mid] < tar <= nums[e]` → `s = mid + 1`
     - Else → `e = mid - 1`
3. Return `false`

---

### Dry Run

```cpp
nums = [2,5,6,0,0,1,2], target = 0

s=0, e=6, mid=3: nums[3]=0 == tar ✅ return true
```

```cpp
nums = [1,1,1,0,1], target = 0

s=0, e=4, mid=2: nums[2]=1, nums[0]=1, nums[4]=1 → ambiguous → s=1, e=3
s=1, e=3, mid=2: nums[2]=1, nums[1]=1, nums[3]=0 → not ambiguous
  nums[s]=1 <= nums[mid]=1 → left sorted
  tar=0 not in [1,1) → s = mid+1 = 3
s=3, e=3, mid=3: nums[3]=0 == tar ✅ return true
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n) worst case (all duplicates)
O(log n) average case
```

Because:
- In the worst case (all same elements), `s++; e--` each iteration → O(n).

---

## Space Complexity

```cpp
O(1)
```

---

# 💻 Code

```cpp
class Solution {
public:
    bool search(vector<int>& nums, int tar) {
        int s = 0, e = nums.size() - 1;

        while (s <= e) {
            int mid = s + (e - s) / 2;

            if (nums[mid] == tar) return true;

            if (nums[s] == nums[mid] && nums[mid] == nums[e]) {
                s++;
                e--;
            } else if (nums[s] <= nums[mid]) {
                if (nums[s] <= tar && nums[mid] > tar)
                    e = mid - 1;
                else
                    s = mid + 1;
            } else {
                if (nums[e] >= tar && nums[mid] < tar)
                    s = mid + 1;
                else
                    e = mid - 1;
            }
        }
        return false;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ All duplicates (worst case):

```cpp
nums = [1,1,1,1,1], target = 2
// O(n) scan, returns false
```

---

✅ Target at boundaries:

```cpp
nums = [3,1,1], target = 3
// Output: true
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

The **ambiguous case** (`nums[s] == nums[mid] == nums[e]`) is the only difference from LC 33. Handle it by shrinking both boundaries: `s++; e--`.

---

## Common Mistakes

❌ Forgetting the ambiguous case — causes incorrect half-selection when duplicates exist at boundaries.

❌ Using strict `<` instead of `<=` in range checks for sorted half.

---

## Related Problems

- 33 — Search in Rotated Sorted Array (no duplicates)
- 153 — Find Minimum in Rotated Sorted Array
- 154 — Find Minimum in Rotated Sorted Array II

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Search in a rotated sorted array WITH duplicates

Think:

```cpp
Binary Search + handle ambiguous case (s++, e--) when boundaries equal mid
```

---
