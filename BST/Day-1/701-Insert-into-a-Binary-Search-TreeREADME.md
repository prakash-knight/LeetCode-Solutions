# 701. Insert into a Binary Search Tree

[Link to LeetCode Problem](https://leetcode.com/problems/insert-into-a-binary-search-tree/)

---

## 📝 Problem Statement

Given the `root` of a binary search tree (BST) and a `value` to insert, insert the value into the BST. Return the root of the BST after the insertion. It is guaranteed that the new value does not exist in the original BST.

### Example

```
Input:  root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]

      4                4
     / \              / \
    2   7     →      2   7
   / \              / \ /
  1   3            1  3 5
```

---

# 💡 Intuition & Approach

## Iterative BST Insertion

A new node in a BST is always inserted as a **leaf**. Walk down the tree using BST property until you find the correct empty spot.

1. If tree is empty, return a new node.
2. Walk down: go left if `val < curr`, go right otherwise.
3. When the next position is null, insert the new node there.

```
Insert 5 into [4,2,7,1,3]:
  4 → 5 > 4, go right
  7 → 5 < 7, go left → null, insert here!
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(H) — where H is the height of the BST
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {

        if (!root)
            return new TreeNode(val);

        TreeNode* curr = root;

        while (true) {

            if (val < curr->val) {

                if (!curr->left) {
                    curr->left = new TreeNode(val);
                    break;
                }

                curr = curr->left;
            }

            else {

                if (!curr->right) {
                    curr->right = new TreeNode(val);
                    break;
                }

                curr = curr->right;
            }
        }

        return root;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty tree → create and return new root

✅ Insert smaller than all → goes to leftmost leaf

✅ Insert larger than all → goes to rightmost leaf

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
BST insertion always adds a LEAF node.
Walk down using BST property, find the null spot, insert.
```

## Common Mistakes

❌ Trying to insert in the middle of the tree — new nodes are always leaves.

❌ Not handling empty tree case.

---

## Related Problems

- 700. Search in a Binary Search Tree
- 450. Delete Node in a BST
- 98. Validate Binary Search Tree

---

# 🧠 Revision Notes

## Pattern Recognition

BST insert follows the same path as BST search, but instead of returning null when not found, you create a new node at that position.
