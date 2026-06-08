# 19. Remove Nth Node From End of List

[Link to LeetCode Problem](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)

---

## 📝 Problem Statement

Given the `head` of a linked list, remove the `n`th node from the **end** of the list and return its head.

### Example

```cpp
Input: head = [1, 2, 3, 4, 5], n = 2
Output: [1, 2, 3, 5]
// 4th node (2nd from end) removed

Input: head = [1], n = 1
Output: []
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Count total nodes (`L`), then remove the `(L - n)`th node from the front.

### Why is it inefficient?

```cpp
O(n) time — two passes
```

Works but requires traversing the list twice.

---

## 2. Optimized Approach (Dummy Node + Two Pointers — One Pass)

### Pattern Used

```cpp
Dummy Head + Fast & Slow Pointers with n+1 gap
```

### Main Idea

Create a gap of `n+1` between `fast` and `slow` starting from the dummy node. When `fast` reaches `NULL`, `slow` is exactly at the node **before** the target — enabling clean deletion.

---

## Step-by-Step Logic

1. Create `dummy = new ListNode(0)`, `dummy->next = head`.
2. Initialize `fast = dummy`, `slow = dummy`.
3. Advance `fast` by `n+1` steps.
4. Move both `fast` and `slow` until `fast == NULL`.
5. Delete: `slow->next = slow->next->next`.
6. Return `dummy->next`.

---

### Dry Run

```cpp
List: 1 → 2 → 3 → 4 → 5, n = 2

dummy → 1 → 2 → 3 → 4 → 5

fast advances 3 steps (n+1=3):
fast = dummy(0), advance 1: fast=1
advance 2: fast=2
advance 3: fast=3

Move both until fast=NULL:
Step 1: fast=4, slow=1
Step 2: fast=5, slow=2
Step 3: fast=NULL, slow=3

slow->next = slow->next->next → 3→5 (skip 4)

Result: 1 → 2 → 3 → 5 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Single pass through the list.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only a dummy node and two pointers.

---

# 💻 Code

```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* fast = dummy;
        ListNode* slow = dummy;

        for (int i = 0; i <= n; i++)
            fast = fast->next;

        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        slow->next = slow->next->next;

        return dummy->next;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Remove the head node

```cpp
head = [1, 2, 3], n = 3
// dummy ensures we can update dummy->next
Result: [2, 3]
```

---

✅ Single node list

```cpp
head = [1], n = 1 → return NULL
```

---

✅ Remove last node

```cpp
head = [1, 2, 3], n = 1 → [1, 2]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Advancing `fast` by **`n+1`** steps (not `n`) from the dummy ensures `slow` lands on the **predecessor** of the node to delete — making `slow->next = slow->next->next` safe without needing a separate `prev` pointer.

---

## Common Mistakes

❌ Advancing `fast` only `n` steps — `slow` ends up on the target node itself, not its predecessor.

❌ Not using a dummy node — makes removing the head node a special case requiring extra logic.

---

## Related Problems

- 876 — Middle of the Linked List
- 206 — Reverse Linked List
- 82 — Remove Duplicates from Sorted List II

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Remove kth node from the end
- One-pass solution required

Think:

```cpp
Dummy head + two pointers
Advance fast by (n+1) steps first
Then move both until fast = NULL
slow->next = slow->next->next
```

---
