# 496. Next Greater Element I

[Link to LeetCode Problem](https://leetcode.com/problems/next-greater-element-i/)

---

## 1. 📝 Problem Statement

The **next greater element** of some element `x` in an array is the **first greater element** to its right in the array.

You are given two **distinct** integer arrays `nums1` and `nums2`, where `nums1` is a subset of `nums2`. For each `nums1[i]`, find the next greater element in `nums2`. If it does not exist, return `-1`.

### Example

```
Input:  nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1,3,-1]

Explanation:
- 4 → no element to its right in nums2 is greater → -1
- 1 → next greater in nums2 is 3
- 2 → no element to its right in nums2 is greater → -1
```

### Constraints
- `1 <= nums1.length <= nums2.length <= 1000`
- `0 <= nums1[i], nums2[i] <= 10⁴`
- All integers in `nums1` and `nums2` are **unique**.
- All integers in `nums1` also appear in `nums2`.

---

## 2. 💡 Intuition

### How should I think about this problem?

For each element in `nums2`, we want to know "what is the next greater element to my right?" This is a classic **monotonic stack** problem.

### Key Observations

1. Traverse `nums2` from **right to left**.
2. Maintain a **decreasing monotonic stack** of indices.
3. For each `nums2[i]`, pop elements from the stack that are ≤ `nums2[i]` — they can't be the next greater for anything to the left.
4. The stack top (if non-empty) is the next greater element for `nums2[i]`.
5. Store results in a **hash map**: `mp[nums2[i]] = nextGreater`.
6. Look up `nums1` elements in the map.

### Visualization

```
nums2 = [1, 3, 4, 2]
Traverse right to left:

i=3: num=2, stack=[] → mp[2]=-1, push 3 → stack:[3]
i=2: num=4, pop 3 (3<4) → stack=[] → mp[4]=-1, push 2 → stack:[2]
i=1: num=3, pop 2 (2<3) → stack=[] → mp[3]=-1... wait
     Actually 2 < 3, pop → stack=[], mp[3]=-1, push 1 → stack:[1]
     Wait, stack holds INDICES not values...

Let me re-trace with index-based stack:
i=3: nums2[3]=2, stack empty → mp[2]=-1, push 3
i=2: nums2[2]=4, top=3,nums2[3]=2<4 → pop. stack empty → mp[4]=-1, push 2
i=1: nums2[1]=3, top=2,nums2[2]=4>3 → mp[3]=4, push 1
i=0: nums2[0]=1, top=1,nums2[1]=3>1 → mp[1]=3, push 0

mp: {2:-1, 4:-1, 3:4, 1:3}

nums1=[4,1,2] → [-1, 3, -1] ✅
```

---

## 3. 🐢 Brute Force Approach

For each element in `nums1`, find it in `nums2`, then scan right for the next greater element.

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        for (int x : nums1) {
            int idx = find(nums2.begin(), nums2.end(), x) - nums2.begin();
            int res = -1;
            for (int j = idx + 1; j < nums2.size(); j++) {
                if (nums2[j] > x) { res = nums2[j]; break; }
            }
            ans.push_back(res);
        }
        return ans;
    }
};
```

- **Time**: `O(m × n)` where `m = nums1.size()`, `n = nums2.size()`
- **Space**: `O(1)` extra

---

## 4. 🚀 Optimal Approach — Monotonic Stack + Hash Map

### Logic (Step-by-Step)

1. Traverse `nums2` from **right to left**.
2. For each index `i`:
   - Pop from stack while `nums2[stack.top()] < nums2[i]` (they can't be NGE for anything to the left).
   - If stack non-empty → `mp[nums2[i]] = nums2[stack.top()]`.
   - Else → `mp[nums2[i]] = -1`.
   - Push `i`.
3. Build answer by looking up each `nums1[j]` in `mp`.

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        unordered_map<int, int> mp;

        for (int i = nums2.size() - 1; i >= 0; i--) {
            while (!st.empty() && nums2[st.top()] < nums2[i])
                st.pop();

            if (!st.empty())
                mp[nums2[i]] = nums2[st.top()];
            else
                mp[nums2[i]] = -1;

            st.push(i);
        }

        vector<int> ans;
        for (int x : nums1) {
            ans.push_back(mp[x]);
        }

        return ans;
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `st` | Monotonic decreasing stack (stores indices) |
| `mp` | Maps each `nums2` value → its next greater element |
| `ans` | Result array for `nums1` lookups |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Monotonic Stack — Next Greater Element**

This is the canonical **NGE (Next Greater Element)** pattern.

### When to use:
- "Find the next greater/smaller element to the right/left."
- Questions involving stock span, temperature, buildings etc.

| Pattern | How it applies |
|---------|---------------|
| **Monotonic Decreasing Stack** | Pops elements that can no longer be answers |
| **Right-to-left traversal** | Naturally sees "future" elements first |
| **Hash Map lookup** | Quick O(1) answer retrieval for subset queries |

> 🧠 **Mental Model**: "The stack keeps candidates for 'next greater'. When we see a bigger element, all smaller ones in the stack are useless — pop them."

---

## 7. ⚠️ Common Mistakes

### ❌ Traversing left to right
Left-to-right traversal requires more careful bookkeeping. Right-to-left is more intuitive for NGE.

### ❌ Storing values instead of indices in the stack
While for this problem values work (all distinct), for NGE II (circular), indices are necessary.

### ❌ Wrong pop condition (using `<=` instead of `<`)
Pop when `nums2[top] < nums2[i]` (strictly less). Equal elements should NOT be popped (though here all values are distinct, so it doesn't matter).

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "What if nums1 is not a subset of nums2?"
**Answer**: Use `mp.count(x)` to check; return -1 if not found.

### Q2: "What about Next Greater Element II (circular array)?" (LeetCode 503)
**Answer**: Double the array (or use modulo), traverse once right-to-left.

### Q3: "Can you do left-to-right?"
**Answer**: Yes — maintain a stack and a result array. When a new element pops something, that popped element's NGE is the current element.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(m + n)`
- Build map: O(n) — each element pushed/popped at most once.
- Build answer: O(m) — hash map lookup per element.

### Space Complexity: `O(n)`
- Stack: O(n), Hash map: O(n).
