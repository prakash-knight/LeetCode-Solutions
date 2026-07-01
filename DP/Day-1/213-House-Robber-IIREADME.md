# 213. House Robber II

[Link to LeetCode Problem](https://leetcode.com/problems/house-robber-ii/)

---

## 📝 Problem Statement

All houses are arranged in a **circle**. That means the first and last houses are adjacent. Given an array `nums` representing the money at each house, return the maximum amount you can rob without robbing two adjacent houses.

### Example

```
Input:  nums = [2,3,2]
Output: 3

Can't rob house 0 and house 2 (they're adjacent in circle).
Best: rob house 1 → 3
```

---

# 💡 Intuition & Approach

## Two Passes of House Robber I

The circular constraint means house `0` and house `n-1` can't both be robbed. Break it into two linear subproblems:

1. **Pass 1**: Rob houses `[0, n-2]` (exclude last house).
2. **Pass 2**: Rob houses `[1, n-1]` (exclude first house).
3. Answer = `max(Pass 1, Pass 2)`.

Each pass is a standard House Robber I (take/skip DP).

```
nums = [2, 3, 2]
Pass 1 (houses 0-1): max(2, 3) = 3
Pass 2 (houses 1-2): max(3, 2) = 3
Answer = max(3, 3) = 3
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — two linear passes
```

## Space Complexity

```
O(N) — dp arrays
```

---

# 💻 Code

```cpp
class Solution {
public:
    int hepler(vector<int>& nums, int i, vector<int>& dp, int n) {
        if (i > n)
            return 0;
        if (dp[i] != -1)
            return dp[i];

        int take = nums[i] + hepler(nums, i + 2, dp, n);
        int ignore = hepler(nums, i + 1, dp, n);

        return dp[i] = max(take, ignore);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        if (n == 2)
            return max(nums[0], nums[1]);
        vector<int> dp(101, -1);
        int f = hepler(nums, 0, dp, n - 2);
        vector<int> cp(101, -1);
        int s = hepler(nums, 1, cp, n - 1);
        return max(f, s);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single house → rob it

✅ Two houses → rob the richer one

✅ All same values → alternating selection

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Circular array → break into two linear problems:
  1. [0, n-2] — include first, exclude last
  2. [1, n-1] — exclude first, include last
Answer = max of both.
```

## Common Mistakes

❌ Treating it as a simple linear robber → first/last adjacent constraint violated.

❌ Not handling n=1 and n=2 edge cases.

---

## Related Problems

- 198. House Robber (linear version)
- 337. House Robber III (tree version)
- 740. Delete and Earn

---

# 🧠 Revision Notes

## Pattern Recognition

Circular DP → decompose into two linear subproblems:

```
One including the first element (excluding last).
One excluding the first element (including last).
This pattern applies to any circular take/skip problem.
```
