# 1. Two Sum

[Link to LeetCode Problem](https://leetcode.com/problems/two-sum/)

---

## 📝 Problem Statement

Given an array of integers `nums` and an integer `target`, return the indices of the two numbers such that they add up to the target.

You may assume that:
- Exactly one solution exists.
- You cannot use the same element twice.

### Example

```cpp
Input:
nums = [2,7,11,15]
target = 9

Output:
[0,1]
```

Because:

```cpp
nums[0] + nums[1] = 2 + 7 = 9
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

The most straightforward method is:
- Check every pair of elements.
- If their sum equals the target, return their indices.

### Why is it inefficient?

Because for every element, we iterate through the remaining array.

This leads to:

```cpp
O(n²)
```

time complexity.

---

## 2. Optimized Approach (Hash Map)

### Pattern Used

```cpp
Hash Map + Complement Search
```

### Main Idea

For every number:

```cpp
find = target - nums[i]
```

If `find` already exists in the hash map, then:

```cpp
nums[i] + find = target
```

So we immediately return the indices.

Otherwise, store the current element in the map for future lookup.

---

## Step-by-Step Logic

1. Create a hash map:
   - Key → array value
   - Value → index

2. Traverse the array.

3. For each element:
   - Compute complement:
   
```cpp
find = target - nums[i]
```

4. Check if complement exists in map:
   - YES → return answer
   - NO → store current element in map

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- We traverse the array once.
- Hash map lookup takes constant time on average.

---

## Space Complexity

```cpp
O(n)
```

Because:
- We store elements inside the hash map.

---

# 💻 Code

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        unordered_map<int,int> mp;

        for(int i = 0; i < nums.size(); i++) {

            int find = target - nums[i];

            // If complement already exists
            if(mp.find(find) != mp.end()) {
                return {mp[find], i};
            }

            // Store current number with index
            mp[nums[i]] = i;
        }

        return {-1, -1};
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Duplicate numbers

```cpp
nums = [3,3]
target = 6
```

---

✅ Negative numbers

```cpp
nums = [-1,-2,-3,-4,-5]
target = -8
```

---

✅ Large inputs

Efficient due to:

```cpp
O(n)
```

time complexity.

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Instead of checking all pairs:
- Store previously seen numbers.
- Search for complement in constant time.

---

## Common Mistakes

❌ Using:

```cpp
mp[find]
```

without checking existence.

This may insert unwanted keys into the map.

Correct way:

```cpp
mp.find(find) != mp.end()
```

---

❌ Using:

```cpp
==
```

instead of:

```cpp
=
```

while inserting into map.

---

## Related Problems

- Contains Duplicate
- Two Sum II
- 3Sum
- 4Sum
- Subarray Sum Equals K
- Longest Consecutive Sequence

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Find pair with target
- Complement exists?
- Fast lookup required

Think:

```cpp
Hash Map
```

---