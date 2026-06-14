# 503. Next Greater Element II

[Link to LeetCode Problem](https://leetcode.com/problems/next-greater-element-ii/)

---

## 1. 📝 Problem Statement

Given a **circular** integer array `nums` (i.e., the next element of `nums[nums.length - 1]` is `nums[0]`), return the **next greater number** for every element in `nums`.

The next greater number of a number `x` is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return `-1`.

### Example

```
Input:  nums = [1,2,1]
Output: [2,-1,2]

Explanation:
- 1 → next greater is 2
- 2 → no greater element in circular traversal → -1
- 1 → next greater circularly is 2
```

### Constraints
- `1 <= nums.length <= 10⁴`
- `-10⁹ <= nums[i] <= 10⁹`

---

## 2. 💡 Intuition

### How should I think about this problem?

This is **Next Greater Element I** but on a **circular array**. The trick: simulate two passes by **doubling** the array (or using modulo). After doubling, it becomes a standard NGE problem — traverse right to left with a monotonic stack.

### Key Observations

1. **Doubling trick**: Append the array to itself → `[1,2,1,1,2,1]`. Now any "wrapping around" is captured as a normal right-side lookup.
2. The answer only applies to the first `n` indices.
3. **Resize** the result to `n` at the end.

### Visualization

```
nums = [1, 2, 1]
doubled = [1, 2, 1, 1, 2, 1]

Traverse right to left with monotonic stack:
i=5: num=1, stack=[] → ans[5]=-1, push 5
i=4: num=2, pop 5(1<2) → stack=[], ans[4]=-1, push 4
i=3: num=1, top=4,nums[4]=2>1 → ans[3]=2, push 3
i=2: num=1, top=3,nums[3]=1, pop(1<=1)→ top=4,nums[4]=2>1 → ans[2]=2, push 2
i=1: num=2, pop 2(1<2),pop 3(1<2),pop 4(2<=2)→ stack=[], ans[1]=-1, push 1
i=0: num=1, top=1,nums[1]=2>1 → ans[0]=2, push 0

ans = [2,-1,2,2,-1,-1]
resize to n=3 → [2,-1,2] ✅
```

---

## 3. 🐢 Brute Force Approach

For each element, scan circularly to find the next greater.

```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (nums[(i + j) % n] > nums[i]) {
                    ans[i] = nums[(i + j) % n];
                    break;
                }
            }
        }
        return ans;
    }
};
```

- **Time**: `O(n²)`
- **Space**: `O(1)` extra

---

## 4. 🚀 Optimal Approach — Monotonic Stack + Array Doubling

### Logic (Step-by-Step)

1. **Double the array**: append `nums` to itself.
2. Traverse the doubled array **right to left** with a monotonic decreasing stack.
3. For each position `i`:
   - Pop while `nums[stack.top()] <= nums[i]`.
   - If stack non-empty → `ans[i] = nums[stack.top()]`.
   - Else → `ans[i] = -1`.
   - Push `i`.
4. **Resize** `ans` to original length `n`.

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        int n = nums.size();

        // Double the array
        vector<int> temp = nums;
        for (auto x : temp) {
            nums.push_back(x);
        }

        vector<int> ans(nums.size());
        for (int i = nums.size() - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }
            if (st.empty()) {
                ans[i] = -1;
            } else {
                ans[i] = nums[st.top()];
            }
            st.push(i);
        }

        ans.resize(n);
        return ans;
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `st` | Monotonic decreasing stack of indices |
| `temp` | Copy of original array for doubling |
| `ans` | Result array (doubled, then resized to n) |

---

## 6. 💡 Alternative — Modulo (No Array Doubling)

```cpp
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> st;

        for (int i = 2 * n - 1; i >= 0; i--) {
            int idx = i % n;
            while (!st.empty() && nums[st.top()] <= nums[idx])
                st.pop();
            if (!st.empty()) ans[idx] = nums[st.top()];
            st.push(idx);
        }

        return ans;
    }
};
```

- More space-efficient (no extra vector), same time complexity.

---

## 7. 🧩 Pattern Recognition

### Primary Pattern: **Monotonic Stack — Next Greater Element (Circular)**

### When to use:
- Standard NGE but on circular/wrapped arrays.

| Pattern | How it applies |
|---------|---------------|
| **Monotonic Decreasing Stack** | Pops elements that can't be NGE answers |
| **Array Doubling / Modulo** | Simulates circular traversal linearly |

> 🧠 **Mental Model**: "For a circular array, the second pass (doubling) lets elements at the beginning 'see' elements at the end."

---

## 8. ⚠️ Common Mistakes

### ❌ Using `<` instead of `<=` in the pop condition
For NGE, pop when `nums[top] <= nums[i]` (equal elements to the left can't have the current equal element as their NGE).

### ❌ Forgetting to resize
The doubled array gives `2n` answers. Only the first `n` are relevant.

### ❌ Modifying input array permanently
The doubling approach modifies `nums` in place. If the original array is needed later, save a copy first.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Each of the `2n` elements is pushed/popped at most once.

### Space Complexity: `O(n)`
- Stack: O(n), doubled array: O(n).
