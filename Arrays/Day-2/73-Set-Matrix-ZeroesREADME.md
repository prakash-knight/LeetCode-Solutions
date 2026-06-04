# 73. Set Matrix Zeroes

[Link to LeetCode Problem](https://leetcode.com/problems/set-matrix-zeroes/)

---

## 📝 Problem Statement

Given an `m x n` integer matrix, if an element is `0`, set its entire row and column to `0`.

You must do it **in place**.

### Example

```cpp
Input:
matrix = [[1,1,1],
           [1,0,1],
           [1,1,1]]

Output:
[[1,0,1],
 [0,0,0],
 [1,0,1]]
```

Because:

```cpp
Element at (1,1) is 0 → entire row 1 and column 1 set to 0.
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

- Use a copy of the matrix.
- Scan for zeros, then zero out rows/columns in the copy.

### Why can we do better?

```cpp
O(m × n) extra space for the copy.
```

---

## 2. Better Approach (Marker Arrays)

### Pattern Used

```cpp
Row/Column Marker Arrays
```

### Main Idea

Use two separate arrays to mark which rows and columns need to be zeroed:

```cpp
row[i] = 1   → row i should be zeroed
col[j] = 1   → column j should be zeroed
```

**Pass 1:** Scan the matrix and mark rows/columns containing zeros.

**Pass 2:** Zero out cells based on markers.

---

## Step-by-Step Logic

1. Create marker arrays:

```cpp
vector<int> row(n, 0);    // n rows
vector<int> col(m, 0);    // m columns
```

2. **First pass** — find all zeros:
   - If `mat[i][j] == 0` → set `row[i] = 1` and `col[j] = 1`

3. **Second pass** — apply zeros:
   - If `row[i] == 1` OR `col[j] == 1` → set `mat[i][j] = 0`

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(m × n)
```

Because:
- Two passes through the entire matrix.

---

## Space Complexity

```cpp
O(m + n)
```

Because:
- Two marker arrays of size `m` and `n`.

---

# 💻 Code

```cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();

        vector<int> row(n, 0);
        vector<int> col(m, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 0) {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (row[i] == 1) mat[i][j] = 0;
                if (col[j] == 1) mat[i][j] = 0;
            }
        }
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Multiple zeros in the matrix

```cpp
matrix = [[0,1,0],
           [1,1,1],
           [0,1,1]]
```

---

✅ No zeros in the matrix

```cpp
matrix = [[1,2,3],
           [4,5,6]]
// Output: unchanged
```

---

✅ Single row or column

```cpp
matrix = [[0, 1, 2, 0]]
// Output: [[0, 0, 0, 0]]
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Instead of modifying the matrix while scanning:
- First **mark** which rows and columns need zeroing.
- Then **apply** the zeros in a second pass.
- This avoids cascading zeros (zeroing an element that then triggers more zeroing).

---

## Follow-Up: O(1) Space Solution

Use the **first row** and **first column** of the matrix itself as markers:

```cpp
mat[0][j] = 0   → column j should be zeroed
mat[i][0] = 0   → row i should be zeroed
```

Use separate boolean flags for whether the first row/column themselves should be zeroed.

---

## Common Mistakes

❌ Modifying the matrix during scanning:

```cpp
// WRONG: setting zeros while still scanning
if (mat[i][j] == 0) {
    // zero out row immediately ← causes false positives
}
```

---

## Related Problems

- Game of Life
- Spiral Matrix

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Mark and apply operations on matrix
- In-place matrix modification based on conditions
- Avoid cascading updates

Think:

```cpp
Marker Arrays (or use matrix itself as markers for O(1) space)
```

---
