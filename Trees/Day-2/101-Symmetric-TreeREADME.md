# 101. Symmetric Tree

[Link to LeetCode Problem](https://leetcode.com/problems/symmetric-tree/)

---

## 📝 Problem Statement

Given the `root` of a binary tree, check whether it is a **mirror** of itself (i.e., symmetric around its center).

### Example

```
Input:  root = [1,2,2,3,4,4,3]
Output: true

        1
       / \
      2   2
     / \ / \
    3  4 4  3   ← mirror!

Input:  root = [1,2,2,null,3,null,3]
Output: false
```

---

# 💡 Intuition & Approach

## Recursive Mirror Check

Compare the tree with its own mirror:
1. Two trees are mirrors if:
   - Both are `null` → ✅
   - One is `null`, other isn't → ❌
   - Values differ → ❌
   - `left.left` mirrors `right.right` AND `left.right` mirrors `right.left` → ✅

```
yes(q1, q2):
  if both null → true
  if one null → false
  if q1->val != q2->val → false
  return yes(q1->left, q2->right) && yes(q1->right, q2->left)
```

### Visual

```
        1
       / \
      2   2       compare: 2==2 ✓
     / \ / \
    3  4 4  3     compare: 3==3 ✓, 4==4 ✓ (cross-paired!)
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N) — visit every node once (in pairs)
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
    bool yes(TreeNode* q1, TreeNode* q2) {
        if (!q1 && !q2)
            return true;

        if ((!q1 && q2) || (!q2 && q1))
            return false;

        if (q1->val != q2->val)
            return false;

        return yes(q1->left, q2->right) && yes(q1->right, q2->left);
    }
    bool isSymmetric(TreeNode* root) {
        if (!root)
            return true;

        return yes(root->left, root->right);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → symmetric (true)

✅ Single node → symmetric (true)

✅ Structure matches but values differ → correctly returns false

✅ One subtree is null, other isn't → false

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Mirror comparison: cross-pair the children.
  left.left  ↔ right.right
  left.right ↔ right.left
```

## Common Mistakes

❌ Comparing `left.left` with `right.left` (same side) → that checks equality, not symmetry.

❌ Only checking structure without values.

---

## Related Problems

- 100. Same Tree (check equality instead of mirror)
- 226. Invert Binary Tree (actually create the mirror)

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Mirror / symmetry check

Think:

```
Recursive two-pointer comparison with cross-pairing.
Same Tree: same(L.left, R.left) && same(L.right, R.right)
Symmetric: sym(L.left, R.right) && sym(L.right, R.left)
```
