# 199. Binary Tree Right Side View

[Link to LeetCode Problem](https://leetcode.com/problems/binary-tree-right-side-view/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, imagine yourself standing on the **right side** of it. Return the values of the nodes you can see ordered from top to bottom.

### Example

```
Input:  root = [1,2,3,null,5,null,4]
Output: [1,3,4]

   1       ← you see 1
  / \
 2   3     ← you see 3
  \   \
   5   4   ← you see 4
```

---

# 💡 Intuition & Approach

## DFS with (col, row, val) + Rightmost per Level

Use a DFS approach collecting `{col, row, val}` triples. After sorting, the rightmost node at each level is the last value seen per row when iterating by column order.

Alternatively, a cleaner BFS approach: at each level, the **last node** in the queue is the right-side view node.

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N log N) — DFS + sort approach
O(N) — BFS approach
```

## Space Complexity

```
O(N)
```

---

# 💻 Code

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    void dfs(TreeNode* root, int le, int col) {
        if (!root)
            return;

        ans.push_back({col, le, root->val});

        dfs(root->left, le + 1, col - 1);
        dfs(root->right, le + 1, col + 1);
    }
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        dfs(root, 0, 0);
        sort(ans.begin(), ans.end());
        vector<vector<int>> f;
        int col = INT_MIN;
        vector<int> temp;
        for (auto& t : ans) {
            if (col == INT_MIN) {
                temp.push_back(t[2]);
                col = t[0];
            } else if (col == t[0]) {
                temp.push_back(t[2]);
            } else {
                f.push_back(temp);
                temp.clear();
                col = t[0];
                temp.push_back(t[2]);
            }
        }
        if (!temp.empty())
            f.push_back(temp);

        return f;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → returns `[]`

✅ Left-skewed tree → each level has only a left node visible from right

✅ Right-skewed tree → all nodes visible

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
BFS approach (cleaner): at each level, the LAST node popped is the right-side view.
DFS approach: track depth, only add to result when visiting a new depth for the first time (right-first DFS).
```

## Common Mistakes

❌ Only traversing the right subtree → misses cases where left subtree is deeper.

---

## Related Problems

- 102. Binary Tree Level Order Traversal
- 987. Vertical Order Traversal of a Binary Tree
- 515. Find Largest Value in Each Tree Row

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- View from one side of a tree
- First/last node at each level

Think:

```
BFS: last node per level = right side view
     first node per level = left side view
```
