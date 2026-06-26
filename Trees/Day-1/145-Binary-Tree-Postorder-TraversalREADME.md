# 145. Binary Tree Postorder Traversal

[Link to LeetCode Problem](https://leetcode.com/problems/binary-tree-postorder-traversal/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, return the **postorder** traversal of its nodes' values.

Postorder: **Left → Right → Root**

### Example

```
Input:  root = [1,null,2,3]
Output: [3,2,1]

    1
     \
      2
     /
    3
```

---

# 💡 Intuition & Approach

## Recursive DFS

Recurse into the left subtree, then the right subtree, then visit the current node.

```
postorder(node):
  if node is null → return
  postorder(node->left)   ← left subtree
  postorder(node->right)  ← right subtree
  ans.push(node->val)     ← visit root (LAST)
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
        pre(root->right, ans);
        ans.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
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
Postorder = Left, Right, then Root LAST
Mnemonic: "LRN" (Left-Right-Node)
```

Useful for: deletion (delete children before parent), expression tree evaluation.

## Common Mistakes

❌ Confusing with preorder (root is visited first in preorder, last in postorder).

---

## Related Problems

- 144. Binary Tree Preorder Traversal
- 94. Binary Tree Inorder Traversal

---

# 🧠 Revision Notes

## Pattern Recognition

```
Preorder:  push → left → right
Inorder:   left → push → right
Postorder: left → right → push  ← this one
```
