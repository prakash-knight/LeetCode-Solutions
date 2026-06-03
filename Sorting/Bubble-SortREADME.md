# Bubble Sort

---

## 1. 📝 What is Bubble Sort?

Bubble Sort repeatedly **compares adjacent elements** and **swaps them if they're in the wrong order**. After each complete pass, the largest unsorted element "bubbles up" to its correct position at the end.

Think of it like bubbles rising in water — the **biggest bubble reaches the top first**.

### Example

```
Input:  [13, 46, 24, 52, 20, 9]

Pass 1: Compare adjacent, swap if needed
  13, 46 → ok
  46, 24 → swap → [13, 24, 46, 52, 20, 9]
  46, 52 → ok
  52, 20 → swap → [13, 24, 46, 20, 52, 9]
  52, 9  → swap → [13, 24, 46, 20, 9, 52]  ← 52 is fixed ✅

Pass 2: [13, 24, 20, 9, 46, 52]  ← 46 is fixed ✅
Pass 3: [13, 20, 9, 24, 46, 52]  ← 24 is fixed ✅
Pass 4: [13, 9, 20, 24, 46, 52]  ← 20 is fixed ✅
Pass 5: [9, 13, 20, 24, 46, 52]  ← Done ✅
```

---

## 2. 💡 Intuition

### Core Idea

After **each pass**, the largest unsorted element reaches its final position.

- **Pass 1** → largest element fixed at the end.
- **Pass 2** → 2nd largest fixed.
- **Pass n-1** → everything sorted.

### Why "n-i-1" in the inner loop?

After `i` passes, the last `i` elements are already sorted. No need to compare them again — hence `j < n - i - 1`.

### Optimization: Early Termination

If during a pass, **no swaps happen**, the array is already sorted. We can stop early.

---

## 3. 🐢 Basic vs Optimized

### Basic Version

```cpp
for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
            swap(arr[j], arr[j + 1]);
        }
    }
}
```

- **Always runs n-1 passes**, even if sorted early.
- Best/Worst/Avg: **O(n²)**.

### Optimized Version (with early exit)

```cpp
for (int i = 0; i < n - 1; i++) {
    bool swapped = false;
    for (int j = 0; j < n - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
            swap(arr[j], arr[j + 1]);
            swapped = true;
        }
    }
    if (!swapped) break;   // already sorted — stop early
}
```

- **Best Case (already sorted): O(n)** — one pass, no swaps, breaks.

---

## 4. 💻 Code (C++)

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {13, 46, 24, 52, 20, 9};
    int n = arr.size();

    // Number of passes
    for (int i = 0; i < n - 1; i++) {

        bool swapped = false;       // optimization flag

        // Compare adjacent elements
        for (int j = 0; j < n - i - 1; j++) {
            // n-i-1 because last i elements are already sorted
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);   // swap if wrong order
                swapped = true;
            }
        }

        // If no swaps in this pass → array is sorted
        if (!swapped) break;
    }

    for (int x : arr) cout << x << " ";
    return 0;
}
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `i` | Pass number (0 to n-2). After pass `i`, last `i+1` elements are sorted |
| `j` | Index for comparing adjacent pairs within unsorted portion |
| `swapped` | Optimization flag — if no swap in a pass, array is sorted |

---

## 5. 🧩 Pattern Recognition

### Algorithm Type: **Comparison-based, In-place Sorting**

### Key Properties

| Property | Value |
|----------|-------|
| **Stable** | ✅ Yes — equal elements maintain relative order |
| **In-place** | ✅ Yes — O(1) extra space |
| **Adaptive** | ✅ Yes (optimized version) — O(n) for nearly sorted |
| **Online** | ❌ No — needs all elements upfront |

### When is Bubble Sort actually useful?

- **Teaching** — simplest sorting algorithm to understand.
- **Nearly sorted data** — optimized version runs in O(n).
- **Small arrays** — overhead is negligible for tiny inputs.
- **Detecting if array is sorted** — one pass with `swapped` flag.

---

## 6. ⚠️ Common Mistakes

### ❌ Inner loop going to `n-1` instead of `n-i-1`

```cpp
// WRONG: re-checks already sorted elements
for (int j = 0; j < n - 1; j++)

// CORRECT: skip last i sorted elements
for (int j = 0; j < n - i - 1; j++)
```

### ❌ Forgetting the early exit optimization

Without `swapped` flag, best case is still O(n²). Interviewers expect you to mention this optimization.

### ❌ Confusing with Selection Sort

- **Bubble Sort**: Swaps adjacent elements repeatedly → largest bubbles to end.
- **Selection Sort**: Finds minimum and places it at front → no adjacent swapping.

---

## 7. 🎤 Interview Follow-up Questions

### Q1: "Is Bubble Sort stable?"
**Answer**: Yes. We only swap when `arr[j] > arr[j+1]` (strict >). Equal elements are never swapped, so their relative order is preserved.

### Q2: "What's the best case and when does it occur?"
**Answer**: O(n) — when the array is already sorted (optimized version). One pass, zero swaps, early exit.

### Q3: "Why is Bubble Sort never used in practice?"
**Answer**: O(n²) average/worst case. For large inputs, algorithms like Merge Sort O(n log n) or Quick Sort are far superior. Even Insertion Sort performs better in practice due to fewer swaps.

### Q4: "Can you sort in descending order?"
**Answer**: Change `arr[j] > arr[j+1]` to `arr[j] < arr[j+1]`.

### Q5: "How many swaps does Bubble Sort make in worst case?"
**Answer**: O(n²) swaps. Worst case is reverse sorted array — every comparison results in a swap.

---

## 8. 📊 Complexity Analysis

| Case | Time | When? |
|------|------|-------|
| **Best** | O(n) | Already sorted (with optimization) |
| **Average** | O(n²) | Random order |
| **Worst** | O(n²) | Reverse sorted |

**Space**: O(1) — only a few variables, no extra array.

### Why O(n²)?

```
Pass 1: n-1 comparisons
Pass 2: n-2 comparisons
Pass 3: n-3 comparisons
...
Total = (n-1) + (n-2) + ... + 1 = n(n-1)/2 = O(n²)
```

---

## 9. 🔍 Dry Run

```
Input: [5, 3, 8, 4, 2]

Pass 1 (i=0):
  j=0: 5 > 3 → swap → [3, 5, 8, 4, 2]
  j=1: 5 < 8 → ok
  j=2: 8 > 4 → swap → [3, 5, 4, 8, 2]
  j=3: 8 > 2 → swap → [3, 5, 4, 2, 8]  ← 8 fixed ✅

Pass 2 (i=1):
  j=0: 3 < 5 → ok
  j=1: 5 > 4 → swap → [3, 4, 5, 2, 8]
  j=2: 5 > 2 → swap → [3, 4, 2, 5, 8]  ← 5 fixed ✅

Pass 3 (i=2):
  j=0: 3 < 4 → ok
  j=1: 4 > 2 → swap → [3, 2, 4, 5, 8]  ← 4 fixed ✅

Pass 4 (i=3):
  j=0: 3 > 2 → swap → [2, 3, 4, 5, 8]  ← Done ✅

Output: [2, 3, 4, 5, 8]
```

---
