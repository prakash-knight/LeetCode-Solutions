# 88. Merge Sorted Array

[Link to LeetCode Problem](https://leetcode.com/problems/merge-sorted-array/)

---

## 📝 Problem Statement

You are given two integer arrays `nums1` and `nums2`, sorted in **non-decreasing order**, and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.

Merge `nums2` into `nums1` as one sorted array, **in-place**.

`nums1` has a length of `m + n` — the last `n` slots are `0` and should be ignored.

### Example

```cpp
Input:  nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
```

---

# 💡 Intuition & Approach

## 1. Approach (In-Place Insertion)

### Pattern Used

```cpp
Two pointers — scan and insert nums2 elements into nums1 in-place
```

### Main Idea

Use two pointers `s1` and `s2` scanning `nums1` and `nums2`. When `nums1[s1] >= nums2[s2]`, shift all elements in `nums1` from `s1` to end one position right to make room, then insert `nums2[s2]` at `s1`.

After the scan, any remaining elements in `nums2` are appended to `nums1`.

---

## Step-by-Step Logic

1. `s1 = 0`, `s2 = 0`
2. While `s1 < nums1.size()` and `s2 < n`:
   - If `nums1[s1] >= nums2[s2]`: shift `nums1[s1..end]` right by 1, insert `nums2[s2]`, advance both pointers.
   - Else: advance `s1`.
3. Append remaining `nums2` elements to `nums1[m..]`.

---

### Dry Run

```cpp
nums1 = [1,2,3,0,0,0], m=3, nums2 = [2,5,6], n=3

s1=0,s2=0: nums1[0]=1 < nums2[0]=2 → s1++
s1=1,s2=0: nums1[1]=2 >= nums2[0]=2 → shift, insert 2
  nums1 = [1,2,2,3,0,0], s1=2, s2=1
s1=2,s2=1: nums1[2]=2 < 5 → s1++
s1=3,s2=1: nums1[3]=3 < 5 → s1++
s1=4,s2=1: nums1[4]=0 < 5? No (0<5 yes) → s1++
s1=5,s2=1: nums1[5]=0 < 5 → s1++
s1=6: exit while loop
Append: nums1[4]=5, nums1[5]=6
nums1 = [1,2,2,3,5,6] ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(m * n)  — worst case due to shifts
```

> **Note**: An optimal O(m+n) approach uses three pointers from the end (fill from the back of nums1). Consider this as an upgrade.

---

## Space Complexity

```cpp
O(1)
```

Because:
- All operations are in-place.

---

# 💻 Code

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int s1 = 0, s2 = 0;

        while (s1 < nums1.size() && s2 < n) {
            if (nums1[s1] >= nums2[s2]) {
                int j = nums1.size() - 1;
                while (j != s1) {
                    nums1[j] = nums1[j - 1];
                    j--;
                }
                nums1[s1] = nums2[s2];
                m++;
                s1++;
                s2++;
            } else
                s1++;
        }

        while (s2 < n) {
            nums1[m] = nums2[s2];
            s2++;
            m++;
        }
    }
};
```

---

# 🔍 Edge Cases Handled

✅ `nums2` is empty:

```cpp
nums1 = [1], m=1, nums2 = [], n=0
// Output: [1]
```

---

✅ `nums1` has no real elements:

```cpp
nums1 = [0], m=0, nums2 = [1], n=1
// Output: [1]
```

---

✅ All of `nums2` is smaller:

```cpp
nums1 = [4,5,6,0,0,0], m=3, nums2 = [1,2,3], n=3
// Output: [1,2,3,4,5,6]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

**Optimal approach (O(m+n))**: Fill from the **back** of `nums1`. Compare `nums1[m-1]` and `nums2[n-1]`, placing the larger at `nums1[m+n-1]`. No shifting needed.

---

## Common Mistakes

❌ Forgetting to append remaining `nums2` elements after the main loop ends.

❌ Not accounting for the padded `0`s at the end of `nums1` — the real size is `m`, total allocated size is `m+n`.

---

## Related Problems

- 21 — Merge Two Sorted Lists
- 23 — Merge k Sorted Lists

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Merge two sorted arrays in-place
- One array has extra space at the end

Think:

```cpp
Three pointers from the back — fill from position (m+n-1) downward
```

---
