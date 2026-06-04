# 169. Majority Element

[Link to LeetCode Problem](https://leetcode.com/problems/majority-element/)

---

## 📝 Problem Statement

Given an array `nums` of size `n`, return the majority element.

The majority element is the element that appears more than `⌊n / 2⌋` times.

You may assume that the majority element always exists in the array.

### Example

```cpp
Input:
nums = [2,2,1,1,1,2,2]

Output:
2
```

Because:

```cpp
2 appears 4 times out of 7 elements → 4 > ⌊7/2⌋ = 3
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

The most straightforward method is:
- Count frequency of each element using a hash map.
- Return the element with count > n/2.

### Why can we do better?

While this works in O(n) time, it uses O(n) space.

---

## 2. Optimized Approach (Boyer-Moore Voting Algorithm)

### Pattern Used

```cpp
Boyer-Moore Majority Vote Algorithm
```

### Main Idea

The algorithm works like a voting system:
- Maintain a candidate and a counter.
- When counter drops to 0, pick the current element as new candidate.
- If current element matches candidate, increment counter.
- Otherwise, decrement counter.

### Why does it work?

The majority element appears more than n/2 times. So even if every other element "votes against" it, the majority element will survive as the final candidate.

Think of it as:
- Majority element has more "soldiers" than all others combined.
- Pair up opposing elements — the majority will always have survivors.

---

## Step-by-Step Logic

1. Initialize:

```cpp
num = 0      // candidate
count = 0    // vote counter
```

2. For each element `n` in array:
   - If `count == 0` → set `num = n` (new candidate)
   - If `n == num` → increment count
   - Else → decrement count

3. Return `num` (the surviving candidate).

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Single pass through the array.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only two variables used regardless of input size.

---

# 💻 Code

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int num = 0, count = 0;

        for (auto n : nums) {
            if (count == 0) num = n;
            if (num == n) count++;
            else count--;
        }

        return num;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single element array

```cpp
nums = [1]
// Output: 1
```

---

✅ All elements are the same

```cpp
nums = [3, 3, 3]
// Output: 3
```

---

✅ Majority element at the end

```cpp
nums = [1, 2, 3, 3, 3]
// Output: 3
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Instead of counting every element:
- Use a voting mechanism where the majority element always survives cancellation.
- This achieves O(1) space.

---

## Common Mistakes

❌ Assuming the algorithm verifies the majority.

Boyer-Moore only finds a **candidate**. If the problem doesn't guarantee a majority exists, you need a second pass to verify the count.

---

❌ Confusing the algorithm flow:

```cpp
// WRONG: checking count before updating candidate
if (num == n) count++;
else if (count == 0) num = n;  // ← wrong order
```

Correct order: check `count == 0` first, then compare.

---

## Related Problems

- Majority Element II (appears > n/3 times)
- Check If a Number Is Majority Element in a Sorted Array

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Element appearing more than n/2 or n/3 times
- Find dominant element in O(1) space

Think:

```cpp
Boyer-Moore Voting Algorithm
```

---
