# 540. Single Element in a Sorted Array

[Link to LeetCode Problem](https://leetcode.com/problems/single-element-in-a-sorted-array/)

---

## 📝 Problem Statement

You are given a sorted array consisting of only integers where every element appears **exactly twice**, except for one element which appears **exactly once**.

Return the single element that appears only once.

Your solution must run in **O(log n)** time and **O(1)** space.

### Example

```cpp
Input:  nums = [1,1,2,3,3,4,4,8,8]
Output: 2

Input:  nums = [3,3,7,7,11,12,12]
Output: 11
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

XOR all elements — the pairs cancel out and you're left with the single element.

```cpp
O(n) time, O(1) space — simple but doesn't leverage the sorted property.
```

---

## 2. Optimized Approach (Binary Search on Pair Boundaries)

### Pattern Used

```cpp
Binary Search — check if the single element is in the left or right half by counting parity
```

### Main Idea

In a sorted array with all pairs, before the single element the pairs start at **even indices** (0-indexed). After the single element, pairs start at **odd indices**.

Identify which half the single element is in by checking the parity of the distance from `s` to `mid`.

---

## Step-by-Step Logic

1. `s = 0`, `e = n - 1`
2. While `s < e`:
   - `mid = s + (e - s) / 2`
   - Ensure `mid` points to the **start** of a pair: if `nums[mid] == nums[mid-1]`, do `mid--`.
   - Check if `nums[mid]` is isolated (not equal to neighbors) → it's the single element, return it.
   - Count elements in left half: `left = mid - s`
   - If `left % 2 != 0` → odd count on left → single element is in `[s, mid-1]` → `e = mid - 1`
   - Else → single element is in `[mid+2, e]` → `s = mid + 2` (skip both of mid's pair)
3. Return `nums[s]`

---

### Dry Run

```cpp
nums = [1,1,2,3,3,4,4,8,8]  (n=9)

s=0, e=8, mid=4
  nums[4]=3, nums[3]=3 → equal, mid-- → mid=3
  nums[3]=3, nums[2]=2 (not equal), nums[4]=3 (equal) → not isolated
  left = 3 - 0 = 3 (odd) → e = mid-1 = 2

s=0, e=2, mid=1
  nums[1]=1, nums[0]=1 → equal, mid-- → mid=0
  nums[0]=1 not equal to nums[-1] (boundary), nums[1]=1 (equal) → not isolated
  left = 0 - 0 = 0 (even) → s = mid+2 = 2

s=2, e=2 → exit loop
return nums[2] = 2 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(log n)
```

Because:
- Binary search halves the search space each iteration.

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
    int singleNonDuplicate(vector<int>& nums) {
        int s = 0, e = nums.size() - 1;

        while (s < e) {
            int mid = s + (e - s) / 2;

            if (mid > 0 && nums[mid] == nums[mid - 1])
                mid--;

            int left = mid - s;
            int right = e - mid + 1;

            if ((mid == 0 || nums[mid] != nums[mid - 1]) &&
                (mid == nums.size() - 1 || nums[mid] != nums[mid + 1]))
                return nums[mid];

            if (left % 2 != 0)
                e = mid - 1;
            else
                s = mid + 2;
        }
        return nums[s];
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single element at start:

```cpp
nums = [1,2,2,3,3]
// Output: 1
```

---

✅ Single element at end:

```cpp
nums = [1,1,2,2,3]
// Output: 3
```

---

✅ Only one element:

```cpp
nums = [7]
// Output: 7
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

**Align `mid` to the start of its pair** (by decrementing if it matches its left neighbor), then use `left % 2` to determine which side the singleton is on.

Alternatively, a cleaner O(log n) approach:
- Always keep `mid` even (use `mid &= ~1` or `if (mid % 2 == 1) mid--`).
- Check if `nums[mid] == nums[mid+1]` → single is on the right → `s = mid + 2`.
- Else → single is on the left → `e = mid`.

---

## Common Mistakes

❌ Not handling the boundary check (`mid == 0` or `mid == n-1`) when checking neighbors.

❌ Using `s < e` instead of `s <= e` — needed because we return inside the loop for the isolated element case; `nums[s]` return handles the final convergence.

---

## Related Problems

- 136 — Single Number (XOR approach, unsorted)
- 137 — Single Number II

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Find the unique element in a sorted array where all others appear twice
- O(log n) required

Think:

```cpp
Binary Search — align mid to pair start, use parity of left count to decide direction
```

---
