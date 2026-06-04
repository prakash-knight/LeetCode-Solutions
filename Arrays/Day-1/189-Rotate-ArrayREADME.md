# 189. Rotate Array

[Link to LeetCode Problem](https://leetcode.com/problems/rotate-array/)

---

## 1. 📝 Problem Statement

Given an integer array `nums`, rotate the array to the **right** by `k` steps.

In simple words:
- Take the last `k` elements and move them to the front.
- The remaining elements shift to the right.

### Example

```
Input:  nums = [1, 2, 3, 4, 5, 6, 7], k = 3
Output: [5, 6, 7, 1, 2, 3, 4]
```

Step-by-step rotation:
```
Step 1: [7, 1, 2, 3, 4, 5, 6]   → last element moved to front
Step 2: [6, 7, 1, 2, 3, 4, 5]   → last element moved to front
Step 3: [5, 6, 7, 1, 2, 3, 4]   → last element moved to front
```

### Constraints
- `1 <= nums.length <= 10⁵`
- `-2³¹ <= nums[i] <= 2³¹ - 1`
- `0 <= k <= 10⁵`
- **Must be done in-place** with O(1) extra space.

---

## 2. 💡 Intuition

### How should I think about this problem?

Think of the array as a **circle**. When you rotate right by `k`, the last `k` elements wrap around to the beginning.

### Key Observations

1. **k can be larger than n**: If `k = 10` and `n = 7`, rotating 10 times is the same as rotating `10 % 7 = 3` times. So always do `k = k % n`.

2. **The Reversal Trick**: This is the golden insight. After rotation:
   - The last `k` elements become the first `k` elements.
   - The first `n-k` elements become the last `n-k` elements.
   - Within each group, the **relative order is preserved**.

3. **Visualize it**:
   ```
   Original:       [1, 2, 3, 4, | 5, 6, 7]     (k=3)
                    ← first n-k →  ← last k →
   
   After rotation:  [5, 6, 7, | 1, 2, 3, 4]
                    ← last k →  ← first n-k →
   ```

   The two blocks **swap positions** but keep their internal order.

---

## 3. 🐢 Brute Force Approach

### Idea
Rotate one step at a time. For each step:
1. Save the last element.
2. Shift all elements one position to the right.
3. Place the saved element at position 0.
4. Repeat `k` times.

### Code

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        
        for (int step = 0; step < k; step++) {
            int last = nums[n - 1];           // save last element
            for (int i = n - 1; i > 0; i--) {
                nums[i] = nums[i - 1];         // shift right
            }
            nums[0] = last;                    // place at front
        }
    }
};
```

### Complexity
- **Time**: `O(n × k)` — For each of `k` steps, we shift `n` elements.
- **Space**: `O(1)` — In-place.

### Why is it bad?
If `k` is close to `n`, and `n = 10⁵`, we do ~10¹⁰ operations → **TLE**.

---

## 4. 🚀 Optimal Approach — The Reversal Algorithm

### Logic (Step-by-Step)

1. **Normalize k**: `k = k % n` (handles k > n).
2. **Reverse the entire array**.
3. **Reverse the first k elements**.
4. **Reverse the remaining n-k elements**.

### Why does it work?

Let's call the first `n-k` elements **A** and the last `k` elements **B**.

```
Original:          A  B
Reverse all:       B' A'     (B reversed, A reversed)
Reverse first k:   B  A'     (B restored to original order)
Reverse last n-k:  B  A      (A restored to original order)
```

Each reverse undoes the internal reversal while keeping the groups swapped.

### 🔍 Dry Run

```
Input: nums = [1, 2, 3, 4, 5, 6, 7], k = 3

Step 0: k = 3 % 7 = 3

Step 1: Reverse entire array
        [7, 6, 5, 4, 3, 2, 1]

Step 2: Reverse first k=3 elements → indices [0, 2]
        [5, 6, 7, 4, 3, 2, 1]

Step 3: Reverse remaining n-k=4 elements → indices [3, 6]
        [5, 6, 7, 1, 2, 3, 4]

Output: [5, 6, 7, 1, 2, 3, 4] ✅
```

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    // Helper: reverse array from index 'start' to 'end' (inclusive)
    void reverse(vector<int>& nums, int start, int end) {
        while (start < end) {
            swap(nums[start], nums[end]);  // swap elements at both ends
            start++;                        // move left pointer right
            end--;                          // move right pointer left
        }
    }

    void rotate(vector<int>& nums, int k) {
        int n = nums.size();       // n = total number of elements
        k = k % n;                 // normalize k (handle k > n)

        if (k == 0) return;        // no rotation needed

        reverse(nums, 0, n - 1);   // Step 1: reverse entire array
        reverse(nums, 0, k - 1);   // Step 2: reverse first k elements
        reverse(nums, k, n - 1);   // Step 3: reverse remaining n-k elements
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `n` | Size of the array |
| `k` | Number of positions to rotate (normalized with `% n`) |
| `start` | Left pointer for the reverse helper |
| `end` | Right pointer for the reverse helper |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Array Reversal / In-place Manipulation**

This is a classic **Reversal Algorithm** pattern.

### When to use:
- You need to **rearrange** elements in-place.
- The rearrangement involves **rotating**, **shifting**, or **cyclic permutation**.
- O(1) space is required.

### Related Patterns:

| Pattern | How it applies |
|---------|---------------|
| **In-place Operations** | Modify the array without extra space |
| **Two Pointers** | The `reverse()` helper uses two pointers converging from both ends |
| **Array Manipulation** | Core skill — rearranging elements by index |

> 🧠 **Mental Model**: "When you need to rotate or shift a portion of an array in-place, think **REVERSE**."

---

## 7. ⚠️ Common Mistakes

### ❌ Forgetting to normalize k

```cpp
// WRONG: crashes if k > n
reverse(nums, 0, k - 1);

// CORRECT
k = k % n;
```

### ❌ Off-by-one errors in reverse boundaries

```cpp
// WRONG
reverse(nums, 0, k);      // should be k-1
reverse(nums, k + 1, n);  // should be k and n-1

// CORRECT
reverse(nums, 0, k - 1);
reverse(nums, k, n - 1);
```

### ❌ Using extra space when the problem says in-place

Using a temp array is valid O(n) space solution but doesn't satisfy the follow-up constraint.

### ❌ Not handling k = 0 or k = n

Both mean no rotation. `k = k % n` handles `k = n`, and checking `k == 0` avoids unnecessary work.

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "Can you do this without the reversal approach?"

**Answer**: Yes — **Cyclic Replacement**. Place element from index `i` to `(i+k)%n`, continue with the displaced element. Time O(n), Space O(1).

### Q2: "What if O(n) extra space is allowed?"

**Answer**: Use a temp array: `temp[(i + k) % n] = nums[i]`.

### Q3: "How would you rotate LEFT by k?"

**Answer**: Left rotation by `k` = Right rotation by `n - k`.

### Q4: "Can you rotate a linked list with this?"

**Answer**: No — linked lists don't support random access. Find the `(n-k)`th node, break and reconnect.

### Q5: "What if the array is stored on disk?"

**Answer**: Reversal is ideal — sequential passes, cache-friendly, O(1) memory.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`

- `reverse(0, n-1)` → n/2 swaps
- `reverse(0, k-1)` → k/2 swaps
- `reverse(k, n-1)` → (n-k)/2 swaps
- **Total**: n swaps → O(n)

### Space Complexity: `O(1)`

- Only a few integer variables. No extra array.

---
