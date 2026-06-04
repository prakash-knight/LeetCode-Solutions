# 560. Subarray Sum Equals K

[Link to LeetCode Problem](https://leetcode.com/problems/subarray-sum-equals-k/)

---

## 📝 Problem Statement

Given an array of integers `nums` and an integer `k`, return the total number of subarrays whose sum equals `k`.

A subarray is a contiguous non-empty sequence of elements within an array.

### Example

```cpp
Input:
nums = [1,1,1]
k = 2

Output:
2
```

Because:

```cpp
Subarrays [1,1] (index 0-1) and [1,1] (index 1-2) both sum to 2.
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

The most straightforward method is:
- Check every possible subarray.
- Compute its sum.
- If the sum equals `k`, increment the count.

### Why is it inefficient?

Because for every starting index, we iterate through all ending indices.

This leads to:

```cpp
O(n²)
```

time complexity.

---

## 2. Optimized Approach (Prefix Sum + Hash Map)

### Pattern Used

```cpp
Prefix Sum + Hash Map (Complement Search)
```

### Main Idea

If we maintain a running prefix sum, then:

```cpp
sum(i, j) = prefix[j] - prefix[i-1]
```

So for a subarray sum to equal `k`:

```cpp
prefix[j] - prefix[i-1] = k
→ prefix[i-1] = prefix[j] - k
```

If `prefix[j] - k` has been seen before, then there exist subarrays ending at `j` with sum `k`.

The count of such previous prefix sums gives us the number of valid subarrays.

---

## Step-by-Step Logic

1. Create a hash map to store:
   - Key → prefix sum value
   - Value → frequency of that prefix sum

2. Initialize:

```cpp
prefix[0] = 1   // empty subarray has sum 0
sum = 0
count = 0
```

3. For each element:
   - Add it to running sum.
   - Check if `sum - k` exists in map:
     - YES → add its frequency to count
   - Store current sum in map (increment frequency).

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Single pass through the array.
- Hash map operations are O(1) on average.

---

## Space Complexity

```cpp
O(n)
```

Because:
- Hash map can store up to `n` distinct prefix sums.

---

# 💻 Code

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefix;

        prefix[0] = 1;

        int sum = 0;
        int count = 0;

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];

            if (prefix.find(sum - k) != prefix.end()) {
                count += prefix[sum - k];
            }

            prefix[sum]++;
        }

        return count;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Negative numbers in array

```cpp
nums = [-1, -1, 1]
k = 0
```

---

✅ Single element equals k

```cpp
nums = [5]
k = 5
```

---

✅ Multiple overlapping subarrays

```cpp
nums = [1, 2, 3]
k = 3
// Subarrays: [1,2] and [3]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Instead of recalculating subarray sums:
- Use prefix sums to reduce the problem to a complement search.
- This is similar to Two Sum but on prefix sums.

---

## Common Mistakes

❌ Forgetting to initialize:

```cpp
prefix[0] = 1
```

Without this, subarrays starting from index 0 that sum to `k` are missed.

---

❌ Using sliding window for this problem.

Sliding window does NOT work here because:
- Array can contain negative numbers.
- Window shrinking logic breaks with negatives.

---

## Related Problems

- Two Sum
- Continuous Subarray Sum
- Subarray Sums Divisible by K
- Binary Subarrays With Sum

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Count subarrays with a given sum
- Subarray sum property with negatives allowed
- Prefix sum + frequency

Think:

```cpp
Prefix Sum + Hash Map
```

---
