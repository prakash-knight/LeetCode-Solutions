# 102. Binary Tree Level Order Traversal

[Link to LeetCode Problem](https://leetcode.com/problems/binary-tree-level-order-traversal/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, return the **level order** traversal of its nodes' values (i.e., from left to right, level by level).

### Example

```
Input:  root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

    3
   / \
  9  20
    /  \
   15   7
```

---

# 💡 Intuition & Approach

## BFS with Queue

1. Push root into a queue.
2. While queue is not empty:
   - Record current queue size (`size` = number of nodes at this level).
   - Process exactly `size` nodes: pop each, add value to current level, push its children.
   - Add the level vector to the result.

```
Level 0: queue = [3],        pop 3  → push 9,20
Level 1: queue = [9,20],     pop 9,20 → push 15,7
Level 2: queue = [15,7],     pop 15,7
Result: [[3],[9,20],[15,7]]
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — visit every node once
```

## Space Complexity

```
O(N) — queue holds at most one level (widest level ≤ N/2)
```

---

# 💻 Code

```cpp
class Solution {
public:
    void bfs(TreeNode* root, vector<vector<int>>& ans) {
        if (root == nullptr)
            return;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            vector<int> level;
            int size = q.size();

            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                if (node->left)
                    q.push(node->left);

                if (node->right)
                    q.push(node->right);
            }

            ans.push_back(level);
        }
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        bfs(root, ans);
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → returns `[]`

✅ Single node → returns `[[val]]`

✅ Complete binary tree / skewed tree — both work

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
BFS + "snapshot" the queue size at the start of each level.
Process exactly that many nodes → they're all from the same level.
```

## Common Mistakes

❌ Not capturing `q.size()` before the inner loop → queue size changes during iteration.

❌ Forgetting null check for root → pushing nullptr into queue.

---

## Related Problems

- 103. Binary Tree Zigzag Level Order Traversal
- 107. Binary Tree Level Order Traversal II (bottom-up)
- 199. Binary Tree Right Side View

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Level-by-level processing
- BFS on a tree

Think:

```
Queue + snapshot size per level.
This is the template for ALL level-order problems.
```
