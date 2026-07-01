# 347. Top K Frequent Elements

[Link to LeetCode Problem](https://leetcode.com/problems/top-k-frequent-elements/)

---

## 📝 Problem Statement

Given an integer array `nums` and an integer `k`, return the `k` most frequent elements. You may return the answer in **any order**.

### Example

```
Input:  nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Frequencies: 1→3, 2→2, 3→1
Top 2: [1, 2]
```

---

# 💡 Intuition & Approach

## Frequency Map + Sort

1. Count frequency of each element using a hash map.
2. Convert map to a vector of `(element, frequency)` pairs.
3. Sort by frequency in descending order.
4. Take the first `k` elements.

```
nums = [1,1,1,2,2,3]
freq: {1:3, 2:2, 3:1}
sorted by freq: [(1,3), (2,2), (3,1)]
top 2: [1, 2]
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N + U log U) — N for counting, U log U for sorting unique elements
where U = number of unique elements
```

## Space Complexity

```
O(U) — hash map + sorted vector
```

---

# 💻 Code

```cpp
class Solution {
public:
    static bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;

        for (auto n : nums) {
            mp[n]++;
        }
        vector<pair<int, int>> res(mp.begin(), mp.end());
        sort(res.begin(), res.end(), cmp);

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            ans.push_back(res[i].first);
        }

        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ k = 1 → return the single most frequent element

✅ All elements same → return that element

✅ All elements unique with k = n → return all

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Count frequencies → sort by frequency → take top k.
Custom comparator sorts pairs by second value (frequency) descending.
```

## Common Mistakes

❌ Sorting by element value instead of frequency.

❌ Forgetting `static` on the comparator function for `sort()`.

---

## Related Problems

- 692. Top K Frequent Words
- 451. Sort Characters By Frequency
- 215. Kth Largest Element in an Array

---

# 🧠 Revision Notes

## Pattern Recognition

For "top k" problems, three approaches:

```
1. Sort: O(N log N) — simplest
2. Min-Heap of size k: O(N log k) — better for large N
3. Bucket Sort: O(N) — optimal, frequency as index
```
