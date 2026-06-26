# 110. Balanced Binary Tree

[Link to LeetCode Problem](https://leetcode.com/problems/balanced-binary-tree/)

---

## 📝 Problem Statement

Given a binary tree, determine if it is **height-balanced**.

A height-balanced binary tree is a tree in which the depth of the two subtrees of every node never differs by more than one.

### Example

```
Input:  root = [3,9,20,null,null,15,7]
Output: true

    3
   / \
  9  20
    /  \
   15   7

Input:  root = [1,2,2,3,3,null,null,4,4]
Output: false
```

---

# 💡 Intuition & Approach

## Top-Down (Current Approach)

For each node:
1. Compute `height(left)` and `height(right)`.
2. If `|left - right| > 1` → not balanced.
3. Recursively check both subtrees.

This is simple but has redundant height calculations (O(N log N) for balanced trees, O(N²) worst case).

### Note

An optimized O(N) approach computes height and checks balance in a single pass (return -1 for unbalanced), but this top-down version is clearer.

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N log N) balanced tree, O(N²) skewed tree
```

- Height is O(N), called for each node

## Space Complexity

```
O(H) — recursion stack
```

---

# 💻 Code

```cpp
class Solution {
public:
    int height(TreeNode* root) {
        if (!root)
            return 0;

        return 1 + max(height(root->left), height(root->right));
    }

    bool isBalanced(TreeNode* root) {
        if (!root)
            return true;

        int left = height(root->left);
        int right = height(root->right);

        if (abs(left - right) > 1)
            return false;

        return isBalanced(root->left) &&
               isBalanced(root->right);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → balanced (returns `true`)

✅ Single node → balanced

✅ Subtree is balanced but root is not → correctly detected

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Balanced = |height(left) - height(right)| ≤ 1 for EVERY node.
Check at each node + recurse into both subtrees.
```

## Common Mistakes

❌ Only checking the root node's balance → subtrees can be unbalanced.

❌ Confusing "balanced" with "complete" or "perfect" tree.

---

## Related Problems

- 104. Maximum Depth of Binary Tree
- 543. Diameter of Binary Tree (also uses height)
- 124. Binary Tree Maximum Path Sum

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Check a property at every node involving subtree heights

Think:

```
height() helper + check condition at each node.
Optimize to O(N) by returning -1 for early termination.
```
