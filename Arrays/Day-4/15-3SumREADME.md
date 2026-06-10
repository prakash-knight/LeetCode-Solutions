# 15. 3Sum

[Link to LeetCode Problem](https://leetcode.com/problems/3sum/)

---

## 📝 Problem Statement

Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that:
- `i != j`, `i != k`, `j != k`
- `nums[i] + nums[j] + nums[k] == 0`

The solution set must **not contain duplicate triplets**.

### Example

```cpp
Input:  nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Three nested loops, check all triplets, store in a set to avoid duplicates.

### Why is it inefficient?

```cpp
O(n³)
```

Too slow for large inputs.

---

## 2. Optimized Approach (Sort + Two Pointers)

### Pattern Used

```cpp
Fix one element → Two-pointer search on the remaining sorted subarray
```

### Main Idea

Sort the array. Fix index `i`, then use two pointers `s = i+1` and `e = n-1` to find pairs that sum to `-nums[i]`. Skip duplicates at each level.

---

## Step-by-Step Logic

1. Sort `nums`.
2. For each `i` from 0 to n-1:
   - Skip if `nums[i] == nums[i-1]` (duplicate outer element).
   - Set `s = i+1`, `e = n-1`.
   - While `s < e`:
     - If `sum == 0`: record triplet, advance both pointers, skip duplicate `s` and `e`.
     - If `sum < 0`: `s++`
     - If `sum > 0`: `e--`

---

### Dry Run

```cpp
nums = [-4,-1,-1,0,1,2]  (sorted)

i=0 (nums[0]=-4): s=1, e=5
  sum=-4+(-1)+2=-3 < 0 → s++
  sum=-4+(-1)+2=-3 < 0 → s++
  sum=-4+0+2=-2 < 0 → s++
  sum=-4+1+2=-1 < 0 → s++
  s >= e, break

i=1 (nums[1]=-1): s=2, e=5
  sum=-1+(-1)+2=0 → [-1,-1,2] ✅, s++, e--
  s=3, e=4: sum=-1+0+1=0 → [-1,0,1] ✅, s++, e--
  s >= e, break

i=2 (nums[2]=-1): skip (dup of -1)
...
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n²)
```

Because:
- Sorting: O(n log n)
- For each of n elements, two-pointer scan is O(n).

---

## Space Complexity

```cpp
O(1)  (excluding output)
```

Because:
- Only pointers used; sorting is in-place.

---

# 💻 Code

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int s = i + 1, e = n - 1;
            while (s < e) {
                int sum = nums[i] + nums[s] + nums[e];
                if (sum == 0) {
                    ans.push_back({nums[i], nums[s], nums[e]});
                    s++;
                    e--;
                    while (s < e && nums[s] == nums[s - 1]) s++;
                    while (s < e && nums[e] == nums[e + 1]) e--;
                } else if (sum < 0)
                    s++;
                else
                    e--;
            }
        }
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ No valid triplet:

```cpp
nums = [1, 2, 3]
// Output: []
```

---

✅ Multiple duplicates:

```cpp
nums = [0, 0, 0, 0]
// Output: [[0, 0, 0]]  — only one triplet
```

---

✅ All same elements:

```cpp
nums = [-2, -2, -2, -2]
// Output: []
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

**Sorting enables duplicate skipping at both the outer loop and inner two-pointer levels**, without needing a set.

---

## Common Mistakes

❌ Forgetting to skip duplicates for the inner pointers after finding a valid triplet — leads to duplicate triplets in output.

❌ Starting duplicate check with `i > 0` — without this guard, accessing `nums[i-1]` at `i=0` is out of bounds.

---

## Related Problems

- 1 — Two Sum
- 18 — 4Sum
- 16 — 3Sum Closest

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Find triplets/pairs summing to a target
- No duplicate combinations in result
- O(n²) expected

Think:

```cpp
Sort + Fix one → Two-pointer on rest + Skip duplicates at all levels
```

---
