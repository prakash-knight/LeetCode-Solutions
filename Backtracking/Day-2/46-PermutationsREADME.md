# 46. Permutations

[Link to LeetCode Problem](https://leetcode.com/problems/permutations/)

---

## 📝 Problem Statement

Given an array `nums` of **distinct** integers, return all possible permutations. You can return the answer in **any order**.

### Example

```
Input:  nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

---

# 💡 Intuition & Approach

## Difference from Subsets

In Subsets we move **forward** (index increases). In Permutations, **every position** can pick from **all unused** elements — order matters.

## Visited Map Approach

Use an `unordered_map<int, int> mp` to track which **indices** are already placed in `temp`.

At each recursion level:
- Iterate over ALL indices `0` to `n-1`
- If index `idx` is already used (in `mp`) → skip
- Otherwise: mark used → push → recurse → pop → unmark (**backtrack**)

When `temp.size() == nums.size()` → all elements placed → record permutation.

### Recursion Tree for [1,2,3] (partial)

```
                     []
         /           |           \
       [1]          [2]          [3]
      /   \        /   \        /   \
  [1,2] [1,3]  [2,1] [2,3]  [3,1] [3,2]
    |     |      |     |      |     |
[1,2,3][1,3,2][2,1,3][2,3,1][3,1,2][3,2,1]
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(n! × n)
```

- n! permutations generated
- Copying each permutation costs O(n)

## Space Complexity

```
O(n)
```

- Recursion depth = n
- `mp` and `temp` each hold at most n elements

---

# 💻 Code

```cpp
class Solution {
public:
    void solve(vector<int>& nums, vector<int>& temp,
               unordered_map<int, int>& mp,
               vector<vector<int>>& ans) {

        if (temp.size() == nums.size()) {
            ans.push_back(temp);   // all elements placed
            return;
        }

        for (int idx = 0; idx < nums.size(); idx++) {
            if (mp[idx]) continue;    // already used

            mp[idx] = 1;              // mark used
            temp.push_back(nums[idx]);
            solve(nums, temp, mp, ans);
            temp.pop_back();          // backtrack
            mp.erase(idx);            // unmark
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> temp;
        unordered_map<int, int> mp;
        vector<vector<int>> ans;
        solve(nums, temp, mp, ans);
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single element → `[[1]]`

✅ Two elements → `[[1,2],[2,1]]`

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Track used **indices** (not values) in a visited map.
Each level of recursion iterates ALL indices and picks one that isn't used yet.

## Common Mistakes

❌ Using `mp.count(idx)` vs `mp[idx]` — `mp[idx]` auto-inserts 0 for unseen keys, which works here but can cause confusion. Prefer `mp.count(idx) > 0` for clarity.

❌ Forgetting `mp.erase(idx)` during backtrack — the index stays "used" permanently and prunes valid paths.

---

## Related Problems

- 47. Permutations II (with duplicates)
- 78. Subsets
- 784. Letter Case Permutation

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- All arrangements / orderings
- Every position can use any remaining element
- Distinct inputs

Think:

```
Visited Map + For-loop at each level (Permutation Backtracking)
```
