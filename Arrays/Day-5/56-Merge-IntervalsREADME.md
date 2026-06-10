# 56. Merge Intervals

[Link to LeetCode Problem](https://leetcode.com/problems/merge-intervals/)

---

## 📝 Problem Statement

Given an array of `intervals` where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals, and return an array of the **non-overlapping intervals** that cover all the intervals in the input.

### Example

```cpp
Input:  intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]

Input:  intervals = [[1,4],[4,5]]
Output: [[1,5]]  // touching intervals are merged
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Repeatedly compare all pairs and merge overlapping ones.

### Why is it inefficient?

```cpp
O(n²)
```

Multiple passes needed.

---

## 2. Optimized Approach (Sort + Linear Scan)

### Pattern Used

```cpp
Sort by start time → Greedily merge with last interval in result
```

### Main Idea

After sorting by start time, any overlapping interval must start at or before the end of the previous interval. We scan linearly and either extend the last interval's end or start a new one.

---

## Step-by-Step Logic

1. Sort `intervals` by start time.
2. Push `intervals[0]` into `ans`.
3. For each subsequent interval:
   - If its start ≤ last interval's end in `ans`:
     - Merge by updating last interval's end = `max(last.end, current.end)`.
   - Else:
     - Push the current interval as a new entry.

---

### Dry Run

```cpp
intervals = [[1,3],[2,6],[8,10],[15,18]]  (already sorted)

ans = [[1,3]]

i=1: [2,6] → 2 <= 3 → merge → ans = [[1,6]]
i=2: [8,10] → 8 > 6 → push → ans = [[1,6],[8,10]]
i=3: [15,18] → 15 > 10 → push → ans = [[1,6],[8,10],[15,18]] ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n log n)
```

Because:
- Sorting dominates; the scan is O(n).

---

## Space Complexity

```cpp
O(n)
```

Because:
- Output array stores up to `n` intervals.

---

# 💻 Code

```cpp
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& in) {
        vector<vector<int>> ans;
        sort(in.begin(), in.end());
        ans.push_back(in[0]);

        for (int i = 1; i < in.size(); i++) {
            int n = ans.size();
            if (in[i][0] <= ans.back()[1]) {
                ans[n - 1][1] = max(ans[n - 1][1], in[i][1]);
            } else
                ans.push_back(in[i]);
        }
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Touching intervals (end == start of next):

```cpp
[[1,4],[4,5]]
// Output: [[1,5]]  → 4 <= 4, so merged
```

---

✅ One interval fully inside another:

```cpp
[[1,10],[2,5]]
// Output: [[1,10]]  → max(10,5) = 10
```

---

✅ Single interval:

```cpp
[[1,5]]
// Output: [[1,5]]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

**Sort first** — this guarantees that any overlapping interval appears right after the one it overlaps with. Then a single greedy pass is enough.

Use `ans.back()[1]` to always reference the **last merged interval's end**.

---

## Common Mistakes

❌ Not using `max()` when updating the end — a smaller interval may be fully contained, so its end shouldn't shrink the current end.

❌ Not sorting the input — unsorted input breaks the greedy merge assumption.

---

## Related Problems

- 57 — Insert Interval
- 435 — Non-overlapping Intervals
- 452 — Minimum Number of Arrows to Burst Balloons

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Merge/consolidate overlapping ranges
- Cover all intervals with minimum groups

Think:

```cpp
Sort by start → Greedy merge with last interval (extend end or push new)
```

---
