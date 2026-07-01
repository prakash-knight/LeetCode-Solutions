# 198. House Robber

[Link to LeetCode Problem](https://leetcode.com/problems/house-robber/)

---

## 📝 Problem Statement

You are a robber planning to rob houses along a street. Each house has a certain amount of money. Adjacent houses have connected security systems — if two adjacent houses are broken into on the same night, the police are alerted.

Given an array `nums` representing the money at each house, return the maximum amount you can rob **without alerting the police**.

### Example

```
Input:  nums = [2,7,9,3,1]
Output: 12

Rob houses 0, 2, 4: 2 + 9 + 1 = 12
```

---

# 💡 Intuition & Approach

## Take/Skip DP (Memoization)

At each house `i`, two choices:
- **Take**: Rob this house → add `nums[i]`, skip next house → `nums[i] + dp[i+2]`
- **Skip**: Don't rob → move to next house → `dp[i+1]`

Pick the max of both.

```
nums = [2, 7, 9, 3, 1]
dp[4] = 1 (take 1)
dp[3] = max(3+0, 1) = 3
dp[2] = max(9+1, 3) = 10
dp[1] = max(7+3, 10) = 10
dp[0] = max(2+10, 10) = 12
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — each state computed once
```

## Space Complexity

```
O(N) — dp array + recursion stack
```

---

# 💻 Code

```cpp
class Solution {
public:
    int hepler(vector<int>& nums, int i, vector<int>& dp) {
        if (i >= nums.size())
            return 0;
        if (dp[i] != -1)
            return dp[i];
        int take = nums[i] + hepler(nums, i + 2, dp);
        int ignore = hepler(nums, i + 1, dp);
        return dp[i] = max(take, ignore);
    }
    int rob(vector<int>& nums) {
        vector<int> dp(101, -1);
        return hepler(nums, 0, dp);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single house → rob it

✅ Two houses → rob the one with more money

✅ All houses same value → rob alternate houses

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Classic take/skip DP.
dp[i] = max(nums[i] + dp[i+2], dp[i+1])
"Take and skip next" vs "skip current"
```

## Common Mistakes

❌ Forgetting the skip option → only considering "take" leads to wrong answers.

❌ Not handling the boundary `i >= nums.size()`.

---

## Related Problems

- 213. House Robber II (circular)
- 337. House Robber III (tree)
- 740. Delete and Earn

---

# 🧠 Revision Notes

## Pattern Recognition

Take/Skip pattern — at each element, decide to include or exclude:

```
take = value[i] + solve(i + 2)  // include, skip adjacent
skip = solve(i + 1)              // exclude, move to next
dp[i] = max(take, skip)
```
