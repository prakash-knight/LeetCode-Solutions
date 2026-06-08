# 237. Delete Node in a Linked List

[Link to LeetCode Problem](https://leetcode.com/problems/delete-node-in-a-linked-list/)

---

## 📝 Problem Statement

There is a singly-linked list and you are given access to a node to be **deleted** (not the tail, and not the head necessarily). You are **not given access to the head** of the list.

Delete the given node such that:
- The node's value doesn't appear in the linked list.
- The number of nodes decreases by one.
- All values before and after the deleted node remain in the same order.

### Example

```cpp
Input: head = [4, 5, 1, 9], node = 5
Output: [4, 1, 9]
// 5 is deleted

Input: head = [4, 5, 1, 9], node = 1
Output: [4, 5, 9]
```

---

# 💡 Intuition & Approach

## Key Observation

We **cannot** traverse back to find the previous node (no access to head, singly linked). But we don't need to delete `node` itself — we can **overwrite** it with the next node's data, then delete the next node instead.

### Pattern Used

```cpp
Node value copy + skip next
```

### Main Idea

1. Copy the value of `node->next` into `node`.
2. Set `node->next = node->next->next`.

The current node now **appears** deleted from the list's perspective.

---

## Step-by-Step Logic

1. `node->val = node->next->val` — overwrite current node's value.
2. `node->next = node->next->next` — bypass and effectively delete the next node.

---

### Dry Run

```cpp
List: 4 → 5 → 1 → 9, delete node(5)

Step 1: node->val = 1  →  List: 4 → 1 → 1 → 9
Step 2: node->next = node->next->next  →  4 → 1 → 9 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(1)
```

Because:
- Only two pointer operations — no traversal needed.

---

## Space Complexity

```cpp
O(1)
```

Because:
- No extra memory used.

---

# 💻 Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Node before the last node (guaranteed by problem)

```cpp
Problem guarantees: node is not the tail → node->next always exists
```

---

✅ Two-node list, delete first node

```cpp
[1 → 2], delete node(1)
Step 1: node->val = 2  →  [2 → 2]
Step 2: node->next = NULL  →  [2] ✅
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

When you have no access to the previous node — **copy the next node's value** into the current node, then delete the next node. It mimics deletion without needing a predecessor.

---

## Common Mistakes

❌ Trying to traverse back to find the previous node — not possible in a singly linked list without the head.

❌ Forgetting that the problem guarantees `node` is not the tail — `node->next` is always safe to access.

---

## Related Problems

- 19 — Remove Nth Node From End of List
- 203 — Remove Linked List Elements
- 21 — Merge Two Sorted Lists

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Delete a node with only access to that node (not head or prev)

Think:

```cpp
Copy next node's value into current node
Bypass next node: node->next = node->next->next
```

---
