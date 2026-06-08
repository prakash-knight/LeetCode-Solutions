# 141. Linked List Cycle

[Link to LeetCode Problem](https://leetcode.com/problems/linked-list-cycle/)

---

## 📝 Problem Statement

Given `head`, the head of a linked list, determine if the linked list has a **cycle** in it.

Return `true` if there is a cycle, otherwise return `false`.

### Example

```cpp
Input: head = [3, 2, 0, -4], pos = 1
Output: true
// Tail connects back to index 1 — cycle exists

Input: head = [1, 2], pos = -1
Output: false
// No cycle
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Use a `HashSet` to store visited nodes. If we visit a node already in the set, a cycle exists.

### Why is it inefficient?

```cpp
O(n) time + O(n) space
```

Extra memory used — not ideal when constant space is possible.

---

## 2. Optimized Approach (Floyd's Cycle Detection)

### Pattern Used

```cpp
Floyd's Tortoise & Hare — Fast & Slow Pointers
```

### Main Idea

- `fast` starts one step ahead (`head->next`).
- `slow` starts at `head`.
- If `fast` ever equals `slow`, a cycle exists.
- If `fast` reaches `NULL`, no cycle.

Starting `fast` one step ahead avoids an immediate false-positive on `fast == slow` at the initial position.

---

## Step-by-Step Logic

1. Initialize:

```cpp
fast = head ? head->next : NULL
slow = head
```

2. While `fast != NULL && fast->next != NULL`:
   - If `fast == slow` → return `true`
   - Advance: `fast = fast->next->next`, `slow = slow->next`

3. Return `false`.

---

### Dry Run

```cpp
List: 3 → 2 → 0 → -4 → (back to 2)

Start:  slow=3, fast=2
Step 1: slow=2, fast=0  (fast: 2→0)
Step 2: slow=0, fast=2  (fast: 0→-4→2)
Step 3: slow=-4, fast=-4 → fast==slow → return true ✅

List: 1 → 2 → NULL
Start:  slow=1, fast=2
Step 1: fast->next = NULL → exit loop → return false ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Fast pointer catches slow pointer within one loop cycle.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only two pointers — no hash set or extra memory.

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
    bool hasCycle(ListNode* head) {
        ListNode* fast = head ? head->next : NULL;
        ListNode* slow = head;

        while (fast != NULL && fast->next != NULL) {
            if (fast == slow)
                return true;

            fast = fast->next->next;
            slow = slow->next;
        }
        return false;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty list

```cpp
head = NULL → return false
```

---

✅ Single node, no self-loop

```cpp
head = [1], pos = -1 → return false
```

---

✅ Single node, self-loop

```cpp
head = [1], pos = 0
// fast = head->next = head → cycle detected immediately
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Starting `fast = head->next` (instead of `head`) avoids the spurious `fast == slow` match at the very start before any movement occurs.

---

## Common Mistakes

❌ Starting both at `head` and checking equality before moving — returns `true` immediately for any non-null list.

❌ Forgetting null guard `head ? head->next : NULL` — crashes when `head` is `NULL`.

---

## Related Problems

- 142 — Linked List Cycle II (find cycle start)
- 876 — Middle of the Linked List
- 287 — Find the Duplicate Number (cycle detection on array)

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Detect a cycle in a linked list
- O(1) space constraint

Think:

```cpp
Floyd's Cycle Detection:
fast = head->next, slow = head
If fast == slow → cycle exists
```

---
