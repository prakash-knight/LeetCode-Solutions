# 103. Binary Tree Zigzag Level Order Traversal

[Link to LeetCode Problem](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, return the **zigzag level order** traversal of its nodes' values (i.e., from left to right, then right to left for the next level and alternate).

### Example

```
Input:  root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]

    3        → left to right:  [3]
   / \
  9  20      → right to left:  [20,9]
    /  \
   15   7    → left to right:  [15,7]
```

---

# 💡 Intuition & Approach

## BFS + Index Placement

Standard level-order BFS, but alternate the placement direction:
1. Create a `temp` vector of size `level_size`.
2. If going left-to-right (`p = true`): place at index `i`.
3. If going right-to-left (`p = false`): place at index `size - 1 - i`.
4. Toggle `p` after each level.

The queue always processes nodes left-to-right, but the placement index controls the output order.

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — visit every node once
```

## Space Complexity

```
O(N) — queue + result
```

---

# 💻 Code

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    void bfs(TreeNode* root) {
        if (!root)
            return;

        queue<TreeNode*> q;
        q.push(root);
        bool p = 1;
        while (!q.empty()) {
            int size = q.size();
            vector<int> temp(size, -1);
            int idx;
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                if (p) {
                    idx = i;
                } else {
                    idx = size - 1 - i;
                }
                temp[idx] = node->val;
                q.pop();

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            p = !p;
            ans.push_back(temp);
        }
    }
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        bfs(root);
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → returns `[]`

✅ Single node → returns `[[val]]`

✅ Two levels → second level is reversed

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Same BFS as level-order, but alternate index placement:
  Left-to-right: idx = i
  Right-to-left: idx = size - 1 - i
```

Alternative approach: do normal BFS, then `reverse()` every odd-level vector.

## Common Mistakes

❌ Using two stacks instead of a queue — works but more complex.

❌ Forgetting to toggle the direction flag.

---

## Related Problems

- 102. Binary Tree Level Order Traversal (simpler version)
- 107. Binary Tree Level Order Traversal II

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Alternating direction traversal

Think:

```
BFS + toggle a boolean flag per level.
Control output direction via index math, not queue order.
```
