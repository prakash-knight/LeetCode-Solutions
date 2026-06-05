# 162. Find Peak Element

[Link to LeetCode Problem](https://leetcode.com/problems/find-peak-element/)

---

## 📝 Problem Statement

A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array `nums`, find a peak element, and return its index. If the array contains multiple peaks, return the index to **any one** of the peaks.

You may imagine that `nums[-1] = nums[n] = -∞`.

You must write an algorithm that runs in `O(log n)` time.

### Example

```cpp
Input:
nums = [1,2,3,1]

Output:
2
```

Because:

```cpp
nums[2] = 3 is a peak element (3 > 2 and 3 > 1).
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Linear scan, check each element against its neighbors.

### Why is it inefficient?

```cpp
O(n)
```

time complexity — doesn't meet the `O(log n)` requirement.

---

## 2. Optimized Approach (Binary Search on Slope)

### Pattern Used

```cpp
Binary Search on Monotonicity / Slope
```

### Main Idea

Even though the array isn't globally sorted, binary search still works because:
- If `nums[mid] < nums[mid+1]`, we're on an **ascending slope** → a peak must exist to the **right**.
- If `nums[mid] >= nums[mid+1]`, we're on a **descending slope** (or at a peak) → a peak exists at `mid` or to the **left**.

The boundary condition `nums[-1] = nums[n] = -∞` guarantees a peak always exists.

---

## Step-by-Step Logic

1. Initialize:

```cpp
s = 0, e = nums.size() - 1
```

2. While `s < e` (note: strict less than, not `<=`):
   - Compute `mid = s + (e - s) / 2`.
   - If `nums[mid] < nums[mid+1]` → peak is to the right: `s = mid + 1`.
   - Else → peak is at `mid` or to the left: `e = mid`.

3. Return `s` (at this point `s == e`, both point to a peak).

---

### Why `s < e` instead of `s <= e`?

We're not searching for a specific target — we're narrowing down to a single index. When `s == e`, we've found our answer. Using `s <= e` with this logic would cause an infinite loop.

### Why `e = mid` instead of `e = mid - 1`?

Because `mid` itself could be the peak. We can't exclude it.

---

### Dry Run

```cpp
nums = [1, 2, 1, 3, 5, 6, 4]

Iteration 1: s=0, e=6, mid=3 → nums[3]=3 < nums[4]=5 → s=4
Iteration 2: s=4, e=6, mid=5 → nums[5]=6 > nums[6]=4 → e=5
Iteration 3: s=4, e=5, mid=4 → nums[4]=5 < nums[5]=6 → s=5
Loop ends: s=5=e → return 5 (nums[5]=6 is a peak) ✅
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
    int findPeakElement(vector<int>& nums) {
        int s = 0, e = nums.size() - 1;

        while (s < e) {
            int mid = s + (e - s) / 2;

            if (nums[mid] < nums[mid + 1])
                s = mid + 1;
            else
                e = mid;
        }

        return s;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single element

```cpp
nums = [1]
// Output: 0 (the only element is a peak by definition)
```

---

✅ Strictly increasing

```cpp
nums = [1, 2, 3, 4, 5]
// Output: 4 (last element is a peak since nums[5] = -∞)
```

---

✅ Strictly decreasing

```cpp
nums = [5, 4, 3, 2, 1]
// Output: 0 (first element is a peak since nums[-1] = -∞)
```

---

✅ Two elements

```cpp
nums = [1, 2]   // Output: 1
nums = [2, 1]   // Output: 0
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Binary search doesn't require a sorted array — it only requires a **decision criterion** that divides the search space. Here, the "slope" (ascending vs. descending) provides that criterion.

---

## Common Mistakes

❌ Using `s <= e`:

With this logic, `s <= e` causes an infinite loop when `s == e` because `mid = s` and `e = mid` doesn't change anything.

---

❌ Using `e = mid - 1`:

If `mid` is the peak, setting `e = mid - 1` would skip it.

---

## Related Problems

- 852 — Peak Index in a Mountain Array
- 1901 — Find a Peak Element II (2D version)
- 153 — Find Minimum in Rotated Sorted Array (similar binary search on non-sorted array)

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Find peak / maximum / turning point
- Binary search on unsorted array
- Decision based on neighbor comparison

Think:

```cpp
Binary Search on Slope — compare nums[mid] vs nums[mid+1]
```

---
