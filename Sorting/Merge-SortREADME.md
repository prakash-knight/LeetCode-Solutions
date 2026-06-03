# Merge Sort

---

## 1. 📝 What is Merge Sort?

Merge Sort is a **Divide and Conquer** algorithm:
1. **Divide** the array into two halves.
2. **Recursively sort** each half.
3. **Merge** the two sorted halves into one sorted array.

It keeps dividing until each piece has **one element** (which is already sorted), then merges everything back together.

### Example

```
Input: [5, 2, 4, 1, 3]

DIVIDE:
[5, 2, 4, 1, 3]
  ↓
[5, 2, 4]   [1, 3]
  ↓            ↓
[5, 2] [4]  [1] [3]
  ↓
[5] [2]

MERGE (bottom-up):
[5] [2] → [2, 5]
[2, 5] [4] → [2, 4, 5]
[1] [3] → [1, 3]
[2, 4, 5] [1, 3] → [1, 2, 3, 4, 5] ✅
```

---

## 2. 💡 Intuition

### Core Idea: Divide and Conquer

**"Sorting a big array is hard. Sorting two small arrays is easy. Merging two sorted arrays is easy."**

### The Merge Step is the Key

The entire power of Merge Sort lies in the **merge function**:
- You have two sorted subarrays.
- Compare their front elements, pick the smaller one, repeat.
- This takes O(n) time.

### Why does it guarantee O(n log n)?

```
Level 0: 1 array of size n           → n work to merge
Level 1: 2 arrays of size n/2        → n work to merge
Level 2: 4 arrays of size n/4        → n work to merge
...
Level log(n): n arrays of size 1     → n work to merge

Total: n × log(n) = O(n log n)
```

Each level does O(n) merge work, and there are log(n) levels.

---

## 3. 💻 Code (C++)

```cpp
#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;          // temporary array for merged result

    int left = low;            // pointer for left half
    int right = mid + 1;       // pointer for right half

    // Compare and pick smaller element from both halves
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // Copy remaining elements from left half
    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    // Copy remaining elements from right half
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // Copy merged result back to original array
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;          // base case: single element

    int mid = (low + high) / 2;      // find middle

    mergeSort(arr, low, mid);         // sort left half
    mergeSort(arr, mid + 1, high);    // sort right half
    merge(arr, low, mid, high);       // merge both sorted halves
}

int main() {
    vector<int> arr = {5, 2, 4, 1, 3};
    mergeSort(arr, 0, arr.size() - 1);

    for (int x : arr) cout << x << " ";
    return 0;
}
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `low` | Starting index of current subarray |
| `high` | Ending index of current subarray |
| `mid` | Middle index — splits array into left and right |
| `left` | Pointer scanning left sorted half during merge |
| `right` | Pointer scanning right sorted half during merge |
| `temp` | Temporary array holding the merged result |

### Why `arr[left] <= arr[right]` (not `<`)?

Using `<=` ensures **stability** — when two elements are equal, the one from the left half goes first, preserving their original relative order.

---

## 4. 🧩 Pattern Recognition

### Algorithm Type: **Divide and Conquer**

### Key Properties

| Property | Value |
|----------|-------|
| **Stable** | ✅ Yes — equal elements maintain relative order (using `<=`) |
| **In-place** | ❌ No — requires O(n) extra space for `temp` array |
| **Adaptive** | ❌ No — always O(n log n) regardless of input |
| **Guaranteed** | ✅ Yes — O(n log n) in ALL cases (no worst-case degradation) |

### When to use Merge Sort?

- **When stability matters** — e.g., sorting records by multiple keys.
- **When guaranteed O(n log n) is needed** — no worst case O(n²) like Quick Sort.
- **Sorting Linked Lists** — no random access needed, merge is natural.
- **External Sorting** — sorting data that doesn't fit in memory (read chunks, sort, merge).
- **Counting inversions** — classic application of merge sort.

---

## 5. ⚠️ Common Mistakes

### ❌ Wrong base case

```cpp
// WRONG: infinite recursion when low == high
if (low > high) return;

