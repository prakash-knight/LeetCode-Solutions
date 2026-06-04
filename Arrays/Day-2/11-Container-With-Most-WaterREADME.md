# 11. Container With Most Water

[Link to LeetCode Problem](https://leetcode.com/problems/container-with-most-water/)

---

## 📝 Problem Statement

You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i`-th line are `(i, 0)` and `(i, height[i])`.

Find two lines that together with the x-axis form a container that holds the most water.

Return the maximum amount of water a container can store.

### Example

```cpp
Input:
height = [1,8,6,2,5,4,8,3,7]

Output:
49
```

Because:

```cpp
Lines at index 1 (height=8) and index 8 (height=7):
Area = (8 - 1) × min(8, 7) = 7 × 7 = 49
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

The most straightforward method is:
- Check every pair of lines.
- Calculate the area for each pair.
- Track the maximum.

### Why is it inefficient?

```cpp
O(n²)
```

time complexity due to nested loops.

---

## 2. Optimized Approach (Two Pointers)

### Pattern Used

```cpp
Two Pointers (Greedy Shrink)
```

### Main Idea

Start with the widest container (pointers at both ends).

```cpp
area = (right - left) × min(height[left], height[right])
```

Then shrink by moving the **shorter** line inward:
- Moving the shorter line might find a taller one → potentially more water.
- Moving the taller line can only decrease or maintain area (width decreases, height can't help).

### Why does this work?

The key insight: if `height[left] < height[right]`, then `left` is the bottleneck. No matter what line we pair `left` with to the left of `right`, the height is still limited by `height[left]`, and the width only gets smaller. So we can safely skip all those pairs.

---

## Step-by-Step Logic

1. Initialize:

```cpp
s = 0                  // left pointer
e = h.size() - 1       // right pointer
maxi = INT_MIN         // maximum area
```

2. While `s <= e`:
   - Calculate area: `(e - s) × min(h[s], h[e])`
   - Update maximum.
   - Move the pointer with the **shorter** height inward.

3. Return `maxi`.

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Each pointer moves at most n times total.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only pointer variables used.

---

# 💻 Code

```cpp
class Solution {
public:
    int maxArea(vector<int>& h) {
        int s = 0, e = h.size() - 1, maxi = INT_MIN;

        while (s <= e) {
            int area = (e - s) * min(h[s], h[e]);
            maxi = max(area, maxi);

            if (h[s] < h[e]) {
                s++;
            } else {
                e--;
            }
        }

        return maxi;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Two elements

```cpp
height = [1, 1]
// Output: 1
```

---

✅ Decreasing heights

```cpp
height = [5, 4, 3, 2, 1]
// Output: 6 → lines at index 0 and 3: (3-0) × min(5,2) = 6
```

---

✅ All same heights

```cpp
height = [4, 4, 4, 4]
// Output: 12 → (3-0) × 4 = 12
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Instead of checking all pairs:
- Start with the widest container.
- Always move the shorter pointer — it's the bottleneck.
- The taller pointer can never do better with a narrower width.

---

## Common Mistakes

❌ Moving the **taller** pointer:

```cpp
// WRONG: moving the taller one can only lose width
if (h[s] > h[e]) s++;
```

Always move the shorter one.

---

❌ Confusing with Trapping Rain Water:

| Problem | What to calculate |
|---------|-------------------|
| Container With Most Water | Max area between **two** lines |
| Trapping Rain Water | Total water trapped between **all** lines |

---

## Related Problems

- Trapping Rain Water
- Two Sum II (sorted array, two pointers)
- 3Sum

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Maximize area/product with two boundaries
- Optimal pair from two ends
- Greedy elimination of suboptimal choices

Think:

```cpp
Two Pointers from Both Ends + Move the Weaker Side
```

---
