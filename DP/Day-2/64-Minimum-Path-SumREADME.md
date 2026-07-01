# 64. Minimum Path Sum

[Link to LeetCode Problem](https://leetcode.com/problems/minimum-path-sum/)

---

## 📝 Problem Statement

Given an `m x n` grid filled with non-negative numbers, find a path from top-left to bottom-right which **minimizes the sum** of all numbers along its path. You can only move **right** or **down**.

### Example

```
Input:  grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7

Path: 1 → 3 → 1 → 1 → 1 = 7

  [1] [3] [1]
  [1]  5  [1]
   4   2  [1]
```

---

# 💡 Intuition & Approach

## Top-Down Grid DP (Min Cost Path)

From each cell, go right or down. Pick the direction with minimum cost.

1. Out of bounds → return `1e9` (infinity, avoid this path).
2. Reached destination `(m-1, n-1)` → return `grid[i][j]`.
3. Recurrence: `dp[i][j] = grid[i][j] + min(right, down)`.

```
grid = [[1,3,1],[1,5,1],[4,2,1]]
dp[2][2] = 1
dp[1][2] = 1+1 = 2, dp[2][1] = 2+1 = 3
dp[0][2] = 1+2 = 3, dp[1][1] = 5+min(2,3) = 7
dp[0][0] = 1+min(dp[0][1], dp[1][0]) = 1+min(6,6) = 7
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(m × n) — each cell computed once
```

## Space Complexity

```
O(m × n) — dp table + recursion stack
```

---

# 💻 Code

```cpp
class Solution {
public:
    int helper(vector<vector<int>>& grid, int i, int j, int m, int n,
               vector<vector<int>>& dp) {
        if (i >= m || j >= n)
            return 1e9;
        if (i == m - 1 && j == n - 1)
            return grid[i][j];
        if (dp[i][j] != -1)
            return dp[i][j];

        int right = helper(grid, i, j + 1, m, n, dp);
        int down = helper(grid, i + 1, j, m, n, dp);

        return dp[i][j] = grid[i][j] + min(right, down);
    }
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));

        return helper(grid, 0, 0, m, n, dp);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ 1×1 grid → return the single element

✅ Single row/column → only one path

✅ All zeros → path sum is 0

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Same structure as Unique Paths, but instead of counting:
dp[i][j] = grid[i][j] + min(dp[right], dp[down])
Use 1e9 for out-of-bounds (not 0, since we're minimizing).
```

## Common Mistakes

❌ Returning 0 for out of bounds → incorrect minimization (0 < any valid path).

❌ Forgetting to add `grid[i][j]` to the cost.

---

## Related Problems

- 62. Unique Paths
- 120. Triangle
- 174. Dungeon Game
- 741. Cherry Pickup

---

# 🧠 Revision Notes

## Pattern Recognition

Grid min-cost path DP:

```
State: (row, col)
Recurrence: dp[i][j] = cost[i][j] + min(dp[right], dp[down])
Out of bounds → infinity (for minimization problems)
Out of bounds → 0 (for counting problems)
```
