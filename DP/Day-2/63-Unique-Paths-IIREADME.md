# 63. Unique Paths II

[Link to LeetCode Problem](https://leetcode.com/problems/unique-paths-ii/)

---

## 📝 Problem Statement

Same as Unique Paths, but now the grid has **obstacles**. An obstacle is marked as `1` in the grid. Find the number of unique paths from top-left to bottom-right, avoiding obstacles.

### Example

```
Input:  obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2

  S → → ↓
  ↓   X   ↓
    → → E

Paths: Right→Right→Down→Down, Down→Down→Right→Right
```

---

# 💡 Intuition & Approach

## Top-Down Grid DP with Obstacle Check

Same as Unique Paths, but add obstacle check: if `obstacleGrid[i][j] == 1`, return 0 (blocked).

1. Out of bounds → return 0.
2. Obstacle → return 0.
3. Reached destination → return 1.
4. Recurrence: `dp[i][j] = paths(i, j+1) + paths(i+1, j)`.

```
Grid with obstacle at (1,1):
[0, 0, 0]
[0, X, 0]  → dp[1][1] = 0 (blocked)
[0, 0, 0]
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
    int helper(int m, int n, vector<vector<int>>& dp, int i, int j,
               vector<vector<int>>& obstacleGrid) {
        if (i >= m || j >= n)
            return 0;
        if (obstacleGrid[i][j] == 1)
            return 0;
        if (i == m - 1 && j == n - 1)
            return 1;

        if (dp[i][j] != -1)

            return dp[i][j];

        // right

        int right = helper(m, n, dp, i, j + 1, obstacleGrid);

        int down = helper(m, n, dp, i + 1, j, obstacleGrid);

        return dp[i][j] = right + down;
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
        return helper(m, n, dp, 0, 0, obstacleGrid);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Start cell is obstacle → return 0

✅ End cell is obstacle → return 0

✅ No path exists → return 0

✅ No obstacles → same as Unique Paths

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Same as Unique Paths + obstacle check before processing.
if (grid[i][j] == 1) return 0;
Check obstacle BEFORE destination check (obstacle at destination = 0 paths).
```

## Common Mistakes

❌ Checking destination before obstacle → wrong answer if destination is blocked.

❌ Not handling obstacle at start position.

---

## Related Problems

- 62. Unique Paths
- 64. Minimum Path Sum
- 980. Unique Paths III

---

# 🧠 Revision Notes

## Pattern Recognition

Grid DP with constraints — add constraint checks before the base case:

```
1. Boundary check
2. Constraint check (obstacles, walls, etc.)
3. Destination check
4. Memoization check
5. Recurse
```
