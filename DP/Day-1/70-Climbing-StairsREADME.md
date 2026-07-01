# 70. Climbing Stairs

[Link to LeetCode Problem](https://leetcode.com/problems/climbing-stairs/)

---

## 📝 Problem Statement

You are climbing a staircase. It takes `n` steps to reach the top. Each time you can either climb `1` or `2` steps. In how many distinct ways can you climb to the top?

### Example

```
Input:  n = 3
Output: 3

Ways: [1+1+1], [1+2], [2+1]
```

---

# 💡 Intuition & Approach

## Top-Down DP (Memoization)

At any step `sum`, we have two choices: take 1 step or take 2 steps.

1. Base case: if `sum == n`, we've reached the top → return 1.
2. If `sum > n`, we've overshot → return 0.
3. Recurrence: `dp[sum] = solver(sum + 1) + solver(sum + 2)`.
4. Memoize with a dp array to avoid recomputation.

This is essentially the **Fibonacci sequence**: `f(n) = f(n-1) + f(n-2)`.

```
n = 3:
f(0) = f(1) + f(2)
f(1) = f(2) + f(3) = 1 + 1 = 2
f(2) = f(3) + f(4) = 1 + 0 = 1
f(0) = 2 + 1 = 3
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
    int solver(vector<int>& dp, int sum, int n) {
        if (sum == n)
            return 1;
        if (sum > n)
            return 0;
        if (dp[sum] != -1)
            return dp[sum];
        return dp[sum] = solver(dp, sum + 1, n) + solver(dp, sum + 2, n);
    }
    int climbStairs(int n) {
        vector<int> dp(n + 1, -1);
        return solver(dp, 0, n);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ n = 1 → only 1 way (single step)

✅ n = 2 → 2 ways (1+1 or 2)

✅ Large n → memoization prevents TLE

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Climbing stairs = Fibonacci.
dp[i] = dp[i-1] + dp[i-2]
Can be optimized to O(1) space with two variables.
```

## Common Mistakes

❌ Missing memoization → exponential time.

❌ Off-by-one on base case (sum == n vs sum == n-1).

---

## Related Problems

- 509. Fibonacci Number
- 746. Min Cost Climbing Stairs
- 198. House Robber

---

# 🧠 Revision Notes

## Pattern Recognition

Classic 1D DP pattern — at each state, make a choice from a small set of options:

```
State: current position
Choices: step +1 or step +2
Recurrence: dp[i] = dp[i+1] + dp[i+2]
```
