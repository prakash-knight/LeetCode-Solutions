# 206. Reverse Linked List

[Link to LeetCode Problem](https://leetcode.com/problems/reverse-linked-list/)

---

## 📝 Problem Statement

Given the `head` of a singly linked list, reverse the list, and return the reversed list.

### Example

```cpp
Input: head = [1, 2, 3, 4, 5]
Output: [5, 4, 3, 2, 1]
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Store all values in an array, reverse it, and rebuild the list.

### Why is it inefficient?

```cpp
O(n) time + O(n) space
```

Uses extra memory — not ideal when in-place reversal is possible.

---

## 2. Optimized Approach (Iterative In-Place)

### Pattern Used

```cpp
Three-pointer technique — prev, curr, forw
```

### Main Idea

Traverse the list while reversing each `next` pointer to point backward:
1. Save the next node (`forw = curr->next`).
2. Reverse the current pointer (`curr->next = prev`).
3. Advance both `prev` and `curr` forward.

---

## Step-by-Step Logic

1. Initialize:

```cpp
curr = head, prev = NULL, forw = NULL
```

2. While `curr != NULL`:
   - Save `forw = curr->next`
   - Reverse: `curr->next = prev`
   - Move: `prev = curr`, `curr = forw`

3. Return `prev` — it now points to the new head.

---

### Dry Run

```cpp
List: 1 → 2 → 3 → NULL

Step 1: forw=2, 1→NULL, prev=1, curr=2
Step 2: forw=3, 2→1, prev=2, curr=3
Step 3: forw=NULL, 3→2, prev=3, curr=NULL

Result: 3 → 2 → 1 → NULL ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Single pass through all `n` nodes.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only three pointers used — no extra data structures.

---

# 💻 Code

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* curr = head;
        ListNode* prev = NULL;
        ListNode* forw = NULL;

        while (curr != NULL) {
            forw = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forw;
        }

        return prev;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty list

```cpp
head = NULL → return NULL
```

---

✅ Single node

```cpp
head = [1] → return [1]
```

---

✅ Two nodes

```cpp
[1 → 2] → [2 → 1]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Always save `curr->next` **before** overwriting it — otherwise you lose the rest of the list.

---

## Common Mistakes

❌ Forgetting `forw = curr->next` before reversing — causes loss of the rest of the list.

❌ Returning `curr` instead of `prev` — `curr` is `NULL` at loop end; `prev` is the new head.

---

## Related Problems

- 92 — Reverse Linked List II
- 234 — Palindrome Linked List
- 25 — Reverse Nodes in k-Group

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Reverse a linked list (full or partial)
- In-place pointer manipulation

Think:

```cpp
Three pointers: prev = NULL, curr = head, forw = NULL
Reverse curr->next = prev, then advance both
```

---
