# 21. Merge Two Sorted Lists

[Link to LeetCode Problem](https://leetcode.com/problems/merge-two-sorted-lists/)

---

## 📝 Problem Statement

You are given the heads of two sorted linked lists `list1` and `list2`.

Merge the two lists into one **sorted** list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

### Example

```cpp
Input: list1 = [1, 2, 4], list2 = [1, 3, 4]
Output: [1, 1, 2, 3, 4, 4]

Input: list1 = [], list2 = []
Output: []
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Collect all values, sort them, and build a new linked list.

### Why is it inefficient?

```cpp
O(n log n) time + O(n) space
```

Sorting is unnecessary since both lists are already sorted.

---

## 2. Optimized Approach (Dummy Node + Two Pointers)

### Pattern Used

```cpp
Dummy Head + Merge technique
```

### Main Idea

Use a **dummy head node** to avoid special-casing the first node. Maintain a `head` pointer that always points to the last node of the merged list. At each step, pick the smaller of the two current nodes.

---

## Step-by-Step Logic

1. Create `dummy = new ListNode(0)`, `head = dummy`.

2. While both `list1` and `list2` are non-null:
   - If `list1->val <= list2->val`: attach `list1`, advance `list1`.
   - Else: attach `list2`, advance `list2`.
   - Advance `head = head->next`.

3. Attach the remaining non-null list.

4. Return `dummy->next`.

---

### Dry Run

```cpp
list1: 1 → 2 → 4
list2: 1 → 3 → 4

Step 1: 1<=1 → attach list1(1), list1=2
Step 2: 1<=2 → attach list2(1), list2=3
Step 3: 2<=3 → attach list1(2), list1=4
Step 4: 3<=4 → attach list2(3), list2=4
Step 5: 4<=4 → attach list1(4), list1=NULL
→ list1 exhausted, attach remaining list2(4)

Result: 1 → 1 → 2 → 3 → 4 → 4 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(m + n)
```

Because:
- Each node from both lists is visited exactly once.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only a dummy node and pointer variables — nodes are relinked, not copied.

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(0);
        ListNode* head = dummy;

        while (list1 && list2) {
            if (list1->val <= list2->val) {
                head->next = list1;
                list1 = list1->next;
            } else {
                head->next = list2;
                list2 = list2->next;
            }
            head = head->next;
        }

        if (list1)
            head->next = list1;
        else
            head->next = list2;

        return dummy->next;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Both lists empty

```cpp
list1 = [], list2 = [] → return NULL
```

---

✅ One list empty

```cpp
list1 = [1,2,3], list2 = [] → return list1 directly
```

---

✅ All elements of one list smaller

```cpp
list1 = [1,2,3], list2 = [4,5,6]
→ 1→2→3→4→5→6
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

The **dummy node** eliminates the need to handle the first element as a special case — `dummy->next` is always the merged list's head regardless of which list contributes the first node.

---

## Common Mistakes

❌ Forgetting to attach the remaining tail — when one list runs out, the other's remaining nodes must be directly linked (not traversed one by one).

❌ Using `<` instead of `<=` — both work for correctness but `<=` keeps `list1`'s nodes first on ties (stable merge).

---

## Related Problems

- 23 — Merge K Sorted Lists
- 148 — Sort List
- 88 — Merge Sorted Array

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Merge sorted linked lists
- Combine two ordered sequences

Think:

```cpp
Dummy head + two pointers
Pick smaller node at each step
Attach leftover tail at end
```

---
