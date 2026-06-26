# LeetCode Solutions Tracker

**Total Solved: 58**

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

## Math & Bits (7 solved)

### Day 1
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 136 | Single Number | Easy | XOR Cancellation |

### Day 2
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 231 | [Power of Two](Math-Bits/Day-2/231-Power-of-TwoREADME.md) | Easy | Bit Trick `n & (n-1)` |
| 29 | [Divide Two Integers](Math-Bits/Day-2/29-Divide-Two-IntegersREADME.md) | Medium | Exponential Bit Doubling |

### Day 3
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 137 | [Single Number II](Math-Bits/Day-3/137-Single-Number-IIREADME.md) | Medium | Bit Count mod 3 |
| 260 | [Single Number III](Math-Bits/Day-3/260-Single-Number-IIIREADME.md) | Medium | XOR + Partition by Set Bit |
| 204 | [Count Primes](Math-Bits/Day-3/204-Count-PrimesREADME.md) | Medium | Sieve of Eratosthenes |

---

## Sliding Window (0 solved)

---

## Stack & Queue (0 solved)

---

## Linked List (0 solved)

---

## Trees (11 solved)

### Day 1
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 144 | [Binary Tree Preorder Traversal](Trees/Day-1/144-Binary-Tree-Preorder-TraversalREADME.md) | Easy | Recursive DFS (NLR) |
| 94 | [Binary Tree Inorder Traversal](Trees/Day-1/94-Binary-Tree-Inorder-TraversalREADME.md) | Easy | Recursive DFS (LNR) |
| 145 | [Binary Tree Postorder Traversal](Trees/Day-1/145-Binary-Tree-Postorder-TraversalREADME.md) | Easy | Recursive DFS (LRN) |
| 102 | [Binary Tree Level Order Traversal](Trees/Day-1/102-Binary-Tree-Level-Order-TraversalREADME.md) | Medium | BFS + Queue Size Snapshot |
| 110 | [Balanced Binary Tree](Trees/Day-1/110-Balanced-Binary-TreeREADME.md) | Easy | Height + Balance Check |

### Day 2
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 543 | [Diameter of Binary Tree](Trees/Day-2/543-Diameter-of-Binary-TreeREADME.md) | Easy | Height + Global Diameter Track |
| 124 | [Binary Tree Maximum Path Sum](Trees/Day-2/124-Binary-Tree-Maximum-Path-SumREADME.md) | Hard | Bend vs Extend (DFS) |
| 103 | [Binary Tree Zigzag Level Order Traversal](Trees/Day-2/103-Binary-Tree-Zigzag-Level-Order-TraversalREADME.md) | Medium | BFS + Toggle Index |
| 987 | [Vertical Order Traversal of a Binary Tree](Trees/Day-2/987-Vertical-Order-Traversal-of-a-Binary-TreeREADME.md) | Hard | DFS + Sort (col, row, val) |
| 199 | [Binary Tree Right Side View](Trees/Day-2/199-Binary-Tree-Right-Side-ViewREADME.md) | Medium | BFS / DFS Right-First |
| 101 | [Symmetric Tree](Trees/Day-2/101-Symmetric-TreeREADME.md) | Easy | Recursive Mirror Check |

---

## BST (0 solved)

---

## Graphs (0 solved)

---

## Heap (0 solved)

---

## Greedy (0 solved)

---

## Backtracking (8 solved)

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

### Day 4
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 17 | [Letter Combinations of a Phone Number](Backtracking/Day-4/17-Letter-Combinations-of-a-Phone-NumberREADME.md) | Medium | Phone Map + DFS Backtrack |
| 131 | [Palindrome Partitioning](Backtracking/Day-4/131-Palindrome-PartitioningREADME.md) | Medium | Is-Palindrome Check + Backtrack |

---

## DP (0 solved)

---

## Trie (4 solved)

### Day 1
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 208 | [Implement Trie (Prefix Tree)](Trie/Day-1/208-Implement-Trie-Prefix-TreeREADME.md) | Medium | Trie Node with 26-child Array |

### Day 2
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 421 | [Maximum XOR of Two Numbers in an Array](Trie/Day-2/421-Maximum-XOR-of-Two-Numbers-in-an-ArrayREADME.md) | Medium | Binary Trie + Greedy Opposite Bit |
| 1707 | [Maximum XOR With an Element From Array](Trie/Day-2/1707-Maximum-XOR-With-an-Element-From-ArrayREADME.md) | Hard | Offline Queries + Binary Trie |
| 648 | [Replace Words](Trie/Day-2/648-Replace-WordsREADME.md) | Medium | Trie Shortest Prefix Match |

---

## Design (1 solved)

### Day 1
| # | Problem | Difficulty | Pattern |
|---|---------|------------|---------|
| 211 | [Design Add and Search Words Data Structure](Trie/Day-2/211-Design-Add-and-Search-Words-Data-StructureREADME.md) | Medium | Trie + DFS Wildcard |

---

## Strings (0 solved)
