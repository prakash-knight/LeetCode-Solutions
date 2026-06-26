# 144. Binary Tree Preorder Traversal

[Link to LeetCode Problem](https://leetcode.com/problems/binary-tree-preorder-traversal/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, return the **preorder** traversal of its nodes' values.

Preorder: **Root → Left → Right**

### Example

```
Input:  root = [1,null,2,3]
Output: [1,2,3]

    1
     \
      2
     /
    3
```

---

# 💡 Intuition & Approach

## Recursive DFS

Visit the current node first, then recurse into the left subtree, then the right subtree.

```
pre(node):
  if node is null → return
  ans.push(node->val)   ← visit root
  pre(node->left)       ← left subtree
  pre(node->right)      ← right subtree
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — visit every node once
```

## Space Complexity

```
O(H) — recursion stack, H = height of tree
O(N) worst case (skewed tree), O(log N) balanced
```

---

# 💻 Code

```cpp
class Solution {
public:
    void pre(TreeNode* root, vector<int>& ans) {
        if (root == nullptr)
            return;

        ans.push_back(root->val);
        pre(root->left, ans);
        pre(root->right, ans);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        pre(root, ans);

        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree (`root == nullptr`) → returns `[]`

✅ Single node → returns `[val]`

✅ Left-skewed / right-skewed trees

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Preorder = Root FIRST, then Left, then Right
Mnemonic: "NLR" (Node-Left-Right)
```

## Common Mistakes

❌ Confusing order with inorder (Left-Node-Right) or postorder (Left-Right-Node).

---

## Related Problems

- 94. Binary Tree Inorder Traversal
- 145. Binary Tree Postorder Traversal
- 102. Binary Tree Level Order Traversal

---

# 🧠 Revision Notes

## Pattern Recognition

All three DFS traversals share the same structure — only the position of `ans.push_back(root->val)` changes:

```
Preorder:  push → left → right
Inorder:   left → push → right
Postorder: left → right → push
```
