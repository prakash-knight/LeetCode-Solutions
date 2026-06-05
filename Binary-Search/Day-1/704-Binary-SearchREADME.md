# 704. Binary Search

[Link to LeetCode Problem](https://leetcode.com/problems/binary-search/)

---

## 📝 Problem Statement

Given an array of integers `nums` which is sorted in ascending order, and an integer `target`, write a function to search `target` in `nums`. If `target` exists, return its index. Otherwise, return `-1`.

You must write an algorithm with `O(log n)` runtime complexity.

### Example

```cpp
Input:
nums = [-1,0,3,5,9,12], target = 9

Output:
4
```

Because:

```cpp
9 exists in nums at index 4.
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Linear scan through the array.

### Why is it inefficient?

```cpp
O(n)
```

time complexity — doesn't take advantage of the sorted property.

---

## 2. Optimized Approach (Classic Binary Search)

### Pattern Used

```cpp
Binary Search — Standard Template
```

### Main Idea

Since the array is sorted, we can eliminate half the search space at each step:
1. Compute the middle index.
2. If `nums[mid] == target`, return `mid`.
3. If `nums[mid] < target`, search the right half.
4. If `nums[mid] > target`, search the left half.

---

## Step-by-Step Logic

1. Initialize two pointers:

```cpp
s = 0, e = nums.size() - 1
```

2. While `s <= e`:
   - Compute `mid = s + (e - s) / 2` (avoids integer overflow).
   - If `nums[mid] == t`, return `mid`.
   - If `nums[mid] < t`, move `s = mid + 1`.
   - If `nums[mid] > t`, move `e = mid - 1`.

3. If loop ends, return `-1` (target not found).

---

### Dry Run

```cpp
nums = [-1, 0, 3, 5, 9, 12], target = 9

Iteration 1: s=0, e=5, mid=2 → nums[2]=3 < 9 → s=3
Iteration 2: s=3, e=5, mid=4 → nums[4]=9 == 9 → return 4 ✅
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
- Only a few variables used, no extra data structures.

---

# 💻 Code

```cpp
class Solution {
public:
    int search(vector<int>& nums, int t) {
        int s = 0, e = nums.size() - 1;

        while (s <= e) {
            int mid = s + (e - s) / 2;
            if (nums[mid] == t) return mid;
            else if (nums[mid] < t) s = mid + 1;
            else e = mid - 1;
        }

        return -1;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Target not in array

```cpp
nums = [-1, 0, 3, 5, 9, 12], target = 2
// Output: -1
```

---

✅ Single element (found)

```cpp
nums = [5], target = 5
// Output: 0
```

---

✅ Single element (not found)

```cpp
nums = [5], target = 3
// Output: -1
```

---

✅ Target at boundaries

```cpp
nums = [1, 2, 3, 4, 5], target = 1  // Output: 0 (first element)
nums = [1, 2, 3, 4, 5], target = 5  // Output: 4 (last element)
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Use `mid = s + (e - s) / 2` instead of `(s + e) / 2` to avoid integer overflow when `s + e` exceeds `INT_MAX`.

---

## Common Mistakes

❌ Using `s < e` instead of `s <= e`:

With `s < e`, the case where `s == e` is skipped. This means the single remaining element is never checked — the target could be missed.

---

❌ Infinite loop with wrong pointer update:

Setting `s = mid` or `e = mid` (without ±1) can cause infinite loops when `s == mid`.

---

## Related Problems

- 35 — Search Insert Position
- 34 — Find First and Last Position
- 33 — Search in Rotated Sorted Array
- 153 — Find Minimum in Rotated Sorted Array

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Search in a sorted array
- O(log n) required
- Find exact match in sorted data

Think:

```cpp
Classic Binary Search — s <= e, mid = s + (e-s)/2
```

---
