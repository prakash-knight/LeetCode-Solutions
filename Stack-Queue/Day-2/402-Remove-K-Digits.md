# 402. Remove K Digits

[Link to LeetCode Problem](https://leetcode.com/problems/remove-k-digits/)

---

## 1. 📝 Problem Statement

Given string `num` representing a non-negative integer, and an integer `k`, return the **smallest possible integer** after removing `k` digits from `num`.

### Example

```
Input:  num = "1432219", k = 3
Output: "1219"

Input:  num = "10200", k = 1
Output: "200"   → wait, leading zeros → "200"

Input:  num = "10", k = 2
Output: "0"
```

### Constraints
- `1 <= k <= num.length <= 10⁵`
- `num` consists of only digits.
- `num` does not have any leading zeros except for `num = "0"`.

---

## 2. 💡 Intuition

### How should I think about this problem?

To get the **smallest number**, we want the **most significant digits to be as small as possible**.

### Key Insight

Greedily scan left to right. Whenever we see a digit **smaller** than the previous digit we placed, remove the previous digit (it's making the number larger). This is a classic **monotonic stack** application.

### Why does this work?

- The number's value is dominated by its most significant digits.
- If `d[i-1] > d[i]`, removing `d[i-1]` makes the number smaller because `d[i]` takes its position, and a smaller digit at a higher position always wins.
- Repeat `k` times greedily.

### Visualization

```
num = "1432219", k = 3

Process '1': stack = [1]
Process '4': 4 > 1, push → stack = [1,4]
Process '3': 3 < 4, pop 4 (k=2), 3 > 1, push → stack = [1,3]
Process '2': 2 < 3, pop 3 (k=1), 2 > 1, push → stack = [1,2]
Process '2': 2 = 2, push → stack = [1,2,2]
Process '1': 1 < 2, pop 2 (k=0), stop → push 1 → stack = [1,2,1]
Process '9': k=0, push → stack = [1,2,1,9]

Result: "1219" ✅
```

---

## 3. 🐢 Brute Force Approach

Try all combinations of removing `k` digits and find the minimum. O(n choose k) — exponential.

---

## 4. 🚀 Optimal Approach — Greedy + Monotonic Stack (using string as stack)

### Logic (Step-by-Step)

1. Use a **string `st`** as a stack (efficient push_back / pop_back).
2. For each character `ch` in `num`:
   - While `k > 0` and stack is non-empty and `st.back() > ch`:
     - Pop from stack. Decrement `k`.
   - Push `ch`.
3. If `k > 0` still (didn't use all removals): remove the last `k` characters.
4. Strip **leading zeros**.
5. Return result, or `"0"` if empty.

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    string removeKdigits(string num, int k) {
        string st;

        for (char ch : num) {
            while (!st.empty() && k > 0 && st.back() > ch) {
                st.pop_back();
                k--;
            }
            st.push_back(ch);
        }

        // If k removals still remain, remove from the end (largest remaining digits)
        while (k > 0 && !st.empty()) {
            st.pop_back();
            k--;
        }

        // Strip leading zeros
        int i = 0;
        while (i < st.size() && st[i] == '0')
            i++;

        string ans = st.substr(i);

        return ans.empty() ? "0" : ans;
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `st` | Monotonic increasing string-stack of remaining digits |
| `k` | Remaining removal budget |
| `i` | Index to skip leading zeros |
| `ans` | Final answer after stripping leading zeros |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Greedy + Monotonic Increasing Stack**

### When to use:
- "Remove k elements to minimize/maximize value."
- "Find the smallest/largest subsequence of length n-k."

| Pattern | How it applies |
|---------|---------------|
| **Greedy** | Always remove the first "peak" digit when possible |
| **Monotonic Increasing Stack** | Maintain digits in non-decreasing order |
| **String as Stack** | Use `push_back`/`pop_back` for O(1) operations |

> 🧠 **Mental Model**: "Scan left to right. Whenever the digit at the top is bigger than the current, it's a 'bad' digit — remove it. Smaller digits at higher positions = smaller number."

---

## 7. ⚠️ Common Mistakes

### ❌ Forgetting to remove trailing digits when k > 0
If the input is monotonically increasing (e.g., `"1234"`, k=2), the while loop never triggers. Remove the last `k` digits manually.

### ❌ Not handling leading zeros
After removing digits, `"0200"` has a leading zero. Strip it to get `"200"`.

### ❌ Returning empty string
If all digits were removed (e.g., `"10"`, k=2), return `"0"` not `""`.

### ❌ Wrong comparison: using `>=` instead of `>`
Using `>=` removes equal digits unnecessarily, which can produce wrong results.

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "What if you want to maximize the number instead?"
**Answer**: Use a monotonic **decreasing** stack — pop when `st.back() < ch`.

### Q2: "What if you can only remove from the ends (not middle)?"
**Answer**: Different problem — use two pointers or sliding window.

### Q3: "Time complexity?"
**Answer**: O(n) — each character is pushed and popped at most once.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Each character pushed and popped at most once from the stack.

### Space Complexity: `O(n)`
- Stack stores up to `n` characters.
