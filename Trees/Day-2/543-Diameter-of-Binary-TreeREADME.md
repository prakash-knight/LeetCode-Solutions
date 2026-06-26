# 543. Diameter of Binary Tree

[Link to LeetCode Problem](https://leetcode.com/problems/diameter-of-binary-tree/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, return the length of the **diameter** of the tree.

The **diameter** is the length of the longest path between any two nodes. This path may or may not pass through the root. The length is measured by the number of **edges**.

### Example

```
Input:  root = [1,2,3,4,5]
Output: 3

      1
     / \
    2   3
   / \
  4   5

Longest path: 4 → 2 → 1 → 3 (or 5 → 2 → 1 → 3), length = 3 edges
```

---

# 💡 Intuition & Approach

## Height + Track Diameter

The diameter through any node = `height(left) + height(right)`.

1. Compute height recursively (same as max depth).
2. At each node, update `diameter = max(diameter, left + right)`.
3. Return `1 + max(left, right)` as the height.

The key insight: the longest path through a node uses the tallest left subtree + tallest right subtree.

```
At node 2: left=1(4), right=1(5) → diameter candidate = 2
At node 1: left=2(from 2), right=1(3) → diameter candidate = 3 ✓
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — visit every node once
```

## Space Complexity

```
O(H) — recursion stack
```

---

# 💻 Code

```cpp
class Solution {
public:
    int diameter = 0;
    int height(TreeNode* root) {
        if (root == nullptr)
            return 0;

        int left = height(root->left);
        int right = height(root->right);

        diameter = max(diameter, left + right);

        return 1 + max(left, right);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        height(root);

        return diameter;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → diameter = 0

✅ Single node → diameter = 0

✅ Longest path doesn't pass through root → still found (tracked globally)

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Diameter at any node = height(left) + height(right)
Track global max while computing heights.
```

Same pattern as LC 124 (Max Path Sum) — compute a "through this node" value, track global best, but return a "single branch" value upward.

## Common Mistakes

❌ Returning `diameter` as height → confusing the two concepts.

❌ Only checking diameter at root → longest path might be entirely in a subtree.

---

## Related Problems

- 104. Maximum Depth of Binary Tree
- 110. Balanced Binary Tree
- 124. Binary Tree Maximum Path Sum (same pattern, harder)

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Longest path in a tree
- Maximum value involving both subtrees

Think:

```
height() helper + track global answer.
At each node: global = max(global, f(left, right))
Return: single-branch value upward.
```
