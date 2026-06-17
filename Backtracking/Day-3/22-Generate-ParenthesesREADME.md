# 22. Generate Parentheses

[Link to LeetCode Problem](https://leetcode.com/problems/generate-parentheses/)

---

## 📝 Problem Statement

Given `n` pairs of parentheses, write a function to generate all combinations of **well-formed** parentheses.

### Example

```
Input:  n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
```

---

# 💡 Intuition & Approach

## What Makes Parentheses "Well-Formed"?

At any point in the string:
1. Number of `(` can never exceed `n`
2. Number of `)` can never exceed number of `(`
3. Final string has exactly `n` of each → length `2n`

## Balance Counter Approach (`cnt`)

Track a `cnt` (balance) variable:
- `cnt` **decrements** when we add `(`
- `cnt` **increments** when we add `)`

So `cnt < 0` means more `(` than `)` → it's **safe to add `)`**.

Base case: `s.size() == 2n` and `cnt == 0` → balanced, record it.

Early pruning:
- `left > n` → too many `(`
- `right > n` → too many `)`
- `s.size() > 2n` → overflowed

### Trace for n=2

```
solve("",  left=0, right=0, cnt=0)
  → add "(": solve("(", left=1, right=0, cnt=-1)
      → add "(": solve("((", left=2, right=0, cnt=-2)
          → cnt<0: add ")": solve("(()", left=2, right=1, cnt=-1)
              → cnt<0: add ")": solve("(())", left=2, right=2, cnt=0) ✅
      → cnt<0: add ")": solve("()", left=1, right=1, cnt=0)
          → add "(": solve("()(", left=2, right=1, cnt=-1)
              → cnt<0: add ")": solve("()()", left=2, right=2, cnt=0) ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(4ⁿ / √n)   — Catalan number Cₙ
```

- The number of valid strings is the nth Catalan number
- Each string has length 2n

## Space Complexity

```
O(n)
```

- Maximum recursion depth = 2n (length of string being built)

---

# 💻 Code

```cpp
class Solution {
public:
    vector<string> ans;
    string s = "";

    void solve(int n, vector<string>& ans, string s,
               int left, int right, int cnt) {

        if (cnt == 0 && s.size() == 2 * n) {
            ans.push_back(s);
            return;
        }
        if (left > n || right > n || s.size() > 2 * n)
            return;

        // Always try adding '('
        solve(n, ans, s + "(", left + 1, right, cnt - 1);

        // Add ')' only if there's an unmatched '('
        if (cnt < 0) {
            solve(n, ans, s + ")", left, right + 1, cnt + 1);
        }
    }

    vector<string> generateParenthesis(int n) {
        solve(n, ans, s, 0, 0, 0);
        return ans;
    }
};
```

> **Note on `cnt` direction**: Here `cnt` starts at 0 and goes **negative** when `(` is added. So `cnt < 0` = unmatched open brackets exist = safe to close.
> An equivalent (perhaps more intuitive) formulation uses `open` and `close` counters directly.

---

# 🔍 Edge Cases Handled

✅ `n = 1` → `["()"]`

✅ `n = 0` → `[""]` (empty string is valid)

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Add '(' freely (while left < n)
Add ')' only when there's an unmatched '(' (cnt < 0 in this code)
```

## Common Mistakes

❌ Adding `)` without checking balance → generates invalid strings like `)(`.

❌ Off-by-one in `left > n` vs `left >= n` — check boundary carefully.

---

## Related Problems

- 20. Valid Parentheses (validation, not generation)
- 32. Longest Valid Parentheses
- 1249. Minimum Remove to Make Valid Parentheses

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Generate valid bracket sequences
- Combinations of characters with constraints

Think:

```
Constrained Backtracking with Balance Tracking
```
