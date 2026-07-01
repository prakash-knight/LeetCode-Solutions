# 509. Fibonacci Number

[Link to LeetCode Problem](https://leetcode.com/problems/fibonacci-number/)

---

## 📝 Problem Statement

The Fibonacci numbers form a sequence such that each number is the sum of the two preceding ones, starting from `0` and `1`:

`F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)` for `n > 1`.

Given `n`, calculate `F(n)`.

### Example

```
Input:  n = 4
Output: 3

F(0)=0, F(1)=1, F(2)=1, F(3)=2, F(4)=3
```

---

# 💡 Intuition & Approach

## Top-Down DP (Memoization)

Direct recursive implementation of the Fibonacci formula with memoization:

1. Base case: `F(0) = 0`, `F(1) = 1`.
2. Recurrence: `F(n) = F(n-1) + F(n-2)`.
3. Store results in dp array to avoid recomputation.

```
F(4) = F(3) + F(2)
     = (F(2) + F(1)) + (F(1) + F(0))
     = ((1) + 1) + (1 + 0)
     = 2 + 1 = 3
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
    int solve(int n, vector<int>& dp) {
        if (n <= 1)
            return dp[n] = n;
        if (dp[n] != -1)
            return dp[n];
        return dp[n] = solve(n - 1, dp) + solve(n - 2, dp);
    }
    int fib(int n) {
        vector<int> dp(n + 1, -1);
        solve(n, dp);
        return dp[n];
    }
};
```

---

# 🔍 Edge Cases Handled

✅ n = 0 → return 0

✅ n = 1 → return 1

✅ Large n → memoization prevents exponential blowup

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Classic DP foundation problem.
dp[n] = dp[n-1] + dp[n-2]
Can optimize to O(1) space with two variables.
```

## Common Mistakes

❌ Forgetting base case `F(0) = 0` → off-by-one errors.

❌ Not memoizing → O(2^n) time.

---

## Related Problems

- 70. Climbing Stairs
- 1137. N-th Tribonacci Number
- 746. Min Cost Climbing Stairs

---

# 🧠 Revision Notes

## Pattern Recognition

Fibonacci is the simplest example of the "linear DP" pattern:

```
Current state depends on the previous 2 states.
Three approaches: Recursion + Memo, Bottom-up tabulation, Space-optimized.
```
