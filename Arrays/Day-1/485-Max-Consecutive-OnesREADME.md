# 485. Max Consecutive Ones

[Link to LeetCode Problem](https://leetcode.com/problems/max-consecutive-ones/)

---

## 1. 📝 Problem Statement

Given a binary array `nums` (only `0`s and `1`s), return the **maximum number of consecutive `1`s** in the array.

### Example

```
Input:  nums = [1, 1, 0, 1, 1, 1]
Output: 3
Explanation: The first two digits and last three digits are consecutive 1s.
             The maximum consecutive 1s is 3.

Input:  nums = [1, 0, 1, 1, 0, 1]
Output: 2
```

### Constraints
- `1 <= nums.length <= 10⁵`
- `nums[i]` is either `0` or `1`.

---

## 2. 💡 Intuition

### How should I think about this problem?

Imagine walking through the array with a **counter**:
- Every time you see a `1`, increment your counter.
- Every time you see a `0`, your streak is broken — reset the counter to 0.
- At every step, check if the current streak is the longest you've seen.

### Key Observations

1. **Linear scan is enough**: You just need one pass — no sorting, no extra data structures.
2. **Track two things**: Current streak length (`count`) and the best streak seen so far (`maxCount`).
3. **Zero resets the streak**: The moment you hit 0, the streak breaks.

---

## 3. 🐢 Brute Force Approach

### Idea
For every index `i`, count consecutive 1s starting from `i`. Track the maximum.

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxCount = 0;
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                int count = 0;
                for (int j = i; j < n && nums[j] == 1; j++) {
                    count++;
                }
                maxCount = max(maxCount, count);
            }
        }
        return maxCount;
    }
};
```

### Complexity
- **Time**: `O(n²)` — For each starting index, we scan forward.
- **Space**: `O(1)`.

### Why is it bad?
Redundant work — you recount overlapping segments.

---

## 4. 🚀 Optimal Approach — Single Pass Counter

### Logic (Step-by-Step)

1. **Initialize `count = 0`** (current streak) and **`maxCount = 0`** (best streak).
2. **Iterate through each element**:
   - If `nums[i] == 1` → `count++`.
   - If `nums[i] == 0` → `count = 0` (reset streak).
   - Update `maxCount = max(maxCount, count)` after every step.
3. **Return `maxCount`**.

### Why does it work?

- We process each element exactly once.
- `count` always holds the length of the current consecutive-1s streak ending at index `i`.
- `maxCount` captures the global maximum across all streaks.
- When a `0` appears, there's no way the current streak can continue, so resetting is correct.

### 🔍 Dry Run

```
Input: nums = [1, 1, 0, 1, 1, 1]

i=0: nums[0]=1 → count=1, maxCount=max(0,1)=1
i=1: nums[1]=1 → count=2, maxCount=max(1,2)=2
i=2: nums[2]=0 → count=0, maxCount=max(2,0)=2
i=3: nums[3]=1 → count=1, maxCount=max(2,1)=2
i=4: nums[4]=1 → count=2, maxCount=max(2,2)=2
i=5: nums[5]=1 → count=3, maxCount=max(2,3)=3

Output: 3 ✅
```

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int count = 0;         // current streak of consecutive 1s
        int maxCount = 0;      // best (longest) streak seen so far
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 1) {
                count++;                           // extend the streak
            } else {
                count = 0;                         // streak broken, reset
            }
            maxCount = max(maxCount, count);       // update global best
        }
        
        return maxCount;       // return the longest streak
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `count` | Length of the current consecutive-1s streak |
| `maxCount` | Maximum streak length seen so far (the answer) |
| `i` | Loop index scanning each element |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Sliding Window / Running Counter**

This is the simplest form of a **sliding window** — a variable-size window that tracks a streak.

### When to use:
- "Maximum/minimum consecutive X"
- "Longest subarray with property Y"
- Streak counting problems.

| Pattern | How it applies |
|---------|---------------|
| **Sliding Window** | The "window" is the current streak of 1s |
| **Running Counter** | `count` accumulates, resets on break |
| **Greedy** | Always extend streak if possible, reset if not |

> 🧠 **Mental Model**: "Walk through the array with a counter. Grow on 1, reset on 0, track the max."

---

## 7. ⚠️ Common Mistakes

### ❌ Forgetting to update maxCount BEFORE resetting
```cpp
// WRONG: you lose the streak length before recording it
if (nums[i] == 0) count = 0;
maxCount = max(maxCount, count);  // count is already 0!

// CORRECT: update maxCount at every step (including when count grows)
// OR update maxCount BEFORE resetting:
maxCount = max(maxCount, count);
if (nums[i] == 0) count = 0;
```

Actually, the cleanest approach (used in our solution) updates maxCount at every step — both when count grows and when it resets:
```cpp
if (nums[i] == 1) count++;
else count = 0;
maxCount = max(maxCount, count);  // works correctly either way
```

### ❌ Not handling all-ones array
If the array is `[1, 1, 1]`, there's no `0` to trigger a "final update". The loop-based `max` at every step handles this correctly.

### ❌ Over-engineering with sliding window
This problem doesn't need left/right pointers or a deque. A simple counter is sufficient.

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "What if you can flip at most one 0 to 1?" (LeetCode 487)
**Answer**: Use a **sliding window** with a counter for zeroes in the window. When zeroes exceed 1, shrink from the left.

### Q2: "What if you can flip at most k zeroes?" (LeetCode 1004)
**Answer**: Generalized sliding window:
```cpp
int left = 0, zeroCount = 0, maxLen = 0;
for (int right = 0; right < n; right++) {
    if (nums[right] == 0) zeroCount++;
    while (zeroCount > k) {
        if (nums[left] == 0) zeroCount--;
        left++;
    }
    maxLen = max(maxLen, right - left + 1);
}
```

### Q3: "Return the starting index of the longest streak?"
**Answer**: Track `startIndex = i - count + 1` whenever `maxCount` is updated.

### Q4: "What if the array is a stream (infinite)?"
**Answer**: Same approach works — you only need `count` and `maxCount`. O(1) space, one-pass.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Single pass through the array. Each element visited once.

### Space Complexity: `O(1)`
- Only two integer variables. No extra data structures.

---
