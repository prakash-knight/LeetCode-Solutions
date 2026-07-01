# 114. Flatten Binary Tree to Linked List

[Link to LeetCode Problem](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, flatten the tree into a "linked list":

- The "linked list" should use the same `TreeNode` class where the `right` child pointer points to the next node in the list and the `left` child pointer is always `null`.
- The "linked list" should be in the same order as a **pre-order traversal** of the binary tree.

### Example

```
Input:  root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]

      1               1
     / \                \
    2   5       →        2
   / \   \                \
  3   4   6                3
                            \
                             4
                              \
                               5
                                \
                                 6
```

---

# 💡 Intuition & Approach

## Reverse Postorder (Right → Left → Root)

The key insight: if we process in **reverse pre-order** (right → left → root), each node we visit should point its `right` to the previously visited node.

1. Recursively process `right` subtree first.
2. Then process `left` subtree.
3. At each node: set `right = prev`, set `left = null`, update `prev = root`.

This builds the flattened list from the **tail to the head**.

```
Processing order: 6 → 5 → 4 → 3 → 2 → 1
prev chain:       null←6←5←4←3←2←1
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — visit every node exactly once
```

## Space Complexity

```
O(H) — recursion stack, where H is height of tree
```

---

# 💻 Code

```cpp
class Solution {
public:
    TreeNode* prev = nullptr;
    void linked(TreeNode* root) {
        if (!root)
            return;

        linked(root->right);
        linked(root->left);

        root->right = prev;
        root->left = nullptr;

        prev = root;
    }
    void flatten(TreeNode* root) { linked(root); }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → nothing to flatten

✅ Single node → already flat

✅ Left-skewed tree → all nodes move to right chain

✅ Right-skewed tree → already in correct order

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Process in reverse pre-order (right → left → node).
Each node's right = prev, left = null.
Build the linked list from tail → head.
```

## Common Mistakes

❌ Processing in normal pre-order — overwrites `right` before visiting it.

❌ Forgetting to set `left = nullptr` — results in invalid tree structure.

---

## Related Problems

- 897. Increasing Order Search Tree
- 430. Flatten a Multilevel Doubly Linked List
- 2415. Reverse Odd Levels of Binary Tree

---

# 🧠 Revision Notes

## Pattern Recognition

When you need to rearrange tree pointers in pre-order:

```
Reverse the traversal order to avoid overwriting pointers.
Use a `prev` pointer to chain nodes from tail to head.
```
