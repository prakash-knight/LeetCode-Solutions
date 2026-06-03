# Insertion Sort

---

## 1. 📝 What is Insertion Sort?

Insertion Sort works like **sorting playing cards in your hand**. You pick one card at a time and **insert it into its correct position** among the already sorted cards.

The left portion is always sorted. Each new element is compared backward and inserted where it belongs.

### Example

```
Input: [13, 46, 24, 52, 20, 9]

[13] | 46, 24, 52, 20, 9      ← 13 alone is sorted

Take 46: 46 > 13 → insert after 13
[13, 46] | 24, 52, 20, 9

Take 24: 24 < 46 → shift 46 right, 24 > 13 → insert after 13
[13, 24, 46] | 52, 20, 9

Take 52: 52 > 46 → insert at end
[13, 24, 46, 52] | 20, 9

Take 20: shift 52, 46, 24 right → insert after 13
[13, 20, 24, 46, 52] | 9

Take 9: shift all right → insert at front
[9, 13, 20, 24, 46, 52] ✅
```

---

## 2. 💡 Intuition

### Core Idea

At every step, the **left part is sorted** and the current element is **inserted into its correct position** by shifting larger elements to the right.

### Why is Insertion Sort special?

1. **Adaptive**: If the array is nearly sorted, very few shifts happen → approaches O(n).
2. **Stable**: Equal elements never cross each other.
3. **Online**: Can sort elements as they arrive (doesn't need all data upfront).

### Key Insight

The `while` loop shifts elements right until we find the correct position. The `key` (current element) is then placed in the gap.

```
Before:  [3, 7, 12, 5, ...]
                    ^key=5
Shift:   [3, 7, _, 12, ...]   ← 12 shifted right
Shift:   [3, _, 7, 12, ...]   ← 7 shifted right
Insert:  [3, 5, 7, 12, ...]   ← 5 > 3, stop, insert here
```

---

## 3. 💻 Code (C++)

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {13, 46, 24, 52, 20, 9};
    int n = arr.size();

    for (int i = 1; i < n; i++) {

        int key = arr[i];        // element to insert
        int j = i - 1;           // start comparing from previous element

        // Shift larger elements to the right
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // shift right
            j--;                  // move backward
        }

        // Insert key at its correct position
        arr[j + 1] = key;
    }

    for (int x : arr) cout << x << " ";
    return 0;
}
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `i` | Index of the element currently being inserted (starts from 1) |
| `key` | The element to be placed at its correct position |
| `j` | Pointer moving backward through the sorted portion to find insertion point |

### Why `j + 1`?

When the `while` loop ends, `j` has gone one step too far (either `j < 0` or `arr[j] <= key`). So the correct insertion spot is `j + 1`.

---

## 4. 🧩 Pattern Recognition

### Algorithm Type: **Comparison-based, In-place, Adaptive Sorting**

### Key Properties

| Property | Value |
|----------|-------|
| **Stable** | ✅ Yes — uses `>` not `>=`, so equal elements don't move |
| **In-place** | ✅ Yes — O(1) extra space |
| **Adaptive** | ✅ Yes — O(n) for nearly sorted arrays |
| **Online** | ✅ Yes — can sort as elements arrive |

### When to use Insertion Sort?

- **Small arrays (n < ~50)** — low overhead, often faster than O(n log n) algorithms.
- **Nearly sorted data** — very few shifts needed → near O(n).
- **Hybrid algorithms** — TimSort (Python) and IntroSort (C++ STL) switch to Insertion Sort for small subarrays.
- **Online sorting** — data arriving one element at a time.

---

## 5. ⚠️ Common Mistakes

### ❌ Starting loop from i=0 instead of i=1

```cpp
// WRONG: element at index 0 has nothing to compare with
for (int i = 0; i < n; i++)

// CORRECT: first element is already "sorted" alone
for (int i = 1; i < n; i++)
```

### ❌ Using `arr[j] >= key` instead of `arr[j] > key`

```cpp
// WRONG: makes it unstable — equal elements get shifted
while (j >= 0 && arr[j] >= key)

// CORRECT: preserves relative order of equal elements
while (j >= 0 && arr[j] > key)
```

