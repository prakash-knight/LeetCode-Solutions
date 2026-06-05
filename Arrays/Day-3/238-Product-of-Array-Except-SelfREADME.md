# 238. Product of Array Except Self

[Link to LeetCode Problem](https://leetcode.com/problems/product-of-array-except-self/)

---

## 📝 Problem Statement

Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to the product of all elements of `nums` except `nums[i]`.

The product of any prefix or suffix of `nums` is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in `O(n)` time and **without using the division operator**.

### Example

```cpp
Input:
nums = [1,2,3,4]

Output:
[24,12,8,6]
```

Because:

```cpp
answer[0] = 2 * 3 * 4 = 24
answer[1] = 1 * 3 * 4 = 12
answer[2] = 1 * 2 * 4 = 8
answer[3] = 1 * 2 * 3 = 6
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

For each index, multiply all other elements together.

### Why is it inefficient?

```cpp
O(n²)
```

time complexity due to nested loops — for each element, you iterate through the entire array.

---

## 2. Optimized Approach (Suffix Array + Prefix Pass)

### Pattern Used

```cpp
Prefix-Suffix Product — Two Pass
```

### Main Idea

For any index `i`, the result is:

```cpp
answer[i] = product_of_all_elements_before_i * product_of_all_elements_after_i
           = prefix[i] * suffix[i]
```

Instead of maintaining two separate arrays, we:
1. **First pass (right to left):** Build a suffix product array.
2. **Second pass (left to right):** Multiply each suffix value by the running prefix product.

This gives us the answer in `O(1)` extra space (reusing the output array).

---

## Step-by-Step Logic

1. **Build suffix products (right to left):**

```cpp
suff = []
mul = 1
for i from n-1 to 0:
    suff.push_back(mul)    // suffix product for index i
    mul *= nums[i]
reverse(suff)              // now suff[i] = product of nums[i+1..n-1]
```

2. **Multiply with prefix products (left to right):**

```cpp
mul = 1
for i from 0 to n-1:
    suff[i] *= mul         // suff[i] now = prefix[i] * suffix[i]
    mul *= nums[i]         // update running prefix
```

3. Return `suff` — it now contains the final answer.

---

### Dry Run

```cpp
nums = [1, 2, 3, 4]

Pass 1 (suffix, right to left):
i=3: suff=[1],       mul=1*4=4
i=2: suff=[1,4],     mul=4*3=12
i=1: suff=[1,4,12],  mul=12*2=24
i=0: suff=[1,4,12,24], mul=24*1=24
After reverse: suff=[24,12,4,1]

Pass 2 (prefix, left to right):
i=0: suff[0]=24*1=24,  mul=1*1=1
i=1: suff[1]=12*1=12,  mul=1*2=2
i=2: suff[2]=4*2=8,    mul=2*3=6
i=3: suff[3]=1*6=6,    mul=6*4=24

Result: [24, 12, 8, 6] ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Two passes through the array, each `O(n)`.
- One `reverse()` call, also `O(n)`.

---

## Space Complexity

```cpp
O(1) extra (output array not counted)
```

Because:
- The `suff` array is the output array itself.
- Only a single variable `mul` is used for running product.

---

# 💻 Code

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> suff;
        int mul = 1;

        for (int i = nums.size() - 1; i >= 0; i--) {
            suff.push_back(mul);
            mul *= nums[i];
        }

        reverse(suff.begin(), suff.end());

        mul = 1;
        for (int i = 0; i < nums.size(); i++) {
            suff[i] *= mul;
            mul *= nums[i];
        }

        return suff;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Array with a zero

```cpp
nums = [1, 2, 0, 4]
// Output: [0, 0, 8, 0]
```

---

✅ Array with two zeros

```cpp
nums = [0, 0, 3]
// Output: [0, 0, 0]
```

---

✅ Two elements

```cpp
nums = [3, 5]
// Output: [5, 3]
```

---

✅ All ones

```cpp
nums = [1, 1, 1, 1]
// Output: [1, 1, 1, 1]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

The product of all elements except self at index `i` = **prefix product up to i-1** × **suffix product from i+1**.

By computing suffix first (right to left) and then multiplying with a running prefix (left to right), we achieve `O(n)` time with `O(1)` extra space.

---

## Common Mistakes

❌ Using division:

The problem explicitly says **no division operator**. A division-based approach would also fail when zeros are present.

---

❌ Forgetting to reverse the suffix array:

Since we build the suffix array by pushing from right to left, it's in reverse order. The `reverse()` step is essential.

---

## Related Problems

- 42 — Trapping Rain Water (prefix-suffix pattern)
- 152 — Maximum Product Subarray
- 1352 — Product of the Last K Numbers

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Compute something for each index that depends on all other elements
- Prefix-suffix decomposition
- Avoid division

Think:

```cpp
Prefix-Suffix Product Pattern
```

---
