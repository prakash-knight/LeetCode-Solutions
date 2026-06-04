# 128. Longest Consecutive Sequence

[Link to LeetCode Problem](https://leetcode.com/problems/longest-consecutive-sequence/)

---

## 📝 Problem Statement

Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in **O(n)** time.

### Example

```cpp
Input:
nums = [100, 4, 200, 1, 3, 2]

Output:
4
```

Because:

```cpp
The longest consecutive sequence is [1, 2, 3, 4]. Length = 4.
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

The most straightforward method is:
- Sort the array.
- Find the longest streak of consecutive numbers.

### Why doesn't it satisfy the constraint?

```cpp
O(n log n)
```

Sorting takes O(n log n), but the problem requires O(n).

---

## 2. Optimized Approach (Hash Set)

### Pattern Used

```cpp
Hash Set + Sequence Start Detection
```

### Main Idea

Put all numbers in a hash set for O(1) lookups.

For each number, check if it's the **start of a sequence**:

```cpp
num is a sequence start if (num - 1) does NOT exist in the set
```

If it's a start, count how long the sequence extends:

```cpp
num, num+1, num+2, ... while they exist in the set
```

### Why is this O(n)?

Even though there's a while loop inside the for loop:
- Each number is visited **at most twice** (once in the outer loop, once as part of a sequence extension).
- Non-start elements are skipped immediately.

---

## Step-by-Step Logic

1. Insert all numbers into an `unordered_set`.

2. For each number in the set:
   - If `num - 1` exists → skip (not a sequence start).
   - If `num - 1` doesn't exist → it's a start:
     - Count consecutive numbers: `num, num+1, num+2, ...`
     - Update the longest length.

3. Return the longest length.

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Set construction: O(n).
- Each element is processed at most twice total.

---

## Space Complexity

```cpp
O(n)
```

Because:
- Hash set stores all elements.

---

# 💻 Code

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st(nums.begin(), nums.end());

        int longest = 0;

        for (int num : st) {
            // Only start counting from the beginning of a sequence
            if (st.find(num - 1) == st.end()) {
                int curr = num;
                int len = 1;

                while (st.find(curr + 1) != st.end()) {
                    curr++;
                    len++;
                }

                longest = max(longest, len);
            }
        }

        return longest;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Empty array

```cpp
nums = []
// Output: 0
```

---

✅ Duplicate elements

```cpp
nums = [1, 2, 0, 1]
// Output: 3 → sequence [0, 1, 2]
// Duplicates are handled naturally by the set
```

---

✅ All elements are the same

```cpp
nums = [5, 5, 5]
// Output: 1
```

---

✅ Negative numbers

```cpp
nums = [-1, 0, 1, 2]
// Output: 4
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Instead of sorting:
- Use a hash set for O(1) lookups.
- Only start counting from **sequence starts** (elements with no predecessor).
- This avoids redundant counting and ensures O(n) total.

---

## Common Mistakes

❌ Starting a count from every element:

```cpp
// WRONG: leads to O(n²) in worst case
for (int num : st) {
    int len = 1;
    while (st.find(num + 1) != st.end()) { ... }
}
```

Must check `st.find(num - 1) == st.end()` to only start from sequence beginnings.

---

❌ Iterating over the original array instead of the set:

Using the original array with duplicates can lead to redundant work.

---

## Related Problems

- Longest Consecutive Sequence
- Array Nesting
- Missing Number
- Find All Numbers Disappeared in an Array

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Longest consecutive sequence
- O(n) time with unordered data
- Sequence detection without sorting

Think:

```cpp
Hash Set + Start Detection (num - 1 not in set)
```

---
