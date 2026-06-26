# 987. Vertical Order Traversal of a Binary Tree

[Link to LeetCode Problem](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, return the **vertical order traversal** of its nodes' values.

For each node at position `(row, col)`:
- Its left child is at `(row + 1, col - 1)`
- Its right child is at `(row + 1, col + 1)`

Group nodes by column, and within the same column sort by row, then by value.

### Example

```
Input:  root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]

Column -1: [9]
Column  0: [3, 15]
Column  1: [20]
Column  2: [7]
```

---

# 💡 Intuition & Approach

## DFS + Sort by (col, row, val)

1. DFS the tree, recording `{col, row, val}` for each node.
2. Sort the collected triples — `sort()` naturally orders by col first, then row, then val.
3. Group consecutive entries with the same column into the same sub-array.

### Why This Works

Sorting by `(col, row, val)` guarantees:
- Columns are grouped together
- Within a column, nodes at higher rows come first
- Same position nodes are sorted by value

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N log N) — dominated by sorting
```

## Space Complexity

```
O(N) — storing all node triples
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

✅ Nodes at same position → sorted by value (guaranteed by triple sort)

✅ Single column tree (skewed left) → all nodes in one group

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Store {col, row, val} triples → sort → group by column.
Sorting handles all ordering requirements automatically.
```

## Common Mistakes

❌ Using `map<int, vector>` with DFS but not sorting by value within same `(row, col)`.

❌ Confusing this problem with LC 314 (Binary Tree Vertical Order Traversal) which doesn't require value-sorting at same position.

---

## Related Problems

- 314. Binary Tree Vertical Order Traversal (simpler, no value sort)
- 102. Binary Tree Level Order Traversal
- 199. Binary Tree Right Side View

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Vertical / diagonal traversal with multi-key ordering

Think:

```
DFS to collect (col, row, val) triples → sort → group.
```
