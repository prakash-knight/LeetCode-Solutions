# Quick Sort

---

## 1. 📝 What is Quick Sort?

Quick Sort is a **Divide and Conquer** algorithm:
1. **Pick a pivot** element.
2. **Partition** the array — elements ≤ pivot go left, elements > pivot go right.
3. **Recursively sort** the left and right parts.

After partition, the **pivot is in its final sorted position**. No merge step needed.

### Example

```
Input: [4, 6, 2, 5, 7]    pivot = 7 (last element)

Partition: all elements ≤ 7 go left
[4, 6, 2, 5, 7]   ← 7 is already at correct position

Now sort [4, 6, 2, 5] with pivot = 5
  Elements ≤ 5: [4, 2, 5]
  Elements > 5: [6]
  → [4, 2, 5, 6, 7]

Now sort [4, 2] with pivot = 2
  → [2, 4]

Result: [2, 4, 5, 6, 7] ✅
```

---

## 2. 💡 Intuition

### Core Idea

**"Put the pivot in its correct position. Everything before it is smaller. Everything after it is larger. Then recurse."**

### How does Partition work?

Using the **Lomuto partition** scheme (pivot = last element):

1. Set `i = low - 1` (tracks the boundary of "smaller" elements).
2. Scan with `j` from `low` to `high - 1`.
3. If `arr[j] <= pivot` → increment `i`, swap `arr[i]` with `arr[j]`.
4. After the loop, swap pivot (`arr[high]`) with `arr[i+1]`.
5. Return `i + 1` as pivot's final position.

```
Before partition (pivot=5):
[4, 6, 2, 5, 7]    → pivot = 7 (last)
 i=-1

j=0: 4 ≤ 7 → i=0, swap(arr[0], arr[0]) → [4, 6, 2, 5, 7]
j=1: 6 ≤ 7 → i=1, swap(arr[1], arr[1]) → [4, 6, 2, 5, 7]
j=2: 2 ≤ 7 → i=2, swap(arr[2], arr[2]) → [4, 6, 2, 5, 7]
j=3: 5 ≤ 7 → i=3, swap(arr[3], arr[3]) → [4, 6, 2, 5, 7]

Swap pivot: swap(arr[4], arr[4]) → pivot 7 at index 4

Pivot position: 4 (already at end — all elements < 7)
```

### Key Difference from Merge Sort

| | Merge Sort | Quick Sort |
|---|-----------|------------|
| **Work** | Done in merge step (after recursion) | Done in partition step (before recursion) |
| **Space** | O(n) extra | O(log n) stack only |
| **Stable** | ✅ Yes | ❌ No |

---

## 3. 💻 Code (C++)

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Partition: place pivot at correct position
    // Returns: final index of pivot
    int partition(vector<int>& arr, int low, int high) {

        int pivot = arr[high];     // choose last element as pivot
        int i = low - 1;           // boundary of "smaller" section

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;                          // expand smaller section
                swap(arr[i], arr[j]);         // move element to smaller side
            }
        }

        // Place pivot after all smaller elements
        swap(arr[i + 1], arr[high]);

        return i + 1;             // pivot's final position
    }

    void quickSort(vector<int>& arr, int low, int high) {

        if (low >= high) return;   // base case: 0 or 1 element

        int p = partition(arr, low, high);  // partition and get pivot index

        quickSort(arr, low, p - 1);         // sort left of pivot
        quickSort(arr, p + 1, high);        // sort right of pivot
    }
};

int main() {
    Solution sol;
    vector<int> arr = {4, 6, 2, 5, 7};
    sol.quickSort(arr, 0, arr.size() - 1);

    for (int x : arr) cout << x << " ";
    return 0;
}
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `pivot` | The element being placed at its correct position (`arr[high]`) |
| `i` | Boundary index — everything from `low` to `i` is ≤ pivot |
| `j` | Scanning pointer — checks each element against pivot |
| `p` | Pivot's final position returned by partition |
| `low, high` | Boundaries of current subarray being sorted |

---

## 4. 🧩 Pattern Recognition

### Algorithm Type: **Divide and Conquer, In-place**

### Key Properties

| Property | Value |
|----------|-------|
| **Stable** | ❌ No — partition swaps can change relative order |
| **In-place** | ✅ Yes — O(1) extra space (ignoring recursion stack) |
| **Adaptive** | ❌ No — depends on pivot choice, not input order |
| **Cache-friendly** | ✅ Yes — sequential access pattern |

### When to use Quick Sort?

- **General purpose sorting** — fastest in practice for most inputs.
- **When space matters** — O(log n) vs Merge Sort's O(n).
- **Arrays** — cache-friendly sequential access (not good for linked lists).
- **C++ STL `std::sort`** — uses Introsort (Quick Sort + Heap Sort + Insertion Sort).

