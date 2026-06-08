# 876. Middle of the Linked List

[Link to LeetCode Problem](https://leetcode.com/problems/middle-of-the-linked-list/)

---

## 📝 Problem Statement

Given the `head` of a singly linked list, return the **middle node** of the linked list.

If there are two middle nodes, return the **second middle node**.

### Example

```cpp
Input: head = [1, 2, 3, 4, 5]
Output: [3, 4, 5]   // Node with value 3

Input: head = [1, 2, 3, 4, 5, 6]
Output: [4, 5, 6]   // Second middle node (value 4)
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Count total nodes, then traverse to `count/2`.

### Why is it inefficient?

```cpp
O(n) time but requires two passes
```

Two traversals when one is sufficient.

---

## 2. Optimized Approach (Fast & Slow Pointer)

### Pattern Used

```cpp
Floyd's Tortoise & Hare — Two-pointer technique
```

### Main Idea

Use two pointers:
- `fast` moves **two steps** at a time.
- `slow` moves **one step** at a time.

When `fast` reaches the end, `slow` is at the middle.

---

## Step-by-Step Logic

1. Initialize:

```cpp
fast = head, slow = head
```

2. While `fast != nullptr && fast->next != nullptr`:
   - `fast = fast->next->next`
   - `slow = slow->next`

3. Return `slow`.

---

### Dry Run

```cpp
List: 1 → 2 → 3 → 4 → 5

Start:  slow=1, fast=1
Step 1: slow=2, fast=3
Step 2: slow=3, fast=5
fast->next = NULL → stop

Result: slow = 3 ✅

List: 1 → 2 → 3 → 4 → 5 → 6

Start:  slow=1, fast=1
Step 1: slow=2, fast=3
Step 2: slow=3, fast=5
Step 3: slow=4, fast=NULL → stop

Result: slow = 4 (second middle) ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Single pass; `fast` covers the list in `n/2` iterations.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only two pointers — no extra memory.

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
    ListNode* middleNode(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }

        return slow;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single node

```cpp
head = [1] → return [1]
```

---

✅ Two nodes (even length)

```cpp
[1 → 2] → return 2 (second middle)
```

---

✅ Odd-length list

```cpp
[1 → 2 → 3] → return 2 (true middle)
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

The condition `fast != nullptr && fast->next != nullptr` is critical:
- `fast != nullptr` — prevents null dereference on odd-length lists.
- `fast->next != nullptr` — prevents `fast->next->next` from crashing on even-length lists.

---

## Common Mistakes

❌ Checking only `fast->next != nullptr` — crashes on odd-length list when `fast` itself is NULL.

❌ Starting `fast = head->next` — gives the first middle for even lists instead of second.

---

## Related Problems

- 206 — Reverse Linked List
- 234 — Palindrome Linked List
- 141 — Linked List Cycle

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Find the middle of a linked list
- No extra space allowed

Think:

```cpp
Fast & Slow pointers: fast moves 2x, slow moves 1x
When fast hits end → slow is at middle
```

---
