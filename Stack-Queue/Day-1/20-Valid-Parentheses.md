# 20. Valid Parentheses

[Link to LeetCode Problem](https://leetcode.com/problems/valid-parentheses/)

---

## 1. 📝 Problem Statement

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is **valid**.

An input string is valid if:
1. Open brackets must be closed by the **same type** of brackets.
2. Open brackets must be closed in the **correct order**.
3. Every close bracket has a corresponding open bracket of the same type.

### Example

```
Input:  s = "()"
Output: true

Input:  s = "()[]{}"
Output: true

Input:  s = "(]"
Output: false

Input:  s = "([)]"
Output: false

Input:  s = "{[]}"
Output: true
```

### Constraints
- `1 <= s.length <= 10⁴`
- `s` consists of parentheses only `'()[]{}'`

---

## 2. 💡 Intuition

### How should I think about this problem?

Use a **stack** to track unmatched opening brackets. When we see a closing bracket, check if the top of the stack has the matching opening bracket.

### Key Observations

1. **LIFO principle**: The most recently opened bracket must be closed first — this is exactly what a stack does.
2. **Matching pairs**: `()`, `{}`, `[]` — each closing bracket has exactly one valid opener.
3. **Empty at the end**: If all brackets matched correctly, the stack is empty at the end.

### Visualization

```
s = "{[]}"

Push '{' → stack: {
See '[' → push → stack: { [
See ']' → top is '[', match! pop → stack: {
See '}' → top is '{', match! pop → stack: (empty)

Stack is empty → true ✅
```

---

## 3. 🐢 Brute Force Approach

Repeatedly scan the string and remove adjacent valid pairs `()`, `{}`, `[]` until no more can be removed. If the string becomes empty, it's valid.

```cpp
class Solution {
public:
    bool isValid(string s) {
        while (s.find("()") != string::npos ||
               s.find("{}") != string::npos ||
               s.find("[]") != string::npos) {
            size_t pos;
            if ((pos = s.find("()")) != string::npos) s.erase(pos, 2);
            if ((pos = s.find("{}")) != string::npos) s.erase(pos, 2);
            if ((pos = s.find("[]")) != string::npos) s.erase(pos, 2);
        }
        return s.empty();
    }
};
```

- **Time**: `O(n²)` — repeated scanning and erasing
- **Space**: `O(n)` — string manipulation

---

## 4. 🚀 Optimal Approach — Stack

### Logic (Step-by-Step)

1. Push the **first character** (or handle it in the loop).
2. For each character `s[i]`:
   - If it's a **closing bracket** and the stack top is the matching **opening bracket** → **pop** and continue.
   - Otherwise → **push** `s[i]`.
3. Return `true` if the stack is **empty** at the end.

### Why does it work?

The stack remembers which brackets are still open. Every valid closing bracket must match the most recently pushed opener (LIFO). If we ever can't match, we push the closer onto the stack — making the stack non-empty at the end (invalid).

### 🔍 Dry Run

```
s = "([)]"

Push '(' → stack: (
See '[' → top is '(', no match → push '[' → stack: ( [
See ')' → top is '[', no match → push ')' → stack: ( [ )
See ']' → top is ')', no match → push ']' → stack: ( [ ) ]

Stack not empty → false ✅
```

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<int> st;

        st.push(s[0]);

        for (int i = 1; i < s.size(); i++) {
            if (!st.empty() && s[i] == ')' && st.top() == '(') {
                st.pop();
                continue;
            } else if (!st.empty() && s[i] == '}' && st.top() == '{') {
                st.pop();
                continue;
            } else if (!st.empty() && s[i] == ']' && st.top() == '[') {
                st.pop();
                continue;
            }
            st.push(s[i]);
        }

        return st.empty();
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `st` | Stack to track unmatched opening brackets |
| `s[i]` | Current character being processed |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Stack — Matching/Bracket Validation**

This is the classic **bracket matching** pattern using a stack.

### When to use:
- Validate balanced brackets / parentheses.
- Match pairs of any kind (HTML tags, function calls).
- Any problem where the most recently opened thing must be closed first.

| Pattern | How it applies |
|---------|---------------|
| **Stack** | LIFO ensures innermost bracket is matched first |
| **Greedy Pop** | Match and remove pairs as soon as they appear |

> 🧠 **Mental Model**: "The stack is like a to-do list of 'brackets still waiting to be closed'."

---

## 7. ⚠️ Common Mistakes

### ❌ Not checking if stack is empty before accessing top
```cpp
// WRONG: st.top() on empty stack → undefined behavior
if (s[i] == ')' && st.top() == '(') { ... }

// CORRECT: always guard with !st.empty()
if (!st.empty() && s[i] == ')' && st.top() == '(') { ... }
```

### ❌ Forgetting the final empty check
The stack may be non-empty if there are unmatched opening brackets at the end.

### ❌ Pushing the first character outside the loop
Better style to handle all characters uniformly in the loop:
```cpp
for (char ch : s) {
    if (!st.empty() && matches(st.top(), ch)) st.pop();
    else st.push(ch);
}
```

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "Can you do it without a stack?"
**Answer**: Not cleanly. A stack is the natural fit for LIFO matching. You could simulate with a string (used as a stack), but it's essentially the same.

### Q2: "What if there are other characters besides brackets?"
**Answer**: Skip non-bracket characters; only push/pop on brackets.

### Q3: "What is the minimum input size that can be valid?"
**Answer**: Empty string (length 0) is trivially valid. Smallest non-trivial valid string has length 2: `()`.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Each character is pushed and popped at most once.

### Space Complexity: `O(n)`
- Worst case (all opening brackets): the stack holds all `n` characters.
