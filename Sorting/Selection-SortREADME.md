# Selection Sort

---

## 1. 📝 What is Selection Sort?

Selection Sort divides the array into **sorted** (left) and **unsorted** (right) parts. In every pass, it **finds the minimum** element from the unsorted part and **swaps it** with the first unsorted element.

Think of it like picking the **smallest card** from a deck and placing it in order.

### Example

```
Input: [13, 46, 24, 52, 20, 9]

Pass 1: min = 9 (index 5), swap with index 0
        [9, 46, 24, 52, 20, 13]    ← 9 is fixed ✅

Pass 2: min = 13 (index 5), swap with index 1
        [9, 13, 24, 52, 20, 46]    ← 13 is fixed ✅

Pass 3: min = 20 (index 4), swap with index 2
        [9, 13, 20, 52, 24, 46]    ← 20 is fixed ✅

Pass 4: min = 24 (index 4), swap with index 3
        [9, 13, 20, 24, 52, 46]    ← 24 is fixed ✅

Pass 5: min = 46 (index 5), swap with index 4
        [9, 13, 20, 24, 46, 52]    ← Done ✅
```

---

## 2. 💡 Intuition

### Core Idea

Each pass **selects** the smallest element from the remaining unsorted portion and places it at the beginning of the unsorted section.

- **Pass 1** → smallest element placed at index 0.
- **Pass 2** → 2nd smallest placed at index 1.
- **Pass i** → i-th smallest placed at index i.

### Key Difference from Bubble Sort

- **Bubble Sort**: Swaps adjacent elements many times per pass.
- **Selection Sort**: Does at most **one swap per pass** (finds min first, then swaps once).

### Why is it O(n²) even in the best case?

Unlike Bubble Sort, Selection Sort **always** scans the entire unsorted portion to find the minimum. Even if the array is sorted, it still does n(n-1)/2 comparisons.

---

## 3. 💻 Code (C++)

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {13, 46, 24, 52, 20, 9};
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        int mini = i;              // assume current index has minimum

        // Find actual minimum in unsorted part
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[mini]) {
                mini = j;          // update minimum index
            }
        }

        // Place minimum at its correct position
        swap(arr[i], arr[mini]);
    }

    for (int x : arr) cout << x << " ";
    return 0;
}
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `i` | Current position being filled (start of unsorted part) |
| `mini` | Index of the minimum element found in unsorted portion |
| `j` | Scanning pointer to find minimum in unsorted portion |

---

## 4. 🧩 Pattern Recognition

### Algorithm Type: **Comparison-based, In-place Sorting**

### Key Properties

| Property | Value |
|----------|-------|
| **Stable** | ❌ No — swaps can change relative order of equal elements |
| **In-place** | ✅ Yes — O(1) extra space |
| **Adaptive** | ❌ No — always O(n²) regardless of input |
| **Minimum Swaps** | ✅ Yes — at most n-1 swaps (best for memory writes) |

### When is Selection Sort useful?

- **When memory writes are expensive** — it does the minimum number of swaps (at most n-1). Good for EEPROM/flash memory.
- **Small arrays** — simple to implement, low overhead.
- **When you need to find k smallest elements** — first k passes give you the k smallest.

---

## 5. ⚠️ Common Mistakes

### ❌ Storing the minimum VALUE instead of INDEX

```cpp
// WRONG: you need the index to swap, not just the value
int minVal = arr[i];

// CORRECT: track index
int mini = i;
if (arr[j] < arr[mini]) mini = j;
swap(arr[i], arr[mini]);
```

### ❌ Starting inner loop from 0 instead of i+1

```cpp
// WRONG: re-checks sorted elements
for (int j = 0; j < n; j++)

// CORRECT: only scan unsorted portion
for (int j = i + 1; j < n; j++)
```

### ❌ Thinking Selection Sort is stable

It's NOT stable. Example:
```
[5a, 3, 5b, 2]
Pass 1: min=2 → swap with 5a → [2, 3, 5b, 5a]
5a and 5b swapped their relative order!
```

---

## 6. 🎤 Interview Follow-up Questions

### Q1: "Is Selection Sort stable?"
**Answer**: No. When we swap the minimum with the front element, it can jump over equal elements. Example: `[5, 5, 3]` → after pass 1: `[3, 5, 5]` but the first 5 moved past the second 5.

### Q2: "When would you prefer Selection Sort over Bubble Sort?"
**Answer**: When the cost of swapping is high (e.g., large records, flash memory). Selection Sort does at most `n-1` swaps, while Bubble Sort can do O(n²) swaps.

### Q3: "Can you make Selection Sort stable?"
**Answer**: Yes — instead of swapping, **shift** elements to the right and insert the minimum. But this increases time constant.

### Q4: "What's the number of comparisons?"
**Answer**: Always `n(n-1)/2`, regardless of input. No best/worst case difference for comparisons.

### Q5: "Why not use Selection Sort for large data?"
**Answer**: O(n²) always — no optimization possible. Merge Sort and Quick Sort are O(n log n) average.

---

## 7. 📊 Complexity Analysis

| Case | Time | Swaps |
|------|------|-------|
| **Best** | O(n²) | O(n) — n-1 swaps |
| **Average** | O(n²) | O(n) |
| **Worst** | O(n²) | O(n) |

**Space**: O(1)

### Why always O(n²)?

```
Pass 1: n-1 comparisons to find min
Pass 2: n-2 comparisons
...
Total = (n-1) + (n-2) + ... + 1 = n(n-1)/2 = O(n²)
```

No early exit possible — must always scan to find minimum.

---

## 8. 🔍 Dry Run

```
Input: [64, 25, 12, 22, 11]

Pass 1 (i=0):
  Scan [25, 12, 22, 11] → min = 11 (index 4)
  swap(arr[0], arr[4]) → [11, 25, 12, 22, 64]  ← 11 fixed ✅

Pass 2 (i=1):
  Scan [12, 22, 64] → min = 12 (index 2)
  swap(arr[1], arr[2]) → [11, 12, 25, 22, 64]  ← 12 fixed ✅

Pass 3 (i=2):
  Scan [22, 64] → min = 22 (index 3)
  swap(arr[2], arr[3]) → [11, 12, 22, 25, 64]  ← 22 fixed ✅

Pass 4 (i=3):
  Scan [64] → min = 64 (index 4, same as 25? no)
  Already in place → [11, 12, 22, 25, 64]  ← 25 fixed ✅

Output: [11, 12, 22, 25, 64]
```

---
