# 700. Search in a Binary Search Tree

[Link to LeetCode Problem](https://leetcode.com/problems/search-in-a-binary-search-tree/)

---

## 📝 Problem Statement

Given the `root` of a binary search tree (BST) and an integer `val`, find the node in the BST whose value equals `val` and return the subtree rooted at that node. If the node does not exist, return `null`.

### Example

```
Input:  root = [4,2,7,1,3], val = 2
Output: [2,1,3]

      4
     / \
    2   7     →  Search for 2  →  Return subtree rooted at 2
   / \
  1   3
```

---

# 💡 Intuition & Approach

## Iterative BST Search

Leverage the BST property: for any node, all left descendants < node < all right descendants.

1. Start at root.
2. If `val == root->val`, found it — return the node.
3. If `val < root->val`, go left.
4. If `val > root->val`, go right.
5. If we fall off the tree (`root == null`), return null.

```
Search for 2 in [4,2,7,1,3]:
  4 → val < 4, go left
  2 → val == 2, FOUND!
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(H) — where H is the height of the BST
       O(log N) for balanced, O(N) worst case (skewed)
```

## Space Complexity

```
O(1) — iterative, no extra space
```

---

# 💻 Code

```cpp
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root) {
            if (root->val == val)
                return root;

            if (val < root->val)
                root = root->left;
            else
                root = root->right;
        }

        return nullptr;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → return nullptr

✅ Value at root → return root immediately

✅ Value not in tree → return nullptr after traversal

✅ Single node tree → check and return

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
BST property gives O(H) search — just go left or right.
Iterative is preferred over recursive for O(1) space.
```

## Common Mistakes

❌ Using linear search (ignoring BST property) → O(N) instead of O(H).

❌ Forgetting to return nullptr when node not found.

---

## Related Problems

- 701. Insert into a Binary Search Tree
- 450. Delete Node in a BST
- 270. Closest Binary Search Tree Value

---

# 🧠 Revision Notes

## Pattern Recognition

BST search is the foundation of all BST operations:

```
val < node → go left
val > node → go right
val == node → found
```
