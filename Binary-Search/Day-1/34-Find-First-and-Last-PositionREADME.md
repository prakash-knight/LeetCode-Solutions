# 34. Find First and Last Position of Element in Sorted Array

[Link to LeetCode Problem](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

---

## 📝 Problem Statement

Given an array of integers `nums` sorted in non-decreasing order, find the starting and ending position of a given `target` value.

If `target` is not found in the array, return `[-1, -1]`.

You must write an algorithm with `O(log n)` runtime complexity.

### Example

```cpp
Input:
nums = [5,7,7,8,8,10], target = 8

Output:
[3,4]
```

Because:

```cpp
8 first appears at index 3 and last appears at index 4.
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Linear scan to find first and last occurrence.

### Why is it inefficient?

```cpp
O(n)
```

time complexity in the worst case (all elements are the target).

---

## 2. Approach Used (Binary Search + Linear Expansion)

### Pattern Used

```cpp
Binary Search + Linear Scan from Match Point
```

### Main Idea

1. Use binary search to find **any** occurrence of the target.
2. Once found, expand **left** to find the first occurrence and **right** to find the last occurrence.

This is a hybrid approach — the binary search gives us `O(log n)` to find the target, then we linearly scan outward.

---

## Step-by-Step Logic

1. Standard binary search to find `mid` where `nums[mid] == target`.

2. If found:
   - Set `x = mid`, scan left: while `x >= 0 && nums[x] == nums[mid]`, decrement `x`.
   - Set `y = mid`, scan right: while `y < n && nums[y] == nums[mid]`, increment `y`.
   - Return `{x+1, y-1}` (since `x` and `y` go one step beyond).

3. If not found, return `{-1, -1}`.

---

### Dry Run

```cpp
nums = [5, 7, 7, 8, 8, 10], target = 8

Binary search finds mid=3 (nums[3]=8)
Expand left:  x=3→2 (nums[2]=7, stop) → x=2
Expand right: y=3→4→5 (nums[5]=10, stop) → y=5
Return: {2+1, 5-1} = {3, 4} ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(log n + k)   where k = count of target elements
```

Because:
- Binary search takes `O(log n)`.
- Linear expansion takes `O(k)` where `k` is the number of duplicates.
- Worst case (all elements same): `O(n)`.

> **Note:** A pure `O(log n)` solution would run two separate binary searches — one for the leftmost and one for the rightmost occurrence. This approach trades worst-case guarantee for simpler code.

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
    vector<int> searchRange(vector<int>& nums, int t) {
        int s = 0, e = nums.size() - 1;
        int x = -1, y = -1;

        while (s <= e) {
            int mid = s + (e - s) / 2;

            if (nums[mid] == t) {
                x = mid;
                y = mid;
                while (x >= 0 && nums[x] == nums[mid]) x--;
                while (y < nums.size() && nums[y] == nums[mid]) y++;

                return {x + 1, y - 1};
            }
            else if (nums[mid] < t) s = mid + 1;
            else e = mid - 1;
        }
        return {x, y};
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Target not in array

```cpp
nums = [5, 7, 7, 8, 8, 10], target = 6
// Output: [-1, -1]
```

---

✅ Single occurrence

```cpp
nums = [1, 2, 3, 4, 5], target = 3
// Output: [2, 2]
```

---

✅ All elements are target

```cpp
nums = [8, 8, 8, 8], target = 8
// Output: [0, 3]
```

---

✅ Empty array

```cpp
nums = [], target = 0
// Output: [-1, -1]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Find any match via binary search, then linearly expand to find boundaries. Simple and effective, though not strictly `O(log n)` in the worst case.

---

## Common Mistakes

❌ Off-by-one in expansion:

The `while` loops go one step past the boundary, so the answer is `{x+1, y-1}`, not `{x, y}`.

---

❌ Boundary check missing in expansion:

Must check `x >= 0` and `y < nums.size()` to avoid out-of-bounds access.

---

## Alternative: Pure O(log n) Approach

Run two separate binary searches:
- **Left bound:** When `nums[mid] == target`, set `e = mid - 1` to keep searching left.
- **Right bound:** When `nums[mid] == target`, set `s = mid + 1` to keep searching right.

---

## Related Problems

- 704 — Binary Search
- 35 — Search Insert Position
- 2089 — Find Target Indices After Sorting

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Find range/boundaries of a value in sorted array
- First and last occurrence

Think:

```cpp
Binary Search + Expand from Match Point
// Or: Two Binary Searches (left bound + right bound) for strict O(log n)
```

---
