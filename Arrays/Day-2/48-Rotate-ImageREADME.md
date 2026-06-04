# 48. Rotate Image

[Link to LeetCode Problem](https://leetcode.com/problems/rotate-image/)

---

## 📝 Problem Statement

You are given an `n x n` 2D matrix representing an image. Rotate the image by **90 degrees clockwise**.

You have to rotate the image **in-place**, meaning you must modify the input matrix directly.

### Example

```cpp
Input:
matrix = [[1,2,3],
           [4,5,6],
           [7,8,9]]

Output:
[[7,4,1],
 [8,5,2],
 [9,6,3]]
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Use an extra matrix:
- Place element at `(i, j)` in position `(j, n-1-i)` of the new matrix.

### Why can we do better?

The problem explicitly asks for **in-place** rotation. We need O(1) extra space.

---

## 2. Optimized Approach (Transpose + Reverse)

### Pattern Used

```cpp
Transpose + Reverse Rows
```

### Main Idea

A 90° clockwise rotation is equivalent to two simple operations:

**Step 1: Transpose the matrix** (swap rows and columns)

```cpp
mat[i][j] ↔ mat[j][i]
```

**Step 2: Reverse each row**

```cpp
[7,4,1]     →     [1,4,7] after transpose
                   [7,4,1] after reverse ← correct!
```

### Visual Example

```
Original:       Transpose:       Reverse Rows:
1 2 3            1 4 7            7 4 1
4 5 6    →       2 5 8    →       8 5 2
7 8 9            3 6 9            9 6 3
```

---

## Step-by-Step Logic

1. **Transpose** — swap `mat[i][j]` with `mat[j][i]`:
   - Only iterate upper triangle (`j = i+1` to `n`) to avoid double swapping.

2. **Reverse each row** — use `reverse()` on each row.

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n²)
```

Because:
- Transpose takes O(n²).
- Reversing all rows takes O(n²).

---

## Space Complexity

```cpp
O(1)
```

Because:
- All operations are done in-place using swaps.

---

# 💻 Code

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& mat) {
        // Step 1: Transpose
        for (int i = 0; i < mat.size(); i++) {
            for (int j = i + 1; j < mat[0].size(); j++) {
                swap(mat[i][j], mat[j][i]);
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < mat.size(); i++) {
            reverse(mat[i].begin(), mat[i].end());
        }
    }
};
```

---

# 🔍 Edge Cases Handled

✅ 1x1 matrix

```cpp
matrix = [[1]]
// Output: [[1]] (no change)
```

---

✅ 2x2 matrix

```cpp
matrix = [[1,2],
           [3,4]]
// Output: [[3,1],
//          [4,2]]
```

---

✅ Large matrix

Works efficiently due to O(1) space and O(n²) time.

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Instead of complex index mapping:
- **Transpose + Reverse = 90° clockwise rotation**
- **Transpose + Reverse columns = 90° counter-clockwise rotation**

---

## Rotation Cheat Sheet

| Rotation | Operation |
|----------|-----------|
| 90° clockwise | Transpose → Reverse rows |
| 90° counter-clockwise | Transpose → Reverse columns |
| 180° | Reverse rows → Reverse columns |

---

## Common Mistakes

❌ Transposing the full matrix (both triangles):

```cpp
// WRONG: swapping twice = no change
for (int j = 0; j < n; j++)  // ← should be j = i+1
```

---

❌ Confusing transpose with rotation:

Transpose alone ≠ rotation. You need the reverse step too.

---

## Related Problems

- Spiral Matrix
- Spiral Matrix II
- Determine Whether Matrix Can Be Obtained By Rotation

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Rotate matrix 90°/180°/270°
- In-place matrix transformation

Think:

```cpp
Transpose + Reverse
```

---
