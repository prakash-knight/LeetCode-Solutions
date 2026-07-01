# 120. Triangle

[Link to LeetCode Problem](https://leetcode.com/problems/triangle/)

---

## 📝 Problem Statement

Given a `triangle` array, return the minimum path sum from top to bottom. At each step, you may move to an adjacent number on the row below (i.e., from index `j` you can move to `j` or `j+1` on the next row).

### Example

```
Input:  triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11

    2
   3 4
  6 5 7
 4 1 8 3

Min path: 2 → 3 → 5 → 1 = 11
```

---

# 💡 Intuition & Approach

## Top-Down DP with Visited Array

From cell `(i, j)`, two choices: go **down** `(i+1, j)` or **diagonal** `(i+1, j+1)`.

1. Base case: last row → return `t[i][j]` (leaf value).
2. Recurrence: `dp[i][j] = t[i][j] + min(down, diagonal)`.
3. Use a `visited` array since triangle values can be negative (can't use -1 as sentinel).

```
    2
   3 4
  6 5 7
 4 1 8 3

dp[3][*] = [4, 1, 8, 3]
dp[2][0] = 6+min(4,1) = 7
dp[2][1] = 5+min(1,8) = 6
dp[1][0] = 3+min(7,6) = 9
dp[1][1] = 4+min(6,15) = 10
dp[0][0] = 2+min(9,10) = 11
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N²) — where N is the number of rows (total elements = N*(N+1)/2)
```

## Space Complexity

```
O(N²) — dp + visited arrays
```

---

# 💻 Code

```cpp
class Solution {
public:
    int helper(vector<vector<int>>& t, int i, int j, int m,
               vector<vector<int>>& dp, vector<vector<bool>>& vis) {

        if (i == m - 1)
            return t[i][j];

        if (vis[i][j])
            return dp[i][j];

        vis[i][j] = true;

        int down = helper(t, i + 1, j, m, dp, vis);
        int diagonal = helper(t, i + 1, j + 1, m, dp, vis);

        return dp[i][j] = t[i][j] + min(down, diagonal);
    }

    int minimumTotal(vector<vector<int>>& t) {
        int m = t.size();

        vector<vector<int>> dp(m, vector<int>(m, 0));
        vector<vector<bool>> vis(m, vector<bool>(m, false));

        return helper(t, 0, 0, m, dp, vis);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single element triangle → return that element

✅ Negative values → visited array instead of -1 sentinel

✅ All paths same cost → any path works

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Triangle DP: from (i,j) go to (i+1,j) or (i+1,j+1).
dp[i][j] = t[i][j] + min(dp[i+1][j], dp[i+1][j+1])
Use visited array for negative values (can't use -1 sentinel).
```

## Common Mistakes

❌ Using -1 as memo sentinel when values can be negative → wrong cache hits.

❌ Moving to wrong indices (j-1 instead of j+1 for diagonal).

---

## Related Problems

- 64. Minimum Path Sum
- 931. Minimum Falling Path Sum
- 1289. Minimum Falling Path Sum II

---

# 🧠 Revision Notes

## Pattern Recognition

Triangle/pyramid DP:

```
Different from grid DP — only two choices: down or diagonal-right.
Bottom-up approach is cleaner: start from last row, work upward.
When values can be negative, use a separate visited/bool array.
```
