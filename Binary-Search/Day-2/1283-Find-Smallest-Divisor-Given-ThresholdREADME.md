# 1283. Find the Smallest Divisor Given a Threshold

[Link to LeetCode Problem](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/)

---

## 📝 Problem Statement

Given an array of integers `nums` and an integer `threshold`, choose a **positive integer divisor**, divide all the array by it, and sum the division results (ceiling division). Find the **smallest** such divisor such that the result of dividing and summing is less than or equal to `threshold`.

### Example

```cpp
Input:  nums = [1,2,5,9], threshold = 6
Output: 5

// With divisor=5: ceil(1/5)+ceil(2/5)+ceil(5/5)+ceil(9/5) = 1+1+1+2 = 5 ≤ 6 ✅
// With divisor=4: ceil(1/4)+ceil(2/4)+ceil(5/4)+ceil(9/4) = 1+1+2+3 = 7 > 6 ❌
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Try every divisor from 1 to max(nums), compute the sum, return the first that satisfies the threshold.

### Why is it inefficient?

```cpp
O(n * max(nums))
```

---

## 2. Optimized Approach (Binary Search on Answer)

### Pattern Used

```cpp
Binary Search on the answer space (divisor range)
```

### Main Idea

As the divisor increases, the sum decreases (monotone). Binary search on divisor range `[1, max(nums)]`.

- If `solve(mid) ≤ threshold` → `mid` is a candidate; try smaller (go left).
- If `solve(mid) > threshold` → too large a sum; need bigger divisor (go right).

### Ceiling Division Trick

```cpp
ceil(x / d) = (x % d == 0) ? x/d : x/d + 1
```

---

## Step-by-Step Logic

1. Sort `nums` to find max easily: `e = nums[n-1]`.
2. Binary search `s = 1`, `e = max(nums)`, `ans = 0`.
3. Compute `mid`, call `solve(nums, mid)`.
4. If sum ≤ threshold → `ans = mid`, `e = mid - 1` (try smaller).
5. Else → `s = mid + 1`.

---

### Dry Run

```cpp
nums = [1,2,5,9], threshold = 6
s=1, e=9

mid=5: solve=1+1+1+2=5 ≤ 6 → ans=5, e=4
mid=2: solve=1+1+3+5=10 > 6 → s=3
mid=3: solve=1+1+2+3=7 > 6 → s=4
mid=4: solve=1+1+2+3=7 > 6 → s=5 > e=4, exit

ans = 5 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n log(max(nums)))
```

Because:
- Binary search over `max(nums)` values, each check is O(n).

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
    int solve(vector<int>& nums, int th) {
        int n = 0;
        for (auto x : nums) {
            if (x % th == 0)
                n += (x / th);
            else
                n += ((x / th) + 1);
        }
        return n;
    }

    int smallestDivisor(vector<int>& nums, int th) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int s = 1, e = nums[n - 1];
        int ans = 0;

        while (s <= e) {
            int mid = s + (e - s) / 2;
            int tar = solve(nums, mid);

            if (tar <= th) {
                ans = mid;
                e = mid - 1;
            } else
                s = mid + 1;
        }
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Threshold equals array size (each element rounds up to 1):

```cpp
// Divisor = max(nums) ensures each element divides to at most 1
```

---

✅ Single element:

```cpp
nums = [1], threshold = 1
// Output: 1
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

**Binary Search on Answer**: the answer lies in `[1, max(nums)]` and the sum function is **monotonically decreasing** with divisor — perfect for binary search.

---

## Common Mistakes

❌ Using floor division instead of ceiling: `x/d` ≠ `ceil(x/d)` — use the mod check pattern.

❌ Not sorting to find `max` — or using `*max_element(nums.begin(), nums.end())` directly without sorting.

---

## Related Problems

- 875 — Koko Eating Bananas
- 1011 — Capacity to Ship Packages
- 410 — Split Array Largest Sum

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Find minimum/maximum value satisfying a condition
- Condition is monotone over the value range
- Involves ceiling/floor division with a variable divisor

Think:

```cpp
Binary Search on Answer — define feasibility check, search over value range
```

---
