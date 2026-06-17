# LeetCode Solutions Tracker

**Total Solved: 35**

---

## 📖 How to Add a New Problem

> Follow these steps exactly every time a new problem is solved.

### Step 1 — Create the solution file

**File path format:**
```
<Topic>/Day-<N>/<problem-number>-<Problem-Name-Kebab-Case>README.md
```

**Examples:**
```
Backtracking/Day-1/78-SubsetsREADME.md
Arrays/Day-2/53-Maximum-SubarrayREADME.md
```

**File structure (copy this template):**
```markdown
# <number>. <Problem Name>

[Link to LeetCode Problem](<leetcode-url>)

---

## 📝 Problem Statement

<Brief description of the problem>

### Example

\`\`\`
Input:  ...
Output: ...
\`\`\`

---

# 💡 Intuition & Approach

## <Approach Name>

<Explanation of the approach>

---

# ⏱️ Complexity Analysis

## Time Complexity

\`\`\`
O(...)
\`\`\`

## Space Complexity

\`\`\`
O(...)
\`\`\`

---

# 💻 Code

\`\`\`cpp
// solution here
\`\`\`

---

# 🔍 Edge Cases Handled

✅ ...

---

# 🤔 Key Takeaways (For Revision)

## Main Trick
...

## Common Mistakes
❌ ...

---

## Related Problems
- ...

---

# 🧠 Revision Notes

## Pattern Recognition
...
```

---

### Step 2 — Update this README

1. **Increment** `Total Solved` count at the top.
2. **Find the right topic section** (e.g. `## Backtracking`).
3. **Update the solved count** in the section header (e.g. `(6 solved)` → `(7 solved)`).
4. **Add a row** to the correct Day table (or add a new `### Day N` block if it's a new day):

```markdown
| <#> | [<Problem Name>](<Topic>/Day-<N>/<file>README.md) | <Easy/Medium/Hard> | <Pattern> |
```

5. If starting a **new topic** that shows `(0 solved)`, change it to `(1 solved)` and add the Day table below it.

---

### Step 3 — Git commit

```bash
git add .
git commit -m "Add <#>. <Problem Name> [<Topic>]"
```

---

## Arrays (15 solved)

### Day 1
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 1 | Two Sum | Easy | Hash Map + Complement |
| 26 | Remove Duplicates from Sorted Array | Easy | Two Pointers |
| 283 | Move Zeroes | Easy | Two Pointers |
| 485 | Max Consecutive Ones | Easy | Linear Scan |
| 189 | Rotate Array | Medium | Reverse Technique |
| 1752 | Check if Array is Sorted and Rotated | Easy | Count Breaks |

### Day 2
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 53 | Maximum Subarray | Medium | Kadane's Algorithm |
| 121 | Best Time to Buy and Sell Stock | Easy | Track Min + Max Profit |
| 169 | Majority Element | Easy | Boyer-Moore Voting |
| 128 | Longest Consecutive Sequence | Medium | Hash Set + Start Detection |
| 73 | Set Matrix Zeroes | Medium | In-place Marking |
| 48 | Rotate Image | Medium | Transpose + Reverse |
| 560 | Subarray Sum Equals K | Medium | Prefix Sum + Hash Map |
| 11 | Container With Most Water | Medium | Two Pointers (Greedy) |

### Day 3
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 238 | Product of Array Except Self | Medium | Prefix & Suffix Products |

---

## Binary Search (8 solved)

### Day 1
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 704 | Binary Search | Easy | Classic Binary Search |
| 35 | Search Insert Position | Easy | Lower Bound BS |
| 34 | Find First and Last Position | Medium | Two Binary Searches |
| 33 | Search in Rotated Sorted Array | Medium | Modified BS (Pivot) |
| 153 | Find Minimum in Rotated Sorted Array | Medium | BS on Rotated Array |
| 162 | Find Peak Element | Medium | BS on Answer |
| 875 | Koko Eating Bananas | Medium | BS on Answer Space |
| 1011 | Capacity To Ship Packages | Medium | BS on Answer Space |

---

## Sorting (5 algorithms)

### Day 1
| Algorithm | Best | Worst | Space | Stable |
|-----------|------|-------|-------|--------|
| Bubble Sort | O(n) | O(n²) | O(1) | Yes |
| Selection Sort | O(n²) | O(n²) | O(1) | No |
| Insertion Sort | O(n) | O(n²) | O(1) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n) | Yes |
| Quick Sort | O(n log n) | O(n²) | O(log n) | No |

---

## Math & Bits (1 solved)

### Day 1
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 136 | Single Number | Easy | XOR Cancellation |

---

## Sliding Window (0 solved)

---

## Stack & Queue (0 solved)

---

## Linked List (0 solved)

---

## Trees (0 solved)

---

## BST (0 solved)

---

## Graphs (0 solved)

---

## Heap (0 solved)

---

## Greedy (0 solved)

---

## Backtracking (6 solved)

### Day 1
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 78 | [Subsets](Backtracking/Day-1/78-SubsetsREADME.md) | Medium | Binary Choice (Take / Leave) |
| 90 | [Subsets II](Backtracking/Day-1/90-Subsets-IIREADME.md) | Medium | Sort + Skip Duplicates on Leave |

### Day 2
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 46 | [Permutations](Backtracking/Day-2/46-PermutationsREADME.md) | Medium | Visited Map + For-loop |
| 47 | [Permutations II](Backtracking/Day-2/47-Permutations-IIREADME.md) | Medium | Visited Map + Set Dedup |

### Day 3
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 22 | [Generate Parentheses](Backtracking/Day-3/22-Generate-ParenthesesREADME.md) | Medium | Balance Counter (cnt) |
| 216 | [Combination Sum III](Backtracking/Day-3/216-Combination-Sum-IIIREADME.md) | Medium | Start Index + Sum Constraint |

---

## DP (0 solved)

---

## Design (0 solved)

---

## Strings (0 solved)
