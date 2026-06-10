# 1539. Kth Missing Positive Number

[Link to LeetCode Problem](https://leetcode.com/problems/kth-missing-positive-number/)

---

## 📝 Problem Statement

Given an array `arr` of positive integers sorted in strictly increasing order, and an integer `k`, return the `k`th **missing** positive integer.

### Example

```cpp
Input:  arr = [2,3,4,7,11], k = 5
Output: 9

// Missing: 1,5,6,8,9 → 5th missing = 9
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Iterate from 1 upwards, check if each number is in the array using a set, count missing numbers until you reach the kth one.

```cpp
O(n + kth missing value)
```

---

## 2. Optimized Approach (Binary Search)

### Pattern Used

```cpp
Binary Search — use the count of missing numbers up to arr[mid] as the search key
```

### Main Idea

At index `mid` (0-indexed), the value `arr[mid]` is at position `mid + 1` if no numbers were missing. The **count of missing numbers** up to `arr[mid]` is:

```cpp
missing_count = arr[mid] - (mid + 1)
```

- If `missing_count < k` → the kth missing is to the **right** of `mid`.
- If `missing_count >= k` → the kth missing is to the **left** of or at `mid`.

Binary search for the **largest index `s`** where `missing_count < k`. The answer is then `s + k`.

---

## Step-by-Step Logic

1. `s = 0`, `e = n - 1`.
2. Binary search: `mid = s + (e - s) / 2`.
3. `idx = arr[mid] - (mid + 1)` = missing count before `arr[mid]`.
4. If `idx < k` → `s = mid + 1`.
5. Else → `e = mid - 1`.
6. After loop: `ans = s + k`.

---

### Dry Run

```cpp
arr = [2,3,4,7,11], k = 5

s=0, e=4, mid=2: arr[2]=4, missing=4-3=1 < 5 → s=3
s=3, e=4, mid=3: arr[3]=7, missing=7-4=3 < 5 → s=4
s=4, e=4, mid=4: arr[4]=11, missing=11-5=6 >= 5 → e=3

exit: s=4 → ans = 4+5 = 9 ✅
```

```cpp
Verification:
Missing up to index 3 (arr[3]=7): 3 numbers missing (1,5,6)
After position 3, we need 5-3=2 more missing numbers after 7.
Sequence: 7(present), 8(missing-4th), 9(missing-5th) → ans=9 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(log n)
```

Because:
- Standard binary search.

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
    int findKthPositive(vector<int>& nums, int k) {
        int s = 0, e = nums.size() - 1;
        int ans = -1;

        while (s <= e) {
            int mid = s + (e - s) / 2;
            int idx = nums[mid] - (mid + 1);  // missing count up to nums[mid]

            if (idx < k)
                s = mid + 1;
            else
                e = mid - 1;
        }
        ans = s + k;
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ kth missing is before first array element:

```cpp
arr = [5,6,7], k = 3
// missing: 1,2,3,4 → 3rd missing = 3
// ans = s + k where s converges to 0 → 0+3=3 ✅
```

---

✅ kth missing is after last array element:

```cpp
arr = [1,2,3], k = 4
// all array elements present, s goes to n → s+k = 3+4 = 7 ✅
```

---

✅ No missing before k:

```cpp
arr = [1,2,3,4], k = 2
// s=4 → ans = 4+2 = 6 ✅ (5 and 6 are the 1st and 2nd missing)
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

The formula `ans = s + k` works because after the loop:
- `s` = first index where `arr[s] - (s+1) >= k` (or `n` if none found).
- There are `s` elements in the array to the left of position `s`.
- So the kth missing after those `s` elements lands at position `s + k`.

---

## Common Mistakes

❌ Initializing `ans = -1` without using it — the actual answer is always `s + k` after the loop, regardless of where the binary search ends.

---

## Related Problems

- 268 — Missing Number
- 448 — Find All Numbers Disappeared in an Array

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- kth missing in a sorted array
- O(log n) required

Think:

```cpp
Binary Search — missing count = arr[mid] - (mid+1)
Find largest index where missing count < k, then ans = s + k
```

---
