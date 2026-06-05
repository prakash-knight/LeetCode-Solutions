# 153. Find Minimum in Rotated Sorted Array

[Link to LeetCode Problem](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

---

## 📝 Problem Statement

Suppose an array of length `n` sorted in ascending order is rotated between `1` and `n` times. Given the sorted rotated array `nums` of **unique** elements, return the minimum element.

You must write an algorithm that runs in `O(log n)` time.

### Example

```cpp
Input:
nums = [3,4,5,1,2]

Output:
1
```

Because:

```cpp
Original sorted: [1,2,3,4,5] → rotated 3 times → [3,4,5,1,2]
Minimum is 1.
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Linear scan to find the minimum.

### Why is it inefficient?

```cpp
O(n)
```

time complexity — doesn't exploit the rotated sorted structure.

---

## 2. Optimized Approach (Binary Search — Compare with Right End)

### Pattern Used

```cpp
Binary Search — Shrink towards the Inflection Point
```

### Main Idea

The minimum element is at the **rotation point** (inflection). We use binary search comparing `nums[mid]` with `nums[e]`:

- If `nums[mid] > nums[e]` → the rotation point (minimum) is to the **right** of `mid`: `s = mid + 1`.
- If `nums[mid] <= nums[e]` → `mid` could be the minimum, or the minimum is to the **left**: `e = mid`.

This works because:
- In the rotated part, elements are **larger** than `nums[e]`.
- In the non-rotated part, elements are **smaller or equal** to `nums[e]`.

---

## Step-by-Step Logic

1. Initialize:

```cpp
s = 0, e = nums.size() - 1
```

2. While `s < e`:
   - Compute `mid = s + (e - s) / 2`.
   - If `nums[mid] > nums[e]` → minimum is in right half: `s = mid + 1`.
   - Else → minimum is at `mid` or in left half: `e = mid`.

3. Return `nums[s]`.

---

### Why compare with `nums[e]` and not `nums[s]`?

Comparing with `nums[s]` doesn't work for the no-rotation case:
```cpp
nums = [1, 2, 3] → nums[mid]=2 > nums[s]=1 → s = mid+1 (wrong!)
```
Comparing with `nums[e]` correctly handles both rotated and non-rotated arrays.

---

### Dry Run

```cpp
nums = [4, 5, 6, 7, 0, 1, 2]

Iteration 1: s=0, e=6, mid=3 → nums[3]=7 > nums[6]=2 → s=4
Iteration 2: s=4, e=6, mid=5 → nums[5]=1 ≤ nums[6]=2 → e=5
Iteration 3: s=4, e=5, mid=4 → nums[4]=0 ≤ nums[5]=1 → e=4
Loop ends: s=4=e → return nums[4]=0 ✅
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
    int findMin(vector<int>& nums) {
        int s = 0, e = nums.size() - 1;

        while (s < e) {
            int mid = s + (e - s) / 2;

            if (nums[mid] > nums[e]) {
                s = mid + 1;
            } else {
                e = mid;
            }
        }

        return nums[s];
    }
};
```

---

# 🔍 Edge Cases Handled

✅ No rotation

```cpp
nums = [1, 2, 3, 4, 5]
// Output: 1 (already sorted, minimum is first element)
```

---

✅ Full rotation (same as no rotation)

```cpp
nums = [1, 2, 3]  // rotated n times = original
// Output: 1
```

---

✅ Single element

```cpp
nums = [1]
// Output: 1
```

---

✅ Two elements

```cpp
nums = [2, 1]  // Output: 1
nums = [1, 2]  // Output: 1
```

---

✅ Minimum at the end

```cpp
nums = [2, 3, 4, 5, 1]
// Output: 1
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Compare `nums[mid]` with `nums[e]` (right endpoint), **not** `nums[s]`. This correctly distinguishes the rotated half (where min lives) from the sorted half.

---

## Common Mistakes

❌ Comparing with `nums[s]`:

Fails for non-rotated arrays where `nums[mid] > nums[s]` but the min is still at `s`.

---

❌ Using `s <= e`:

When `s == e`, we've found the minimum. Using `<=` causes an infinite loop since `e = mid` doesn't shrink the interval.

---

❌ Using `e = mid - 1`:

If `mid` is the minimum, we'd skip it. Use `e = mid` to keep `mid` as a candidate.

---

## Related Problems

- 154 — Find Minimum in Rotated Sorted Array II (with duplicates)
- 33 — Search in Rotated Sorted Array
- 162 — Find Peak Element

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Find min/max in rotated sorted array
- Find rotation point / inflection point

Think:

```cpp
Binary Search — compare nums[mid] with nums[e]
// nums[mid] > nums[e] → min is on the right
// nums[mid] ≤ nums[e] → min is on the left (or at mid)
```

---
