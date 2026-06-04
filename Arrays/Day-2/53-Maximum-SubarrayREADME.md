# 53. Maximum Subarray

[Link to LeetCode Problem](https://leetcode.com/problems/maximum-subarray/)

---

## 📝 Problem Statement

Given an integer array `nums`, find the subarray with the largest sum, and return its sum.

A subarray is a contiguous non-empty sequence of elements within an array.

### Example

```cpp
Input:
nums = [-2,1,-3,4,-1,2,1,-5,4]

Output:
6
```

Because:

```cpp
Subarray [4,-1,2,1] has the largest sum = 6.
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

The most straightforward method is:
- Check every possible subarray.
- Track the maximum sum found.

### Why is it inefficient?

```cpp
O(n²)
```

time complexity due to nested loops over all subarrays.

---

## 2. Optimized Approach (Kadane's Algorithm)

### Pattern Used

```cpp
Kadane's Algorithm (Dynamic Programming / Greedy)
```

### Main Idea

At each position, decide:
- Should we **extend** the current subarray?
- Or **start fresh** from the current element?

The key insight:

```cpp
If the running sum becomes negative, discard it.
A negative prefix can never improve a future subarray.
```

So whenever `sum < 0`, reset it to 0 before adding the current element.

---

## Step-by-Step Logic

1. Initialize:

```cpp
sum = INT_MIN    // running sum (reset when negative)
maxi = INT_MIN   // global maximum
```

2. For each element:
   - If `sum < 0` → reset `sum = 0`
   - Add current element: `sum += nums[i]`
   - Update global max: `maxi = max(maxi, sum)`

3. Return `maxi`.

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
- Only two variables used.

---

# 💻 Code

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = INT_MIN;
        int maxi = INT_MIN;

        for (int i = 0; i < nums.size(); i++) {
            if (sum < 0) {
                sum = 0;
            }

            sum += nums[i];
            maxi = max(maxi, sum);
        }

        return maxi;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ All negative numbers

```cpp
nums = [-3, -2, -1]
// Output: -1 (largest single element)
```

---

✅ Single element

```cpp
nums = [5]
// Output: 5
```

---

✅ Entire array is the answer

```cpp
nums = [1, 2, 3, 4]
// Output: 10
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Instead of trying all subarrays:
- A negative running sum can never help future subarrays.
- Reset to 0 whenever sum goes negative.
- Always track the maximum seen so far.

---

## Common Mistakes

❌ Initializing `maxi = 0` instead of `INT_MIN`:

```cpp
// WRONG: fails for all-negative arrays
int maxi = 0;
```

---

❌ Resetting sum **after** adding the element:

```cpp
// WRONG order
sum += nums[i];
if (sum < 0) sum = 0;  // ← loses valid negative result
```

Correct: reset **before** adding.

---

## Related Problems

- Maximum Product Subarray
- Maximum Sum Circular Subarray
- Subarray Sum Equals K
- Longest Turbulent Subarray

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Maximum/minimum subarray sum
- Contiguous subarray optimization
- Extend or start fresh decision

Think:

```cpp
Kadane's Algorithm
```

---