// CORRECT: stop when one or zero elements
if (low >= high) return;
```

### ❌ Wrong mid calculation (integer overflow)

```cpp
// WRONG for very large arrays (low + high can overflow)
int mid = (low + high) / 2;

// SAFER version
int mid = low + (high - low) / 2;
```

### ❌ Forgetting `i - low` offset when copying back

```cpp
// WRONG: temp starts at index 0, but arr starts at 'low'
arr[i] = temp[i];

// CORRECT: offset by 'low'
arr[i] = temp[i - low];
```

### ❌ Using `<` instead of `<=` in merge (breaks stability)

```cpp
// WRONG: unstable — equal elements from right half go first
if (arr[left] < arr[right])

// CORRECT: stable — left half elements go first on tie
if (arr[left] <= arr[right])
```

---

## 6. 🎤 Interview Follow-up Questions

### Q1: "Why is Merge Sort preferred for Linked Lists?"

**Answer**: 
- Linked Lists don't support O(1) random access (no `arr[mid]`), so Quick Sort's partition is inefficient.
- Merge Sort only needs sequential access.
- Merge step for linked lists is O(1) space (just pointer manipulation).

### Q2: "How is Merge Sort used in External Sorting?"

**Answer**: When data is too large for RAM:
1. Read chunks that fit in memory.
2. Sort each chunk using any in-memory sort.
3. Merge sorted chunks using a **k-way merge** (min-heap).

### Q3: "Can you do Merge Sort in-place?"

**Answer**: Yes, but it's complex and impractical. In-place merge sort exists but has worse constant factors. The O(n) space version is standard.

### Q4: "Count inversions using Merge Sort?"

**Answer**: During merge, when `arr[right] < arr[left]`, it means `arr[right]` is smaller than ALL remaining elements in the left half. Count += `(mid - left + 1)`. This counts inversions in O(n log n).

### Q5: "Merge Sort vs Quick Sort?"

**Answer**:

| Aspect | Merge Sort | Quick Sort |
|--------|-----------|------------|
| Worst case | O(n log n) ✅ | O(n²) ❌ |
| Average case | O(n log n) | O(n log n) |
| Space | O(n) ❌ | O(log n) ✅ |
| Stable | ✅ Yes | ❌ No |
| Cache | ❌ Poor | ✅ Good |
| In practice | Slower | Faster (better constants) |

---

## 7. 📊 Complexity Analysis

| Case | Time | Why? |
|------|------|------|
| **Best** | O(n log n) | Always divides and merges |
| **Average** | O(n log n) | Same — no input dependency |
| **Worst** | O(n log n) | Same — guaranteed |

**Space**: O(n) — for the temporary array during merge.

### Recursion Tree Visualization

```
                [5, 2, 4, 1, 3]              → n work
               /                \
        [5, 2, 4]            [1, 3]           → n work
        /      \             /    \
     [5, 2]   [4]         [1]   [3]           → n work
     /    \
   [5]   [2]                                  → n work
   
   log₂(5) ≈ 3 levels × n work each = O(n log n)
```

---

## 8. 🔍 Dry Run

```
Input: [38, 27, 43, 3]

mergeSort(0, 3):
  mid = 1
  mergeSort(0, 1):       ← sort left half
    mid = 0
    mergeSort(0, 0): return   ← [38] base case
    mergeSort(1, 1): return   ← [27] base case
    merge(0, 0, 1):           ← merge [38] and [27]
      left=38, right=27 → 27 first → [27, 38]

  mergeSort(2, 3):       ← sort right half
    mid = 2
    mergeSort(2, 2): return   ← [43] base case
    mergeSort(3, 3): return   ← [3] base case
    merge(2, 2, 3):           ← merge [43] and [3]
      left=43, right=3 → 3 first → [3, 43]

  merge(0, 1, 3):         ← merge [27, 38] and [3, 43]
    3 < 27  → [3]
    27 < 43 → [3, 27]
    38 < 43 → [3, 27, 38]
    43 left → [3, 27, 38, 43]

Output: [3, 27, 38, 43] ✅
```

---
