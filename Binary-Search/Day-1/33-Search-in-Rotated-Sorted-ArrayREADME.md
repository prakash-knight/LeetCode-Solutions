# 33. Search in Rotated Sorted Array

[Link to LeetCode Problem](https://leetcode.com/problems/search-in-rotated-sorted-array/)

---

## 📝 Problem Statement

There is an integer array `nums` sorted in ascending order (with **distinct** values). Prior to being passed to your function, `nums` is possibly rotated at an unknown pivot.

Given the array `nums` after the possible rotation and an integer `target`, return the index of `target` if it is in `nums`, or `-1` if it is not.

You must write an algorithm with `O(log n)` runtime complexity.

### Example

```cpp
Input:
nums = [4,5,6,7,0,1,2], target = 0

Output:
4
```

Because:

```cpp
0 exists at index 4 in the rotated array.
// Original sorted: [0,1,2,4,5,6,7] → rotated at pivot index 4
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Linear scan.

### Why is it inefficient?

```cpp
O(n)
```

time complexity — doesn't use the partially sorted property.

---

## 2. Optimized Approach (Modified Binary Search)

### Pattern Used

```cpp
Binary Search — Identify Sorted Half
```

### Main Idea

In a rotated sorted array, at any `mid`, **one half is always sorted**:
- If `nums[s] <= nums[mid]` → the **left half** `[s..mid]` is sorted.
- Otherwise → the **right half** `[mid..e]` is sorted.

Once we identify the sorted half, we check if `target` lies within that sorted range:
- If yes → search that half.
- If no → search the other half.

---

## Step-by-Step Logic

1. Initialize: `s = 0, e = nums.size() - 1`.

2. While `s <= e`:
   - Compute `mid = s + (e - s) / 2`.
   - If `nums[mid] == target`, return `mid`.
   - **Left half is sorted** (`nums[s] <= nums[mid]`):
     - If `nums[s] <= target < nums[mid]` → target is in left half: `e = mid - 1`.
     - Else → search right half: `s = mid + 1`.
   - **Right half is sorted**:
     - If `nums[mid] < target <= nums[e]` → target is in right half: `s = mid + 1`.
     - Else → search left half: `e = mid - 1`.

3. Return `-1`.

---

### Dry Run

```cpp
nums = [4, 5, 6, 7, 0, 1, 2], target = 0

Iteration 1: s=0, e=6, mid=3 → nums[3]=7 ≠ 0
  Left sorted: nums[0]=4 <= nums[3]=7
  Is 4 <= 0 < 7? No → s = 4

Iteration 2: s=4, e=6, mid=5 → nums[5]=1 ≠ 0
  Left sorted? nums[4]=0 <= nums[5]=1 → Yes
  Is 0 <= 0 < 1? Yes → e = 4

Iteration 3: s=4, e=4, mid=4 → nums[4]=0 == 0 → return 4 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(log n)
```

Because:
- Each iteration halves the search space.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only a few variables used.

---

# 💻 Code

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int s = 0, e = nums.size() - 1;

        while (s <= e) {
            int mid = s + (e - s) / 2;

            if (nums[mid] == target)
                return mid;

            if (nums[s] <= nums[mid]) {
                if (nums[s] <= target && target < nums[mid])
                    e = mid - 1;
                else
                    s = mid + 1;
            }

            else {
                if (nums[mid] < target && target <= nums[e])
                    s = mid + 1;
                else
                    e = mid - 1;
            }
        }

        return -1;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ No rotation (already sorted)

```cpp
nums = [1, 2, 3, 4, 5], target = 3
// Output: 2
```

---

✅ Rotated by 1

```cpp
nums = [5, 1, 2, 3, 4], target = 5
// Output: 0
```

---

✅ Target not in array

```cpp
nums = [4, 5, 6, 7, 0, 1, 2], target = 3
// Output: -1
```

---

✅ Single element

```cpp
nums = [1], target = 1  // Output: 0
nums = [1], target = 0  // Output: -1
```

---

✅ Two elements

```cpp
nums = [3, 1], target = 1  // Output: 1
nums = [1, 3], target = 3  // Output: 1
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

At any `mid` in a rotated sorted array, **one half is guaranteed to be sorted**. Identify it using `nums[s] <= nums[mid]`, then check if the target falls within that sorted range.

---

## Common Mistakes

❌ Using `nums[s] < nums[mid]` instead of `nums[s] <= nums[mid]`:

When `s == mid` (only 2 elements left), `nums[s] == nums[mid]`. Using strict `<` would incorrectly classify the left half as unsorted.

---

❌ Wrong boundary comparisons:

- Left sorted check: `nums[s] <= target` AND `target < nums[mid]` (strict `<` for mid since we already checked `nums[mid] != target`).
- Right sorted check: `nums[mid] < target` AND `target <= nums[e]`.

---

## Related Problems

- 81 — Search in Rotated Sorted Array II (with duplicates)
- 153 — Find Minimum in Rotated Sorted Array
- 154 — Find Minimum in Rotated Sorted Array II

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Search in a rotated sorted array
- Binary search with partial ordering

Think:

```cpp
Identify Sorted Half → Check if target is in sorted range → Narrow search space
```

---
