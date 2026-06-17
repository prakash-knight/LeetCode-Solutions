# 47. Permutations II

[Link to LeetCode Problem](https://leetcode.com/problems/permutations-ii/)

---

## 📝 Problem Statement

Given a collection of numbers `nums` that **might contain duplicates**, return all possible unique permutations in **any order**.

### Example

```
Input:  nums = [1,1,2]
Output: [[1,1,2],[1,2,1],[2,1,1]]
```

---

# 💡 Intuition & Approach

## Key Difference from #46 (Permutations)

In #46 all elements are distinct — any permutation is unique by definition.

Here, duplicates exist. E.g., swapping the two `1`s in `[1,1,2]` gives the same arrangement.

## Approach Used: Set-based Deduplication

Apply the same recursion as #46 (visited-index map), but collect results in a `set<vector<int>>` which **automatically deduplicates**.

At the end, transfer the set contents into a `vector<vector<int>>` to return.

### Why this works

`set` stores only unique sorted sequences. Two identical permutations map to the same set entry, so only one survives.

### Why this is not optimal

Inserting a vector of length n into a set costs **O(n log(n!))** per insertion. A better approach:
- Sort the array
- At each recursion level, skip choosing a value if it equals the previously chosen value at that level

But the set approach is simpler to implement and reason about.

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(n! × n log(n!))
```

- n! permutations explored
- Each set insertion costs O(n log(n!))

## Space Complexity

```
O(n! × n)
```

- All permutations stored in the set

---

# 💻 Code

```cpp
class Solution {
public:
    vector<int> temp;
    set<vector<int>> ans;
    unordered_map<int, int> mp;

    void solver(vector<int>& nums) {
        if (temp.size() == nums.size()) {
            ans.insert(temp);    // set handles deduplication
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (mp.find(i) != mp.end())
                continue;

            mp[i] = i;
            temp.push_back(nums[i]);
            solver(nums);
            mp.erase(i);
            temp.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        solver(nums);

        vector<vector<int>> ans1;
        for (auto x : ans)
            ans1.push_back(x);

        return ans1;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ All elements same → `[[1,1,1]]` for `[1,1,1]`

✅ No duplicates → works exactly like #46

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Same as #46 + use set<vector<int>> to auto-deduplicate
```

## Better Trick (Optimal)

```
Sort + skip same value if already used at this level
```

```cpp
// Inside the for loop after marking used:
if (i > 0 && nums[i] == nums[i-1] && !visited[i-1])
    continue;
```

## Common Mistakes

❌ Using `set` approach for large inputs — TLE risk due to expensive insertions.

❌ Forgetting to convert `set` back to `vector` before returning.

---

## Related Problems

- 46. Permutations (no duplicates version)
- 90. Subsets II (same "skip duplicate" concept)
- 40. Combination Sum II

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- All arrangements with duplicates
- Unique permutations only

Think:

```
Permutation Backtracking + Dedup (set OR sort+skip)
```
