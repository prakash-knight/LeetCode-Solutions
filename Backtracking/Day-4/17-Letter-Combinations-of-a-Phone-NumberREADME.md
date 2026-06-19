# 17. Letter Combinations of a Phone Number

[Link to LeetCode Problem](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)

---

## 📝 Problem Statement

Given a string containing digits from `2–9` inclusive, return all possible letter combinations that the number could represent (like a phone keypad).

### Example

```
Input:  digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Input:  digits = ""
Output: []
```

---

# 💡 Intuition & Approach

## Phone Map + DFS Backtracking

Each digit maps to a set of letters (like a T9 phone keypad). We need all possible combinations picking one letter per digit, in order.

## How It Works

1. Build a map: `digit → string of letters` (e.g. `2 → "abc"`, `7 → "pqrs"`)
2. DFS with index `idx` tracks which digit we're processing
3. For each letter of `mp[digits[idx]]`, append it to `temp`, recurse to `idx+1`, then backtrack (pop)
4. Base case: `idx >= digits.size()` → push `temp` to `ans`

### Trace for "23"

```
solve(temp="", idx=0)   → digit '2' → letters "abc"
  pick 'a' → solve("a", idx=1)   → digit '3' → letters "def"
    pick 'd' → solve("ad", idx=2) → BASE: push "ad"
    pick 'e' → solve("ae", idx=2) → BASE: push "ae"
    pick 'f' → solve("af", idx=2) → BASE: push "af"
  pick 'b' → solve("b", idx=1)
    → "bd", "be", "bf"
  pick 'c' → solve("c", idx=1)
    → "cd", "ce", "cf"
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(4ⁿ × n)
```

- At most 4 letters per digit (e.g. 7 → "pqrs"), n digits
- Building each combination costs O(n)

## Space Complexity

```
O(n)
```

- Recursion depth = n (number of digits)
- `temp` holds at most n characters

---

# 💻 Code

```cpp
class Solution {
public:
    vector<string> ans;
    string temp;

    void solve(string temp, int idx, string& di,
               unordered_map<int, string>& mp) {
        if (idx >= di.size()) {
            ans.push_back(temp);
            return;
        }

        string s = mp[di[idx] - '0'];
        for (int i = 0; i < s.size(); i++) {
            temp.push_back(s[i]);
            solve(temp, idx + 1, di, mp);
            temp.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty())
            return {};

        unordered_map<int, string> mp;
        mp[2] = "abc"; mp[3] = "def"; mp[4] = "ghi";
        mp[5] = "jkl"; mp[6] = "mno"; mp[7] = "pqrs";
        mp[8] = "tuv"; mp[9] = "wxyz";

        solve(temp, 0, digits, mp);
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty `digits` → returns `[]` (early return guard)

✅ Single digit like `"2"` → `["a","b","c"]`

✅ Digit `7` or `9` with 4 letters → handled correctly via map

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Map digit → letters, then DFS picking one letter per digit level
```

Pass `temp` by value (not reference) to avoid manual pop_back, **or** push/pop explicitly as done here.

## Common Mistakes

❌ Forgetting the early return for empty input → pushes empty string `""`.

❌ Using `mp[di[idx]]` instead of `mp[di[idx] - '0']` → wrong key type.

---

## Related Problems

- 131. Palindrome Partitioning
- 22. Generate Parentheses
- 46. Permutations

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Generate all strings by picking one character per "slot"
- Each slot has its own set of valid characters

Think:

```
DFS with index + character map → Phone keypad / Word search style backtracking
```
