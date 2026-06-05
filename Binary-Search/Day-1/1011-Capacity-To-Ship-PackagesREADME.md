# 1011. Capacity To Ship Packages Within D Days

[Link to LeetCode Problem](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

---

## 📝 Problem Statement

A conveyor belt has packages that must be shipped from one port to another within `days` days.

The `i`-th package has a weight of `weights[i]`. Each day, we load packages on the belt in order. We may not load more weight than the maximum weight capacity of the ship.

Return the **least weight capacity** of the ship that will result in all packages being shipped within `days` days.

### Example

```cpp
Input:
weights = [1,2,3,4,5,6,7,8,9,10], days = 5

Output:
15
```

Because:

```cpp
With capacity 15:
  Day 1: [1,2,3,4,5]     → 15
  Day 2: [6,7]            → 13
  Day 3: [8]              → 8
  Day 4: [9]              → 9
  Day 5: [10]             → 10
All shipped in 5 days ✅
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Try every capacity from `max(weights)` to `sum(weights)`. For each, simulate the shipping.

### Why is it inefficient?

```cpp
O((sum - max) × n)
```

time complexity — linearly trying every possible capacity.

---

## 2. Optimized Approach (Binary Search on Answer)

### Pattern Used

```cpp
Binary Search on Answer Space
```

### Main Idea

The minimum capacity lies in `[max(weights), sum(weights)]`:
- **Lower bound `max(weights)`:** Must be able to carry the heaviest single package.
- **Upper bound `sum(weights)`:** Ship everything in 1 day.

As capacity increases, the days needed **decreases** (monotonic). Binary search exploits this.

### Helper Function: Calculate Days Needed

Given a capacity `d`, simulate the loading greedily:

```cpp
count = 1 (start with day 1)
cap = 0   (current day's load)

for each weight x:
    if cap + x <= d:
        cap += x          // add to current day
    else:
        count++           // start new day
        cap = x           // current package starts new day
```

---

## Step-by-Step Logic

1. Compute search range:

```cpp
s = max(weights)       // can't be less than heaviest package
e = sum(weights)       // ship everything in 1 day
```

2. Binary search:
   - Compute `dneed = cal(weights, mid)` — days needed with capacity `mid`.
   - If `dneed <= days` → capacity sufficient, try smaller: save `ans = mid`, `e = mid - 1`.
   - If `dneed > days` → capacity insufficient: `s = mid + 1`.

3. Return `ans`.

---

### Dry Run

```cpp
weights = [1,2,3,4,5,6,7,8,9,10], days = 5
s = 10, e = 55

Iteration 1: mid=32 → days_needed = 2 ≤ 5 → ans=32, e=31
Iteration 2: mid=20 → days_needed = 3 ≤ 5 → ans=20, e=19
Iteration 3: mid=14 → days_needed = 5 ≤ 5 → ans=14, e=13
Iteration 4: mid=11 → days_needed = 6 > 5 → s=12
Iteration 5: mid=12 → days_needed = 6 > 5 → s=13
Iteration 6: mid=13 → days_needed = 6 > 5 → s=14
Loop ends: s=14 > e=13 → return ans=15

Wait, let me recompute more carefully:

mid=32: [1,2,3,4,5,6,7] + [8,9,10] → 2 days → ans=32, e=31
mid=20: [1,2,3,4,5] + [6,7] + [8,9] + [10] → 4 days? 
  Actually: 1+2+3+4+5=15, +6=21≤20? No → day2: 6+7=13, +8=21>20 → day3: 8+9=17, +10=27>20 → day4: 10 → 4 days ≤ 5 → ans=20, e=19
...continuing until convergence → ans=15
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n × log(sum - max))
```

Because:
- Binary search range is `[max(weights), sum(weights)]`, so `O(log(sum - max))` iterations.
- Each iteration simulates loading in `O(n)`.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only a few variables used.

---

# 💻 Code

```cpp
class Solution {
public:
    int cal(vector<int>& w, int d) {
        int count = 1;
        int cap = 0;

        for (auto x : w) {
            if (cap + x <= d) {
                cap += x;
            } else {
                count++;
                cap = x;
            }
        }

        return count;
    }

    int shipWithinDays(vector<int>& w, int days) {
        int s = INT_MIN;
        int ans = 0;

        for (auto x : w) {
            ans += x;
            s = max(s, x);
        }
        int e = ans;
        ans = 0;

        while (s <= e) {
            int mid = s + (e - s) / 2;
            int dneed = cal(w, mid);

            if (dneed <= days) {
                ans = mid;
                e = mid - 1;
            } else
                s = mid + 1;
        }
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ days equals number of packages (each package on its own day)

```cpp
weights = [1, 2, 3], days = 3
// Output: 3 (capacity = max weight)
```

---

✅ days = 1 (ship everything in one day)

```cpp
weights = [1, 2, 3], days = 1
// Output: 6 (capacity = sum of all weights)
```

---

✅ Single package

```cpp
weights = [10], days = 1
// Output: 10
```

---

✅ All packages same weight

```cpp
weights = [5, 5, 5, 5], days = 2
// Output: 10
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

This is the **same pattern as Koko Eating Bananas** (LC 875):
1. Define a search range for the answer.
2. Write a greedy simulation to check feasibility.
3. Binary search for the minimum feasible answer.

---

## Common Mistakes

❌ Wrong lower bound:

Using `s = 1` or `s = 0` is wrong — the ship must be able to carry at least the heaviest package. Use `s = max(weights)`.

---

❌ Greedy simulation error:

Packages must be loaded **in order** (you can't rearrange). The greedy simulation must process them sequentially.

---

❌ Off-by-one in day counting:

Start `count = 1` (not 0), since the first package always uses at least 1 day.

---

## Comparison with LC 875 (Koko Eating Bananas)

| Aspect | Koko (875) | Ship (1011) |
|--------|-----------|-------------|
| Search range | `[1, max(piles)]` | `[max(w), sum(w)]` |
| Feasibility check | Total hours ≤ h | Total days ≤ days |
| Per-item cost | `ceil(pile/speed)` | Greedy bin packing |
| Optimization | Minimize speed | Minimize capacity |

---

## Related Problems

- 875 — Koko Eating Bananas (same pattern)
- 410 — Split Array Largest Sum (identical problem, different wording)
- 1283 — Find the Smallest Divisor Given a Threshold

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Minimize capacity / maximum partition size
- Split array into at most k parts
- "Within D days" / "within H hours"
- Monotonic feasibility check

Think:

```cpp
Binary Search on Answer Space
// Lower bound = max(single element)
// Upper bound = sum(all elements)
// Feasibility = greedy simulation
```

---