### ❌ Forgetting to save `key` before shifting

```cpp
// WRONG: arr[i] gets overwritten by arr[j+1] = arr[j]
int j = i - 1;
while (j >= 0 && arr[j] > arr[i])  // arr[i] changes during shifts!

// CORRECT: save the value first
int key = arr[i];
```

---

## 6. 🎤 Interview Follow-up Questions

### Q1: "Why does C++ STL use Insertion Sort internally?"

**Answer**: C++ `std::sort` uses IntroSort — a hybrid of Quick Sort, Heap Sort, and **Insertion Sort**. When the subarray is small (< ~16 elements), it switches to Insertion Sort because the constant factor is lower for small inputs.

### Q2: "What's the best case and when does it occur?"

**Answer**: O(n) — when the array is already sorted. The `while` loop never executes (every `key` is already >= previous element), so each iteration is O(1) × n = O(n).

### Q3: "How does Insertion Sort compare to Bubble Sort?"

**Answer**: 
- Both are O(n²) average/worst, O(n) best.
- Insertion Sort does **fewer writes** — it shifts instead of swapping.
- Insertion Sort is generally **2x faster** in practice.
- Both are stable.

### Q4: "Can you use Binary Search to find the insertion point?"

**Answer**: Yes — **Binary Insertion Sort**. You can find the insertion position in O(log n) using binary search. But shifting still takes O(n), so overall worst case remains O(n²). Reduces comparisons but not total time.

### Q5: "Insertion Sort on a Linked List?"

**Answer**: Actually performs well! No shifting needed — just pointer manipulation for insertion → O(1) per insert. Total: O(n²) comparisons but with O(1) space.

---

## 7. 📊 Complexity Analysis

| Case | Time | When? |
|------|------|-------|
| **Best** | O(n) | Already sorted — no shifts |
| **Average** | O(n²) | Random order |
| **Worst** | O(n²) | Reverse sorted — every element shifts all the way |

**Space**: O(1) — only `key` and `j` as extra variables.

### Why O(n) best case?

```
Already sorted: [1, 2, 3, 4, 5]

i=1: key=2, arr[0]=1 ≤ 2 → while skipped → 0 shifts
i=2: key=3, arr[1]=2 ≤ 3 → while skipped → 0 shifts
...
Total: n-1 comparisons, 0 shifts → O(n)
```

### Why O(n²) worst case?

```
Reverse sorted: [5, 4, 3, 2, 1]

i=1: key=4, shift 5 → 1 shift
i=2: key=3, shift 5, 4 → 2 shifts
i=3: key=2, shift 5, 4, 3 → 3 shifts
i=4: key=1, shift 5, 4, 3, 2 → 4 shifts

Total = 1+2+3+4 = n(n-1)/2 = O(n²)
```

---

## 8. 🔍 Dry Run

```
Input: [5, 3, 4, 1, 2]

i=1: key=3
  j=0: arr[0]=5 > 3 → shift → [5, 5, 4, 1, 2]  j=-1
  Insert key at j+1=0 → [3, 5, 4, 1, 2]

i=2: key=4
  j=1: arr[1]=5 > 4 → shift → [3, 5, 5, 1, 2]  j=0
  j=0: arr[0]=3 ≤ 4 → stop
  Insert key at j+1=1 → [3, 4, 5, 1, 2]

i=3: key=1
  j=2: 5 > 1 → shift → [3, 4, 5, 5, 2]  j=1
  j=1: 4 > 1 → shift → [3, 4, 4, 5, 2]  j=0
  j=0: 3 > 1 → shift → [3, 3, 4, 5, 2]  j=-1
  Insert key at j+1=0 → [1, 3, 4, 5, 2]

i=4: key=2
  j=3: 5 > 2 → shift  j=2
  j=2: 4 > 2 → shift  j=1
  j=1: 3 > 2 → shift  j=0
  j=0: 1 ≤ 2 → stop
  Insert key at j+1=1 → [1, 2, 3, 4, 5] ✅

Output: [1, 2, 3, 4, 5]
```

---
