# 136. Single Number

[Link to LeetCode Problem](https://leetcode.com/problems/single-number/)

---

## 1. 📝 Problem Statement

Given a **non-empty** array of integers `nums`, every element appears **twice** except for one. Find that single one.

You must implement a solution with:
- **O(n)** time complexity.
- **O(1)** extra space.

### Example

```
Input:  nums = [2, 2, 1]
Output: 1

Input:  nums = [4, 1, 2, 1, 2]
Output: 4

Input:  nums = [1]
Output: 1
```

### Constraints
- `1 <= nums.length <= 3 × 10⁴`
- `-3 × 10⁴ <= nums[i] <= 3 × 10⁴`
- Every element appears exactly twice except one.

---

## 2. 💡 Intuition

### How should I think about this problem?

The key insight is a property of **XOR** (exclusive OR):

```
a ^ a = 0     (any number XOR itself is 0)
a ^ 0 = a     (any number XOR 0 is itself)
XOR is commutative and associative (order doesn't matter)
```

### Key Observations

1. **Pairs cancel out**: If you XOR all numbers together, every pair `(a, a)` becomes `0`.
2. **Only the single number survives**: After all pairs cancel, only the unique number remains.
3. **Order doesn't matter**: XOR is commutative — `a ^ b ^ a = a ^ a ^ b = 0 ^ b = b`.

### Visualization

```
nums = [4, 1, 2, 1, 2]

XOR all: 4 ^ 1 ^ 2 ^ 1 ^ 2
       = 4 ^ (1 ^ 1) ^ (2 ^ 2)
       = 4 ^ 0 ^ 0
       = 4 ✅
```

---

## 3. 🐢 Brute Force Approach

### Idea 1: Nested Loops
For each element, check if it appears again in the array. If not, it's the answer.

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            bool found = false;
            for (int j = 0; j < nums.size(); j++) {
                if (i != j && nums[i] == nums[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) return nums[i];
        }
        return -1;  // should never reach here
    }
};
```

- **Time**: `O(n²)`
- **Space**: `O(1)`

### Idea 2: Hash Map
Count occurrences. Return the one with count 1.

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> freq;
        for (int x : nums) freq[x]++;
        for (auto& [key, val] : freq) {
            if (val == 1) return key;
        }
        return -1;
    }
};
```

- **Time**: `O(n)`
- **Space**: `O(n)` — violates the O(1) space constraint!

---

## 4. 🚀 Optimal Approach — XOR

### Logic (Step-by-Step)

1. **Initialize `result = 0`**.
2. **XOR every element** in the array with `result`.
3. **Return `result`** — it holds the single number.

### Why does it work?

Three XOR properties make this work:

| Property | Example |
|----------|---------|
| **Self-cancellation** | `a ^ a = 0` |
| **Identity** | `a ^ 0 = a` |
| **Commutativity** | `a ^ b = b ^ a` (order doesn't matter) |

Since every number except one appears twice:
- All paired numbers XOR to `0`.
- The single number XOR with `0` gives itself.

### 🔍 Dry Run

```
Input: nums = [4, 1, 2, 1, 2]

result = 0

i=0: result = 0 ^ 4 = 4
     Binary: 000 ^ 100 = 100

i=1: result = 4 ^ 1 = 5
     Binary: 100 ^ 001 = 101

i=2: result = 5 ^ 2 = 7
     Binary: 101 ^ 010 = 111

i=3: result = 7 ^ 1 = 6
     Binary: 111 ^ 001 = 110

i=4: result = 6 ^ 2 = 4
     Binary: 110 ^ 010 = 100

Output: 4 ✅
```

Notice: 1 appeared at i=1 and i=3 (cancelled). 2 appeared at i=2 and i=4 (cancelled). Only 4 survived.

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;              // initialize to 0 (XOR identity)
        
        for (int i = 0; i < nums.size(); i++) {
            result = result ^ nums[i];   // XOR each element
        }
        
        return result;               // only the single number remains
    }
};
```

### Even shorter version:

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int x : nums) result ^= x;   // ^= is shorthand for result = result ^ x
        return result;
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `result` | Accumulator — XORs all elements; pairs cancel, single remains |
| `i` / `x` | Loop variable to iterate through each element |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **XOR / Bit Manipulation**

This is the classic **XOR cancellation** pattern.

### When to use:
- "Find the element that appears once / odd number of times."
- "All elements appear twice except one."
- Need O(1) space with O(n) time.

### XOR Truth Table (for reference)

| A | B | A ^ B |
|---|---|-------|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

### Key XOR Properties

```
a ^ a = 0          (self-cancellation)
a ^ 0 = a          (identity)
a ^ b ^ a = b      (commutativity + cancellation)
a ^ b = b ^ a      (commutative)
(a ^ b) ^ c = a ^ (b ^ c)  (associative)
```

| Pattern | How it applies |
|---------|---------------|
| **XOR** | Pairs cancel to 0, single number survives |
| **Bit Manipulation** | Operates at the bit level for O(1) space |
| **Mathematical Trick** | Exploits algebraic properties of XOR |

> 🧠 **Mental Model**: "XOR is a toggle. Toggling a bit twice returns it to original. Only the unpaired bits survive."

---

## 7. ⚠️ Common Mistakes

### ❌ Initializing result to nums[0] instead of 0
```cpp
// WRONG: skips the first element and double-processes it
int result = nums[0];
for (int i = 0; i < n; i++) result ^= nums[i];
// result now has nums[0] XORed 3 times (0→initial, i=0, but wait that's wrong)

// CORRECT
int result = 0;  // identity element for XOR
```

Actually, if you initialize to `nums[0]`, you must start the loop from `i = 1`:
```cpp
int result = nums[0];
for (int i = 1; i < n; i++) result ^= nums[i];  // this is also correct
```

### ❌ Using addition/subtraction instead of XOR
```cpp
// WRONG approach (overflow risk for large numbers):
// sum of all unique * 2 - sum of array
// This works mathematically but can overflow

// CORRECT: XOR has no overflow risk
```

### ❌ Forgetting that XOR works with negative numbers too
XOR works on bit representations, so it handles negative numbers correctly (two's complement).

### ❌ Thinking this only works for sorted arrays
XOR is commutative — order doesn't matter. No sorting needed.

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "What if every element appears THREE times except one?" (LeetCode 137)
**Answer**: XOR alone won't work. Use **bitwise counting** — count bits at each position modulo 3. Or use two variables to simulate a base-3 counter.

### Q2: "What if TWO elements appear once?" (LeetCode 260)
**Answer**: XOR all → gives `a ^ b`. Find a set bit (differs between `a` and `b`). Use it to partition the array into two groups. XOR each group separately.

### Q3: "Can you find the missing number from 0 to n?" (LeetCode 268)
**Answer**: XOR all numbers from `0` to `n`, then XOR all array elements. Result is the missing number (same cancellation principle).

### Q4: "What if the array is very large and stored on disk?"
**Answer**: XOR is a **streaming operation** — process one element at a time, O(1) memory. Perfect for disk or network streams.

### Q5: "Prove that XOR is commutative and associative."
**Answer**: XOR operates independently on each bit position. For each bit: it's just addition mod 2, which is commutative and associative.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Single pass through the array. Each element XORed once.

### Space Complexity: `O(1)`
- Only one integer variable (`result`). No extra data structures.

This is the **theoretically optimal** solution — you must read every element at least once (Ω(n)), and you can't use less than O(1) space.

---
