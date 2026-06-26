# 94. Binary Tree Inorder Traversal

[Link to LeetCode Problem](https://leetcode.com/problems/binary-tree-inorder-traversal/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, return the **inorder** traversal of its nodes' values.

Inorder: **Left → Root → Right**

### Example

```
Input:  root = [1,null,2,3]
Output: [1,3,2]

    1
     \
      2
     /
    3
```

---

# 💡 Intuition & Approach

## Recursive DFS

Recurse into the left subtree first, then visit the current node, then recurse into the right subtree.

```
inorder(node):
  if node is null → return
  inorder(node->left)    ← left subtree
  ans.push(node->val)    ← visit root
  inorder(node->right)   ← right subtree
```

For a BST, inorder traversal gives nodes in **sorted order**.

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — visit every node once
```

## Space Complexity

```
O(H) — recursion stack, H = height of tree
```

---

# 💻 Code

```cpp
class Solution {
public:
    void pre(TreeNode* root, vector<int>& ans) {
        if (root == nullptr)
            return;

        pre(root->left, ans);
        ans.push_back(root->val);
        pre(root->right, ans);
    }
    vector<int> inorderTraversal(TreeNode* root) {
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
Inorder = Left FIRST, then Node, then Right
Mnemonic: "LNR" (Left-Node-Right)
```

For a BST, inorder gives **sorted output**.

## Common Mistakes

❌ Confusing with preorder (push happens before left recursion).

---

## Related Problems

- 144. Binary Tree Preorder Traversal
- 145. Binary Tree Postorder Traversal
- 230. Kth Smallest Element in a BST (inorder + counter)

---

# 🧠 Revision Notes

## Pattern Recognition

```
Preorder:  push → left → right
Inorder:   left → push → right  ← this one
Postorder: left → right → push
```
