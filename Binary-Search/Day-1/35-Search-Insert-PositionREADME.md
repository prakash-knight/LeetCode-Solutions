# 35. Search Insert Position

[Link to LeetCode Problem](https://leetcode.com/problems/search-insert-position/)

---

## 📝 Problem Statement

Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be inserted in order.

You must write an algorithm with `O(log n)` runtime complexity.

### Example

```cpp
Input:
nums = [1,3,5,6], target = 5

Output:
2
```

```cpp
Input:
nums = [1,3,5,6], target = 2

Output:
1
```

Because:

```cpp
2 would be inserted at index 1 to keep the array sorted: [1, 2, 3, 5, 6]
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Linear scan to find the first element ≥ target.

### Why is it inefficient?

```cpp
O(n)
```

time complexity — doesn't exploit the sorted property.

---

## 2. Optimized Approach (Binary Search — Lower Bound)

### Pattern Used

```cpp
Binary Search — Lower Bound / Insert Position
```

### Main Idea

This is essentially finding the **lower bound** — the first position where `target` can be placed. The key insight is:
- If the target is found, return that index.
- If the loop ends without finding the target, `s` will point to the correct insert position.

Why does `s` give the correct insert position?
- When `nums[mid] < t`, we move `s = mid + 1`, meaning `s` always skips past elements smaller than target.
- When `nums[mid] > t`, we move `e = mid - 1`, meaning `e` moves before elements larger than target.
- When the loop ends (`s > e`), `s` is exactly at the first position where an element ≥ target should be.

---

## Step-by-Step Logic

1. Initialize:

```cpp
s = 0, e = nums.size() - 1
```

2. While `s <= e`:
   - Compute `mid = s + (e - s) / 2`.
   - If `nums[mid] == t`, return `mid`.
   - If `nums[mid] < t`, move `s = mid + 1`.
   - If `nums[mid] > t`, move `e = mid - 1`.

3. Return `s` — the correct insert position.

---

### Dry Run

```cpp
nums = [1, 3, 5, 6], target = 2

Iteration 1: s=0, e=3, mid=1 → nums[1]=3 > 2 → e=0
Iteration 2: s=0, e=0, mid=0 → nums[0]=1 < 2 → s=1
Loop ends: s=1 > e=0 → return s=1 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(log n)
```

Because:
- Standard binary search, halving the search space each iteration.

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
    int searchInsert(vector<int>& nums, int t) {
        int s = 0, e = nums.size() - 1;

        while (s <= e) {
            int mid = s + (e - s) / 2;

            if (nums[mid] == t) return mid;
            else if (nums[mid] < t) s = mid + 1;
            else e = mid - 1;
        }
        return s;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Target smaller than all elements

```cpp
nums = [3, 5, 7], target = 1
// Output: 0 (insert at beginning)
```

---

✅ Target larger than all elements

```cpp
nums = [1, 3, 5], target = 7
// Output: 3 (insert at end)
```

---

✅ Target exists in array

```cpp
nums = [1, 3, 5, 6], target = 5
// Output: 2
```

---

✅ Single element array

```cpp
nums = [1], target = 0  // Output: 0
nums = [1], target = 2  // Output: 1
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

The only difference from standard binary search (LC 704) is the return value: instead of returning `-1` when the target is not found, we return `s` — the left pointer — which naturally lands at the correct insertion index.

---

## Common Mistakes

❌ Returning `e` instead of `s`:

After the loop, `s = e + 1`. The insert position is `s` (first element ≥ target), not `e` (last element < target).

---

❌ Confusing with `lower_bound` vs `upper_bound`:

This problem is equivalent to `lower_bound` — find the first position where the element ≥ target.

---

## Related Problems

- 704 — Binary Search (exact match)
- 34 — Find First and Last Position (two-sided lower/upper bound)
- 278 — First Bad Version

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Insert position in sorted array
- First index where element ≥ target
- Lower bound search

Think:

```cpp
Binary Search — return s (left pointer) when not found
```

---
