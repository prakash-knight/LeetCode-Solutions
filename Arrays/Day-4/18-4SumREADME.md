# 18. 4Sum

[Link to LeetCode Problem](https://leetcode.com/problems/4sum/)

---

## 📝 Problem Statement

Given an array `nums` of `n` integers and an integer `target`, return all **unique quadruplets** `[nums[a], nums[b], nums[c], nums[d]]` such that:

- `a`, `b`, `c`, `d` are all distinct indices.
- `nums[a] + nums[b] + nums[c] + nums[d] == target`

### Example

```cpp
Input:  nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Four nested loops — O(n⁴). Check all quadruplets, use a set for deduplication.

---

## 2. Optimized Approach (Sort + Fix Two + Two Pointers)

### Pattern Used

```cpp
Extension of 3Sum — fix two elements, then two-pointer on the remaining
```

### Main Idea

Sort the array. Fix indices `i` and `j`, then use two pointers `s = j+1` and `e = n-1` to find pairs summing to `target - nums[i] - nums[j]`.

> ⚠️ Use `long long` for intermediate sums to avoid integer overflow when numbers are large.

---

## Step-by-Step Logic

1. Sort `nums`.
2. For `i` from 0 to n-1 (skip dup: `i > 0 && nums[i] == nums[i-1]`):
3. For `j` from i+1 to n-1 (skip dup: `j > i+1 && nums[j] == nums[j-1]`):
4. Set `s = j+1`, `e = n-1`, `tar = (long long)target - nums[i] - nums[j]`.
5. Two-pointer: if `nums[s]+nums[e] == tar`, record, advance both, skip dups.

---

### Dry Run

```cpp
nums = [-2,-1,0,0,1,2], target = 0  (sorted)

i=0 (-2), j=1 (-1): tar = 0-(-2)-(-1) = 3
  s=2,e=5: 0+2=2<3 → s++
  s=3,e=5: 0+2=2<3 → s++
  s=4,e=5: 1+2=3 ✅ → [-2,-1,1,2], s++, e--; s>=e break

i=0 (-2), j=2 (0): tar = 0-(-2)-0 = 2
  s=3,e=5: 0+2=2 ✅ → [-2,0,0,2], s++, e--; s>=e break

i=1 (-1), j=2 (0): tar = 0-(-1)-0 = 1
  s=3,e=5: 0+2=2>1 → e--
  s=3,e=4: 0+1=1 ✅ → [-1,0,0,1], s++, e--; s>=e break
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n³)
```

Because:
- Two nested loops O(n²), two-pointer O(n) each.

---

## Space Complexity

```cpp
O(1)  (excluding output)
```

---

# 💻 Code

```cpp
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int s = j + 1, e = n - 1;
                long long tar = (long long)target - (nums[i] + nums[j]);

                while (s < e) {
                    long long sum = (long long)nums[s] + nums[e];
                    if (sum == tar) {
                        ans.push_back({nums[i], nums[j], nums[s], nums[e]});
                        s++;
                        e--;
                        while (s < e && nums[s] == nums[s - 1]) s++;
                        while (s < e && nums[e] == nums[e + 1]) e--;
                    } else if (sum > tar)
                        e--;
                    else
                        s++;
                }
            }
        }
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Fewer than 4 elements:

```cpp
nums = [1, 2, 3]
// Output: []
```

---

✅ Overflow prevention:

```cpp
nums = [1000000000, 1000000000, 1000000000, 1000000000], target = -294967296
// Uses long long to avoid overflow in sum computation
```

---

✅ All same elements:

```cpp
nums = [0, 0, 0, 0], target = 0
// Output: [[0, 0, 0, 0]]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Cast to `long long` before computing `target - nums[i] - nums[j]` — the intermediate value can overflow `int` even if individual elements are within int range.

---

## Common Mistakes

❌ Using `int` for `tar` — overflows for constraints up to 10⁹.

❌ Duplicate skip for `j`: condition must be `j > i+1` (not `j > 0`) to allow `nums[j]` to equal `nums[i]` when needed.

---

## Related Problems

- 15 — 3Sum
- 1 — Two Sum
- 16 — 3Sum Closest

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- k-Sum (k ≥ 3) with unique combinations
- Large value constraints (potential overflow)

Think:

```cpp
Sort + (k-2) fixed loops with duplicate skipping + Two-pointer innermost
Use long long for intermediate sums
```

---