### Pivot Strategies

| Strategy | Pros | Cons |
|----------|------|------|
| **Last element** | Simple | O(n²) on sorted arrays |
| **First element** | Simple | O(n²) on sorted arrays |
| **Random** | Avoids worst case | Slightly more code |
| **Median-of-three** | Best balance | Most complex |

---

## 5. ⚠️ Common Mistakes

### ❌ Not handling base case properly

```cpp
// WRONG: infinite recursion
if (low > high) return;

// CORRECT
if (low >= high) return;
```

### ❌ Including pivot in recursive calls

```cpp
// WRONG: pivot at index p is already in correct position
quickSort(arr, low, p);       // includes pivot again!
quickSort(arr, p, high);

// CORRECT: exclude pivot
quickSort(arr, low, p - 1);
quickSort(arr, p + 1, high);
```

### ❌ Using last element as pivot on sorted arrays

```
Sorted: [1, 2, 3, 4, 5]  pivot = 5
Partition: everything goes left, pivot at end
→ [1, 2, 3, 4] + [5] + []
→ O(n) partition × n levels = O(n²)!
```

**Fix**: Use random pivot or median-of-three.

---

## 6. 🎤 Interview Follow-up Questions

### Q1: "When does Quick Sort degrade to O(n²)?"

**Answer**: When the pivot is always the smallest or largest element. This happens with:
- Sorted/reverse-sorted arrays using first/last element as pivot.
- All equal elements (without 3-way partition).

### Q2: "How to avoid worst case?"

**Answer**: 
- **Randomized pivot**: `swap(arr[random(low, high)], arr[high])` before partition.
- **Median-of-three**: Pick median of `arr[low]`, `arr[mid]`, `arr[high]`.
- **Introsort**: Switch to Heap Sort if recursion depth exceeds 2×log(n).

### Q3: "Quick Sort vs Merge Sort — which to use?"

**Answer**:
- Quick Sort: Faster in practice, better cache locality, in-place. Use for arrays.
- Merge Sort: Guaranteed O(n log n), stable. Use for linked lists, external sorting, when stability needed.

### Q4: "What is 3-way partition (Dutch National Flag)?"

**Answer**: Partition into three groups: `< pivot`, `== pivot`, `> pivot`. Handles many duplicates efficiently. Avoids O(n²) when all elements are equal.

### Q5: "What is the space complexity?"

**Answer**: O(log n) average (recursion stack depth). O(n) worst case if every partition is unbalanced. Can be improved with **tail call optimization** — always recurse on the smaller partition first.

---

## 7. 📊 Complexity Analysis

| Case | Time | When? |
|------|------|-------|
| **Best** | O(n log n) | Pivot always divides array in half |
| **Average** | O(n log n) | Random pivot, random data |
| **Worst** | O(n²) | Pivot is always min/max (sorted input + bad pivot) |

**Space**: O(log n) average (recursion stack), O(n) worst case.

### Why O(n log n) average?

Even if the pivot doesn't split exactly in half, as long as it splits into constant fractions (e.g., 90/10), the depth is still O(log n). Only consistently extreme splits (like 1/n-1) cause O(n²).

---

## 8. 🔍 Dry Run

```
Input: [10, 7, 8, 9, 1, 5]

quickSort(0, 5):
  partition(0, 5): pivot = 5
    j=0: 10 > 5 → skip
    j=1: 7 > 5 → skip
    j=2: 8 > 5 → skip
    j=3: 9 > 5 → skip
    j=4: 1 ≤ 5 → i=0, swap(arr[0], arr[4]) → [1, 7, 8, 9, 10, 5]
    swap(arr[1], arr[5]) → [1, 5, 8, 9, 10, 7]
    pivot position = 1

  quickSort(0, 0): base case → [1] ✅

  quickSort(2, 5): pivot = 7
    j=2: 8 > 7 → skip
    j=3: 9 > 7 → skip
    j=4: 10 > 7 → skip
    swap(arr[2], arr[5]) → [1, 5, 7, 9, 10, 8]
    pivot position = 2

    quickSort(2, 1): base case
    quickSort(3, 5): pivot = 8
      j=3: 9 > 8 → skip
      j=4: 10 > 8 → skip
      swap(arr[3], arr[5]) → [1, 5, 7, 8, 10, 9]
      pivot position = 3

      quickSort(3, 2): base case
      quickSort(4, 5): pivot = 9
        j=4: 10 > 9 → skip
        swap(arr[4], arr[5]) → [1, 5, 7, 8, 9, 10]
        pivot position = 4

Output: [1, 5, 7, 8, 9, 10] ✅
```

---
