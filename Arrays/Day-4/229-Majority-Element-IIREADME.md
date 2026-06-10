# 229. Majority Element II

[Link to LeetCode Problem](https://leetcode.com/problems/majority-element-ii/)

---

## 📝 Problem Statement

Given an integer array `nums` of size `n`, return all elements that appear **more than ⌊n/3⌋ times**.

### Example

```cpp
Input:  nums = [3,2,3]
Output: [3]

Input:  nums = [1,2]
Output: [1,2]
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Count frequency of each element using a hash map, then filter those with count > n/3.

### Why is it suboptimal?

```cpp
O(n) time, O(n) space
```

Uses extra space for the hash map.

---

## 2. Optimized Approach (Boyer-Moore Voting — Extended)

### Pattern Used

```cpp
Boyer-Moore Voting Algorithm extended to k = 3 candidates
```

### Main Idea

There can be **at most 2** elements appearing more than n/3 times. Maintain two candidate-count pairs. In one pass, vote for/against candidates. Then verify both candidates with a second pass.

---

## Step-by-Step Logic

**Phase 1 — Find Candidates:**

For each element:
- If it equals `maj1`, increment `cnt1`.
- Else if it equals `maj2`, increment `cnt2`.
- Else if `cnt1 == 0`, set `maj1 = nums[i]`, `cnt1 = 1`.
- Else if `cnt2 == 0`, set `maj2 = nums[i]`, `cnt2 = 1`.
- Else decrement both `cnt1` and `cnt2`.

**Phase 2 — Verify Candidates:**

Count actual occurrences of `maj1` and `maj2`. Add to result if count > n/3.

---

### Dry Run

```cpp
nums = [1, 1, 1, 3, 3, 2, 2, 2]

Phase 1:
i=0: maj1=1, cnt1=1
i=1: cnt1=2
i=2: cnt1=3
i=3: maj2=3, cnt2=1
i=4: cnt2=2
i=5: cnt1--, cnt2-- → cnt1=2, cnt2=1
i=6: cnt1--, cnt2-- → cnt1=1, cnt2=0
i=7: maj2=2, cnt2=1

Phase 2: count(1)=3 > 8/3=2 ✅, count(2)=3 > 2 ✅
Output: [1, 2] ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Two linear passes over the array.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only 4 extra variables: `maj1`, `maj2`, `cnt1`, `cnt2`.

---

# 💻 Code

```cpp
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int cnt1 = 0, maj1 = 0;
        int cnt2 = 0, maj2 = 0;

        for (int i = 0; i < nums.size(); i++) {
            if (maj1 == nums[i])
                cnt1++;
            else if (maj2 == nums[i])
                cnt2++;
            else if (cnt1 == 0) {
                maj1 = nums[i];
                cnt1 = 1;
            } else if (cnt2 == 0) {
                maj2 = nums[i];
                cnt2 = 1;
            } else {
                cnt1--;
                cnt2--;
            }
        }

        cnt1 = cnt2 = 0;
        for (int x : nums) {
            if (x == maj1) cnt1++;
            else if (x == maj2) cnt2++;
        }

        vector<int> ans;
        int n = nums.size();
        if (cnt1 > n / 3) ans.push_back(maj1);
        if (cnt2 > n / 3) ans.push_back(maj2);

        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ No majority element:

```cpp
nums = [1, 2, 3]
// Output: []  (each appears once, 1 is not > 3/3=1)
```

---

✅ Two majority elements:

```cpp
nums = [1, 2]
// Output: [1, 2]
```

---

✅ One majority element:

```cpp
nums = [3, 2, 3]
// Output: [3]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

At most **⌊n/k⌋** majority elements can exist for threshold `n/k`. For `n/3`, maintain **2 candidates**. Always reset counts to 0 before the verification pass.

---

## Common Mistakes

❌ Forgetting the **verification pass** — Phase 1 only finds candidates, not confirmed majority elements.

❌ Comparing `maj1 == nums[i]` before checking `cnt1 == 0` — the order of if-else branches matters!

---

## Related Problems

- 169 — Majority Element (> n/2, one candidate)

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Elements appearing more than n/k times
- O(1) space required

Think:

```cpp
Boyer-Moore Voting — maintain (k-1) candidates, then verify
```

---
