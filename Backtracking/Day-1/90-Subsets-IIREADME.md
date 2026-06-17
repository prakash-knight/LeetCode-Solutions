# 90. Subsets II

[Link to LeetCode Problem](https://leetcode.com/problems/subsets-ii/)

---

## 📝 Problem Statement

Given an integer array `nums` that **may contain duplicates**, return all possible subsets (the power set).

The solution set must **not contain duplicate subsets**. Return the solution in any order.

### Example

```
Input:  nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
```

---

# 💡 Intuition & Approach

## Key Difference from #78 (Subsets)

In #78 all elements are unique — any take/leave tree gives unique subsets.

Here, duplicates exist. If we apply the same approach:
- Taking `2` (index 1) and leaving `2` (index 2) gives `[1,2]`
- Taking `2` (index 2) and leaving `2` (index 1) also gives `[1,2]`

→ **Duplicate subsets!**

## Fix: Sort + Skip Duplicates on the "Leave" Branch

**Sort** the array first so duplicates are adjacent.

When we **don't take** `nums[i]`, we skip ALL consecutive copies of `nums[i]` before the next recursive call.

Why only on "leave"? If we **take** `nums[i]`, the next call handles remaining duplicates naturally in sequence. But if we **skip** `nums[i]`, we must skip all its copies too — otherwise different "entry points" into the same value generate the same subset.

### Example: [1, 2, 2]

```
i=0 (1):
  Take 1 → recurse on [2,2]
  Leave 1 → recurse on [2,2]  (no skip needed, 1 is unique)

i=1 (2):
  Take 2 → recurse on [2]
  Leave 2 → skip idx to 3 (skip nums[2]=2 since == nums[1]=2)
            recurse on [] → records []

i=2 (2):
  Take 2 → records [2,2] (if parent took first 2)
  Leave 2 → records [] / [1] / etc.
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(2ⁿ × n)
```

- At most 2ⁿ subsets
- Each subset copy costs O(n)

## Space Complexity

```
O(n)
```

- Recursion depth = n

---

# 💻 Code

```cpp
class Solution {
public:
    void solve(vector<int>& nums, int i,
               vector<vector<int>>& ans,
               vector<int>& temp) {

        if (i == nums.size()) {
            ans.push_back(temp);
            return;
        }

        // Take nums[i]
        temp.push_back(nums[i]);
        solve(nums, i + 1, ans, temp);
        temp.pop_back();

        // Skip all duplicates of nums[i]
        int idx = i + 1;
        while (idx < nums.size() && nums[idx] == nums[i])
            idx++;

        // Not take (jump past all duplicates)
        solve(nums, idx, ans, temp);
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // MUST sort first

        vector<vector<int>> ans;
        vector<int> temp;
        solve(nums, 0, ans, temp);
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ All elements same → `[[],[1],[1,1],[1,1,1]]` for `[1,1,1]`

✅ No duplicates → works exactly like #78

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Sort → Skip duplicates ONLY on the "leave/not-take" branch
```

## Common Mistakes

❌ Forgetting to **sort** before recursing — duplicates won't be adjacent, so skipping won't work.

❌ Skipping duplicates on both branches — this incorrectly removes valid subsets.

---

## Related Problems

- 78. Subsets (no duplicates version)
- 40. Combination Sum II (same skip-duplicates trick)
- 47. Permutations II

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Generate all subsets from array **with duplicates**
- No duplicate subsets in output

Think:

```
Sort + Skip Duplicates on "Not-Take" Branch
```
