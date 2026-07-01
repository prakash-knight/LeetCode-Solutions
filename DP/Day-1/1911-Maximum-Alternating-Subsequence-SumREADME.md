# 1911. Maximum Alternating Subsequence Sum

[Link to LeetCode Problem](https://leetcode.com/problems/maximum-alternating-subsequence-sum/)

---

## 📝 Problem Statement

The **alternating sum** of a subsequence is computed as: the sum of elements at **even** indices minus the sum of elements at **odd** indices (0-indexed within the subsequence).

Return the maximum alternating sum of any subsequence of the array.

### Example

```
Input:  nums = [4,2,5,3]
Output: 7

Subsequence [4, 2, 5]: alternating sum = 4 - 2 + 5 = 7
```

---

# 💡 Intuition & Approach

## 2-State DP (Even/Odd Position)

Track whether the next element we pick would be at an even or odd position in our subsequence.

- **even = 1**: Next element gets **added** (even position).
- **even = 0**: Next element gets **subtracted** (odd position).

At each element, two choices:
- **Skip**: move to next element, state unchanged.
- **Take**: add/subtract based on state, toggle the state.

```
nums = [4, 2, 5, 3], start with even=1
Best: take 4(+), take 2(-), take 5(+) = 4 - 2 + 5 = 7
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — N elements × 2 states, each computed once
```

## Space Complexity

```
O(N) — dp array of size N×2
```

---

# 💻 Code

```cpp
class Solution {
public:
    using ll = long long;

    ll dp[100005][2];

    ll solve(vector<int>& nums, int i, int even) {
        if (i == nums.size())
            return 0;

        if (dp[i][even] != -1)
            return dp[i][even];

        ll skip = solve(nums, i + 1, even);

        ll take;
        if (even)
            take = nums[i] + solve(nums, i + 1, 0);
        else
            take = -nums[i] + solve(nums, i + 1, 1);

        return dp[i][even] = max(skip, take);
    }

    long long maxAlternatingSum(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solve(nums, 0, 1);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single element → take it (positive sum)

✅ All elements equal → take just one

✅ Decreasing array → take first element only

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Track the "parity" of the next position as a DP state.
Even position → add, Odd position → subtract.
Take/skip at each element.
```

## Common Mistakes

❌ Using `int` instead of `long long` → overflow for large arrays.

❌ Not toggling the even/odd state correctly after taking.

---

## Related Problems

- 376. Wiggle Subsequence
- 198. House Robber (take/skip pattern)
- 300. Longest Increasing Subsequence

---

# 🧠 Revision Notes

## Pattern Recognition

Multi-state subsequence DP:

```
State: (index, additional_state)
Here additional_state = even/odd toggle
Choices: take (toggle state) or skip (keep state)
```
