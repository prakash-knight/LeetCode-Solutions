# 118. Pascal's Triangle

[Link to LeetCode Problem](https://leetcode.com/problems/pascals-triangle/)

---

## 📝 Problem Statement

Given an integer `numRows`, return the first `numRows` of **Pascal's triangle**.

In Pascal's triangle, each number is the sum of the two numbers directly above it.

### Example

```cpp
Input:  numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
```

---

# 💡 Intuition & Approach

## 1. Row-by-Row Construction

### Pattern Used

```cpp
Each element (except borders) = sum of two elements from the previous row
```

### Main Idea

- Row 1: `[1]`
- Row 2: `[1, 1]`
- Row j (j ≥ 3): first and last elements are `1`; middle element `i` = `ans[j-2][i-1] + ans[j-2][i]`

Build the triangle iteratively, using the last stored row to compute the next.

---

## Step-by-Step Logic

1. Push `{1}` as the first row.
2. If `n == 1`, return.
3. Push `{1, 1}` as the second row.
4. If `n == 2`, return.
5. For rows `3` to `n`:
   - Create a `temp` vector.
   - Index `0` and last index get `1`.
   - Middle indices: `temp[i] = ans[j-2][i-1] + ans[j-2][i]`.
   - Push `temp` into `ans`.

---

### Dry Run

```cpp
n = 4

ans = [[1], [1,1]]

j=3: temp = [1, 1+1, 1] = [1, 2, 1]  → ans[2]
j=4: temp = [1, 1+2, 2+1, 1] = [1, 3, 3, 1] → ans[3]

Output: [[1],[1,1],[1,2,1],[1,3,3,1]] ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n²)
```

Because:
- Row `j` has `j` elements; total elements = 1+2+…+n = n(n+1)/2 = O(n²).

---

## Space Complexity

```cpp
O(n²)
```

Because:
- Storing the entire triangle.

---

# 💻 Code

```cpp
class Solution {
public:
    vector<vector<int>> generate(int n) {
        vector<vector<int>> ans;
        ans.push_back({1});
        if (n == 1) return ans;

        ans.push_back({1, 1});
        if (n == 2) return ans;

        for (int j = 3; j <= n; j++) {
            vector<int> temp;
            for (int i = 0; i < j; i++) {
                if (i == 0 || i == j - 1) {
                    temp.push_back(1);
                } else {
                    int x = ans[j - 2][i - 1] + ans[j - 2][i];
                    temp.push_back(x);
                }
            }
            ans.push_back(temp);
        }
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single row:

```cpp
n = 1
// Output: [[1]]
```

---

✅ Two rows:

```cpp
n = 2
// Output: [[1],[1,1]]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Index reference: when building row `j` (1-indexed), it is stored at `ans[j-1]`. The **previous row** is `ans[j-2]`.

---

## Common Mistakes

❌ Off-by-one error when referencing `ans[j-2]` — make sure row `j` starts from 3, not 2.

---

## Related Problems

- 119 — Pascal's Triangle II (only return the kth row)

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Build a triangle row by row
- Each cell depends on cells from the previous row

Think:

```cpp
Iterative row construction — borders = 1, inner = sum of two above
```

---
