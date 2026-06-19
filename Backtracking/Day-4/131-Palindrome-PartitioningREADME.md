# 131. Palindrome Partitioning

[Link to LeetCode Problem](https://leetcode.com/problems/palindrome-partitioning/)

---

## 📝 Problem Statement

Given a string `s`, partition it such that **every substring** of the partition is a **palindrome**. Return all possible palindrome partitionings.

### Example

```
Input:  s = "aab"
Output: [["a","a","b"],["aa","b"]]

Input:  s = "a"
Output: [["a"]]
```

---

# 💡 Intuition & Approach

## Cut at Every Valid Palindrome

At each index `idx`, try all substrings `s[idx..i]` for `i` from `idx` to end:
- If `s[idx..i]` is a palindrome → add it to `temp` and recurse from `i+1`
- If not → skip (continue)
- After recursion → backtrack (pop from `temp`)

Base case: `idx >= s.size()` → we've processed the whole string → push `temp` to `ans`.

## Palindrome Check

Two-pointer: shrink from both ends `(i, e)` comparing `s[i]` and `s[e]`.

### Trace for "aab"

```
solve(idx=0)
  s[0..0]="a" → palindrome ✅
    solve(idx=1)
      s[1..1]="a" → palindrome ✅
        solve(idx=2)
          s[2..2]="b" → palindrome ✅
            solve(idx=3) → BASE → push ["a","a","b"]
      s[1..2]="ab" → NOT palindrome ✗
  s[0..1]="aa" → palindrome ✅
    solve(idx=2)
      s[2..2]="b" → palindrome ✅
        solve(idx=3) → BASE → push ["aa","b"]
  s[0..2]="aab" → NOT palindrome ✗
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(n × 2ⁿ)
```

- At most 2ⁿ partitions (each position is a cut or not)
- Palindrome check costs O(n) per substring

## Space Complexity

```
O(n)
```

- Recursion depth = n (length of string)
- `temp` holds at most n substrings

---

# 💻 Code

```cpp
class Solution {
public:
    vector<vector<string>> ans;
    vector<string> temp;

    bool ispal(string s, int i, int e) {
        while (i <= e) {
            if (s[i] != s[e])
                return false;
            i++; e--;
        }
        return true;
    }

    void solve(string s, int idx) {
        if (idx >= s.size()) {
            ans.push_back(temp);
            return;
        }

        for (int i = idx; i < s.size(); i++) {
            if (ispal(s, idx, i)) {
                temp.push_back(s.substr(idx, i - idx + 1));
            } else {
                continue;
            }
            solve(s, i + 1);
            temp.pop_back();  // backtrack
        }
    }

    vector<vector<string>> partition(string s) {
        solve(s, 0);
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single character → `[["a"]]` (every single char is a palindrome)

✅ All identical characters like `"aaa"` → multiple valid partitions

✅ No valid partition beyond single chars → still works (picks one char at a time)

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
For-loop from current idx + palindrome check before branching
```

Only branch (recurse) when the current substring IS a palindrome — otherwise `continue`.

## Common Mistakes

❌ Recursing even when substring is not a palindrome → wrong results.

❌ Forgetting `temp.pop_back()` after recursion → `temp` grows without cleanup.

❌ Using `s.substr(idx, i)` instead of `s.substr(idx, i - idx + 1)` → wrong length.

---

## Related Problems

- 132. Palindrome Partitioning II (DP for minimum cuts)
- 5. Longest Palindromic Substring
- 17. Letter Combinations of a Phone Number

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Partition a string into all valid subsets
- Where validity = some property (palindrome, length, etc.)

Think:

```
Index-based backtracking: try all cuts from current position, validate, recurse
```
