# 230. Kth Smallest Element in a BST

[Link to LeetCode Problem](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)

---

## 📝 Problem Statement

Given the `root` of a binary search tree, and an integer `k`, return the `kth` smallest value (**1-indexed**) of all the values in the BST.

### Example

```
Input:  root = [3,1,4,null,2], k = 1
Output: 1

    3
   / \
  1   4
   \
    2

Inorder: [1, 2, 3, 4] → 1st smallest = 1
```

---

# 💡 Intuition & Approach

## Inorder Traversal with Early Stop

BST inorder traversal visits nodes in **sorted ascending order**. So the kth node visited in inorder is the kth smallest.

1. Recurse left (smaller values first).
2. Decrement `k`. If `k == 0`, this is the answer — return it.
3. Recurse right.
4. Use return value to propagate the answer upward and stop early.

```
Tree: [3,1,4,null,2], k=1
Inorder visits: 1(k=0 → FOUND!) → stop early
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(H + k) — descend to leftmost, then visit k nodes
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
    int inorder(TreeNode* root, int& k) {
        if (!root)
            return -1;

        int left = inorder(root->left, k);
        if (left != -1)
            return left;

        k--;
        if (k == 0)
            return root->val;

        return inorder(root->right, k);
    }
    int kthSmallest(TreeNode* root, int k) { return inorder(root, k); }
};
```

---

# 🔍 Edge Cases Handled

✅ k = 1 → return smallest (leftmost node)

✅ k = n → return largest (rightmost node)

✅ Single node with k = 1 → return root

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
BST Inorder = Sorted Order.
Decrement k at each visit; when k hits 0, that's your answer.
Pass k by reference for early termination.
```

## Common Mistakes

❌ Not using pass-by-reference for `k` → k doesn't persist across recursive calls.

❌ Not propagating the found value upward → answer gets lost in recursion.

---

## Related Problems

- 94. Binary Tree Inorder Traversal
- 378. Kth Smallest Element in a Sorted Matrix
- 671. Second Minimum Node In a Binary Tree

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever you need the "kth element" from a BST:

```
Inorder traversal + counter.
Pass counter by reference for early exit.
Return sentinel (-1) when not yet found, actual value when found.
```
