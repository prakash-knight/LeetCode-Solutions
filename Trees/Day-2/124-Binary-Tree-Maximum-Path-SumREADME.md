# 124. Binary Tree Maximum Path Sum

[Link to LeetCode Problem](https://leetcode.com/problems/binary-tree-maximum-path-sum/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, return the **maximum path sum** of any non-empty path.

A **path** is a sequence of nodes where each pair of adjacent nodes has an edge. A node can only appear in the path at most once. The path does **not** need to pass through the root.

### Example

```
Input:  root = [-10,9,20,null,null,15,7]
Output: 42

    -10
    / \
   9  20
     /  \
    15   7

Path: 15 → 20 → 7 = 42
```

---

# 💡 Intuition & Approach

## Post-order DFS + Global Max

1. At each node, compute the max contribution from the left and right subtrees.
   - Use `max(0, subtree_sum)` to discard negative branches.
2. **Local path sum** through this node = `node->val + left + right` (path bends here).
3. Update global `sum = max(sum, localsum)`.
4. **Return upward** = `node->val + max(left, right)` (can only extend one branch upward).

```
At node 20: left=15, right=7 → localsum = 20+15+7 = 42 ✓
  Return up: 20 + max(15,7) = 35
At node -10: left=9, right=35 → localsum = -10+9+35 = 34
  Global max remains 42.
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
    int sum = INT_MIN;
    int itr(TreeNode* root) {
        if (!root)
            return 0;
        int localsum = 0;

        int left = max(0, itr(root->left));
        int right = max(0, itr(root->right));

        localsum = root->val + left + right;

        sum = max(localsum, sum);
        return root->val + max(left, right);
    }
    int maxPathSum(TreeNode* root) {
        itr(root);
        return sum;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ All negative values → picks the least negative single node

✅ Single node → path sum = node value

✅ Path entirely in a subtree (doesn't pass through root)

✅ `max(0, ...)` discards negative subtrees automatically

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
At each node:
  Global update: val + left + right (path BENDS here)
  Return upward: val + max(left, right) (path EXTENDS one way)

Use max(0, subtree) to discard negative contributions.
```

## Common Mistakes

❌ Initializing `sum = 0` instead of `INT_MIN` → fails for all-negative trees.

❌ Returning `left + right + val` upward → can't bend twice (invalid path).

❌ Forgetting `max(0, ...)` → includes negative branches that hurt the sum.

---

## Related Problems

- 543. Diameter of Binary Tree (same pattern, simpler)
- 687. Longest Univalue Path
- 1372. Longest ZigZag Path in a Binary Tree

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Maximum path sum / length through any node
- Global optimum involving both subtrees

Think:

```
"Bend vs Extend" pattern:
  Global: node + left + right  (path bends)
  Return: node + max(left, right)  (path extends)
```
