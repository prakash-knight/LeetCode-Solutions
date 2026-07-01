# 62. Unique Paths

[Link to LeetCode Problem](https://leetcode.com/problems/unique-paths/)

---

## 📝 Problem Statement

A robot is located at the top-left corner of an `m x n` grid. The robot can only move either **down** or **right** at any point. Find the number of unique paths to reach the bottom-right corner.

### Example

```
Input:  m = 3, n = 7
Output: 28

  S → → → → → →
  ↓               ↓
  ↓               E
```

---

# 💡 Intuition & Approach

## Top-Down Grid DP (Memoization)

From any cell `(i, j)`, we can go **right** `(i, j+1)` or **down** `(i+1, j)`.

1. Base case: reach `(m-1, n-1)` → return 1 (found a path).
2. Out of bounds → return 0.
3. Recurrence: `dp[i][j] = paths(i, j+1) + paths(i+1, j)`.

```
3×3 grid:
dp[2][2] = 1 (destination)
dp[1][2] = 1, dp[2][1] = 1
dp[0][2] = 1, dp[1][1] = 2, dp[2][0] = 1
dp[0][1] = 3, dp[1][0] = 3
dp[0][0] = 6
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(m × n) — each cell computed once
```

## Space Complexity

```
O(m × n) — dp table + recursion stack O(m+n)
```

---

# 💻 Code

```cpp
class Solution {
public:
    int helper(int m, int n, vector<vector<int>>& dp, int i, int j) {
        if (i == m - 1 && j == n - 1)
            return 1;

        if (i >= m || j >= n)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];
        // right
        int right = helper(m, n, dp, i, j + 1);
        int down = helper(m, n, dp, i + 1, j);

        return dp[i][j] = right + down;
    }
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
        return helper(m, n, dp, 0, 0);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ 1×1 grid → 1 path (already at destination)

✅ 1×n or m×1 grid → only 1 path (straight line)

✅ Large grids → memoization prevents TLE

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Grid paths = sum of paths from right + paths from down.
dp[i][j] = dp[i][j+1] + dp[i+1][j]
Also solvable with combinatorics: C(m+n-2, m-1)
```

## Common Mistakes

❌ Forgetting boundary checks → index out of bounds.

❌ Using wrong base case position.

---

## Related Problems

- 63. Unique Paths II (with obstacles)
- 64. Minimum Path Sum
- 174. Dungeon Game

---

# 🧠 Revision Notes

## Pattern Recognition

Grid DP — count paths with restricted movement:

```
State: (row, col)
Transitions: right and down
Base: destination cell = 1
```
