# 23. Merge k Sorted Lists

[Link to LeetCode Problem](https://leetcode.com/problems/merge-k-sorted-lists/)

---

## 📝 Problem Statement

You are given an array of `k` linked-lists, each linked-list is sorted in ascending order. Merge all the linked-lists into one sorted linked-list and return it.

### Example

```
Input:  lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]

List 1: 1 → 4 → 5
List 2: 1 → 3 → 4
List 3: 2 → 6

Merged: 1 → 1 → 2 → 3 → 4 → 4 → 5 → 6
```

---

# 💡 Intuition & Approach

## Multimap (Sorted Insertion)

Use a `multimap<int, ListNode*>` to insert all nodes sorted by value. Then iterate through the map to build the merged list.

1. Traverse all lists, insert every `(val, node)` pair into the multimap.
2. Multimap keeps entries sorted by key automatically.
3. Iterate the multimap, chaining nodes in order.

```
Insert all: {1:node, 1:node, 2:node, 3:node, 4:node, 4:node, 5:node, 6:node}
Chain in order → merged list
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N log N) — N total nodes, each insertion into multimap is O(log N)
```

## Space Complexity

```
O(N) — multimap stores all nodes
```

---

# 💻 Code

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        multimap<int, ListNode*> mp;
        for (int i = 0; i < lists.size(); i++) {
            ListNode* ptr = lists[i];
            while (ptr) {
                mp.insert({ptr->val, ptr});
                ptr = ptr->next;
            }
        }
        ListNode* root = new ListNode();
        ListNode* dummy = root;

        while (!mp.empty()) {
            auto it = mp.begin();
            ListNode* node = it->second;

            dummy->next = node;
            dummy = dummy->next;

            mp.erase(it);
            dummy->next = nullptr;
        }

        return root->next;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty lists array → return nullptr

✅ Lists containing null entries → skipped in traversal

✅ All lists empty → empty result

✅ Single list → returned as-is

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Multimap auto-sorts entries by key.
Insert all nodes, then chain them in sorted order.
Alternative: Use a min-heap (priority_queue) for O(N log k) approach.
```

## Common Mistakes

❌ Forgetting to set `dummy->next = nullptr` → creates cycles.

❌ Not handling empty lists in the input array.

---

## Related Problems

- 21. Merge Two Sorted Lists
- 264. Ugly Number II
- 378. Kth Smallest Element in a Sorted Matrix

---

# 🧠 Revision Notes

## Pattern Recognition

For merging k sorted sequences:

```
Min-Heap approach: O(N log k) — push heads, pop min, push next
Multimap approach: O(N log N) — insert all, iterate in order
Divide & Conquer: O(N log k) — merge pairs recursively
```
