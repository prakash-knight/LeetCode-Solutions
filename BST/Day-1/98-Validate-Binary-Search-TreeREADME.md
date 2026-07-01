# 98. Validate Binary Search Tree

[Link to LeetCode Problem](https://leetcode.com/problems/validate-binary-search-tree/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as:
- The left subtree of a node contains only nodes with keys **less than** the node's key.
- The right subtree contains only nodes with keys **greater than** the node's key.
- Both subtrees must also be valid BSTs.

### Example

```
Input:  root = [5,1,4,null,null,3,6]
Output: false

    5
   / \
  1   4      ← 4 is NOT > 5, invalid!
     / \
    3   6

Input:  root = [2,1,3]
Output: true
```

---

# 💡 Intuition & Approach

## Range-Based DFS (Min/Max Bounds)

Each node must satisfy: `min < node->val < max`. As we recurse:
- Going **left**: the current node becomes the new **upper bound**.
- Going **right**: the current node becomes the new **lower bound**.

Start with bounds `(LLONG_MIN, LLONG_MAX)` to handle INT_MIN/INT_MAX edge cases.

```
Node 5: (-∞, +∞) ✓
  Left 1: (-∞, 5) ✓
  Right 4: (5, +∞) → 4 < 5 → INVALID ✗
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
    bool valid(TreeNode* root, long long maxi, long long mini) {
        if (!root)
            return true;

        if (root->val <= mini)
            return false;
        if (root->val >= maxi)
            return false;

        return valid(root->left, root->val, mini) &&
               valid(root->right, maxi, root->val);
    }
    bool isValidBST(TreeNode* root) {
        return valid(root, LLONG_MAX, LLONG_MIN);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → valid BST

✅ Single node → valid BST

✅ Node with value INT_MAX or INT_MIN → handled by using `long long` bounds

✅ Valid left child but violates grandparent constraint → caught by propagated bounds

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Each node carries an allowed range (min, max).
Left child: range becomes (min, parent_val)
Right child: range becomes (parent_val, max)
Use long long to avoid overflow with INT_MIN/INT_MAX values.
```

## Common Mistakes

❌ Only checking immediate children → misses grandparent constraint violations.

❌ Using `int` for bounds → fails when node value is INT_MIN or INT_MAX.

❌ Using `<=` and `>=` incorrectly — BST requires strictly less/greater (no duplicates).

---

## Related Problems

- 700. Search in a Binary Search Tree
- 230. Kth Smallest Element in a BST
- 501. Find Mode in Binary Search Tree

---

# 🧠 Revision Notes

## Pattern Recognition

For BST validation problems:

```
Carry (min, max) bounds down the tree.
Alternative: Inorder traversal should be strictly increasing.
Both approaches are O(N) time, O(H) space.
```
