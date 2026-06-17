# 216. Combination Sum III

[Link to LeetCode Problem](https://leetcode.com/problems/combination-sum-iii/)

---

## 📝 Problem Statement

Find all valid combinations of `k` numbers that sum up to `n` such that:
- Only numbers `1` through `9` are used.
- Each number is used **at most once**.
- Return a list of all possible valid combinations.

### Example

```
Input:  k = 3, n = 7
Output: [[1,2,4]]

Input:  k = 3, n = 9
Output: [[1,2,6],[1,3,5],[2,3,4]]
```

---

# 💡 Intuition & Approach

## Combination with Fixed Size and Fixed Sum

This is a constrained combination problem:
- **Pool**: digits 1–9 only
- **Constraint 1**: exactly `k` numbers chosen
- **Constraint 2**: they must sum to `n`
- **No reuse**: each digit used at most once

## Start Index to Avoid Reuse

Use a `st` (start) variable. At each level, iterate from `st` to `9`. This ensures:
- We never pick the same digit twice
- We never pick a smaller digit after a larger one (no duplicate combinations)

## Pruning

- If `temp.size() == k` → check if `sum == n` → record or discard
- If `sum > n` → prune early (no point continuing)

### Trace for k=3, n=7

```
solve(k=3, n=7, sum=0, st=1)
  pick 1 → solve(sum=1, st=2)
    pick 2 → solve(sum=3, st=3)
      pick 3 → solve(sum=6, st=4) → size=3, sum≠7 ✗
      pick 4 → solve(sum=7, st=5) → size=3, sum=7 ✅ [1,2,4]
      pick 5 → solve(sum=8, st=6) → sum>7, prune ✗
    pick 3 → solve(sum=4, st=4)
      pick 4 → solve(sum=8) → sum>7 ✗
    ...
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(C(9, k) × k)
```

- At most C(9,k) valid combinations
- Building each combination costs O(k)

## Space Complexity

```
O(k)
```

- `temp` holds at most k elements
- Recursion depth = k

---

# 💻 Code

```cpp
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> temp;

    void solve(int k, int n, int sum, int st) {
        if (temp.size() == k) {
            if (sum == n)
                ans.push_back(temp);
            return;
        }
        if (sum > n)
            return;

        for (int i = st; i <= 9; i++) {
            temp.push_back(i);
            solve(k, n, sum + i, i + 1);   // i+1: no reuse
            temp.pop_back();                // backtrack
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        solve(k, n, 0, 1);
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ No valid combination → returns `[]`

✅ `k=1, n=5` → `[[5]]`

✅ `k=9, n=45` → `[[1,2,3,4,5,6,7,8,9]]` (only one combination)

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
For-loop from start index + prune when sum > n
```

Use `i + 1` as the next start to prevent reusing the same digit.

## Difference from Combination Sum I & II

| Problem | Pool | Reuse | Duplicates |
|---|---|---|---|
| 39. Combination Sum | 1–any | ✅ Yes | No |
| 40. Combination Sum II | Given array | ❌ No | Yes |
| **216. Combination Sum III** | **1–9 fixed** | **❌ No** | **No** |

## Common Mistakes

❌ Starting loop from `1` every time instead of `st` → picks same digit multiple times.

❌ Checking `sum == n` after the loop instead of at the base case → misses the condition.

---

## Related Problems

- 39. Combination Sum
- 40. Combination Sum II
- 78. Subsets
- 77. Combinations

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Choose exactly `k` numbers
- From a fixed range (1–9)
- That sum to a target
- No repeats

Think:

```
Start Index + Fixed-size backtracking with sum constraint
```
