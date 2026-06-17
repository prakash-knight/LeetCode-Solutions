# 78. Subsets

[Link to LeetCode Problem](https://leetcode.com/problems/subsets/)

---

## 📝 Problem Statement

Given an integer array `nums` of **unique** elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in **any order**.

### Example

```
Input:  nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

---

# 💡 Intuition & Approach

## Binary Choice Tree (Take / Leave)

For every element, we have exactly **two choices**:
- **Take** it → add to current subset, move to next index
- **Leave** it → skip it, move to next index

When we reach index `i == nums.size()`, we've decided for all elements — record the current subset.

### Recursion Tree for [1,2,3]

```
                    []
           /                 \
         [1]                  []
       /     \             /      \
    [1,2]   [1]          [2]      []
    /   \   /  \        /   \    /   \
[1,2,3][1,2][1,3][1] [2,3][2] [3]  []
```

Total leaves = 2³ = **8 subsets** ✅

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(2ⁿ × n)
```

- 2ⁿ subsets generated
- Copying each subset to result costs O(n)

## Space Complexity

```
O(n)
```

- Recursion depth = n (height of tree)
- `ans` vector used for backtracking (reused, not copied)

---

# 💻 Code

```cpp
class Solution {
public:
    void solver(vector<int>& nums, int i, vector<int>& ans,
                vector<vector<int>>& aks) {

        if (i >= nums.size()) {
            aks.push_back(ans);   // base case: record current subset
            return;
        }

        // Take nums[i]
        ans.push_back(nums[i]);
        solver(nums, i + 1, ans, aks);

        // Leave nums[i] (backtrack)
        ans.pop_back();
        solver(nums, i + 1, ans, aks);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> ans;
        vector<vector<int>> aks;
        solver(nums, 0, ans, aks);
        return aks;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single element → `[[], [1]]`

✅ Empty array → `[[]]`

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Two recursive calls per element:
1. Push → recurse → pop (**backtrack**)
2. Recurse without pushing

## Common Mistakes

❌ Forgetting `pop_back()` after the "take" branch — this corrupts the `ans` vector for the "leave" branch.

---

## Related Problems

- 90. Subsets II (with duplicates)
- 46. Permutations
- 78 → 90 → 46 → 47 progression

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Generate all subsets / power set
- No duplicates in input

Think:

```
Binary Choice Backtracking (Take / Leave)
```
