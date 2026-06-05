# 875. Koko Eating Bananas

[Link to LeetCode Problem](https://leetcode.com/problems/koko-eating-bananas/)

---

## 📝 Problem Statement

Koko loves to eat bananas. There are `n` piles of bananas, where `piles[i]` is the number of bananas in the `i`-th pile.

The guards have gone and will come back in `h` hours. Koko can decide her bananas-per-hour eating speed `k`. Each hour, she chooses a pile and eats `k` bananas from it. If the pile has fewer than `k` bananas, she eats all of them and won't eat any more that hour.

Return the minimum integer `k` such that she can eat all the bananas within `h` hours.

### Example

```cpp
Input:
piles = [3,6,7,11], h = 8

Output:
4
```

Because:

```cpp
At speed k=4:
  Pile 3: ceil(3/4) = 1 hour
  Pile 6: ceil(6/4) = 2 hours
  Pile 7: ceil(7/4) = 2 hours
  Pile 11: ceil(11/4) = 3 hours
  Total = 8 hours ≤ h ✅
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

Try every speed from 1 to max(piles). For each, calculate total hours.

### Why is it inefficient?

```cpp
O(max(piles) × n)
```

time complexity — trying every possible speed linearly.

---

## 2. Optimized Approach (Binary Search on Answer)

### Pattern Used

```cpp
Binary Search on Answer Space
```

### Main Idea

The answer `k` lies in the range `[1, max(piles)]`. As `k` increases, the total hours needed **decreases** (monotonic relationship). This monotonicity allows binary search:

- If `totalHours(k) <= h` → `k` might be the answer, try smaller: `e = mid - 1`.
- If `totalHours(k) > h` → `k` is too slow, try larger: `s = mid + 1`.

### Helper Function: Calculate Hours

For a given speed `mid`, the hours needed to eat pile `x` is:

```cpp
ceil(x / mid) = (x + mid - 1) / mid   // integer ceiling without using float
```

Total hours = sum of `ceil(x / mid)` for all piles.

---

## Step-by-Step Logic

1. Sort piles (optional, for clarity).
2. Set search range:

```cpp
s = 1                        // minimum speed
e = max(piles)               // maximum speed (eat any pile in 1 hour)
```

3. Binary search:
   - Compute `time = cal(piles, mid)` — total hours at speed `mid`.
   - If `time <= h` → valid speed, save answer, try smaller: `e = mid - 1`.
   - If `time > h` → too slow: `s = mid + 1`.

4. Return `ans`.

---

### Dry Run

```cpp
piles = [3, 6, 7, 11], h = 8

s=1, e=11, ans=11

Iteration 1: mid=6 → hours = 1+1+2+2 = 6 ≤ 8 → ans=6, e=5
Iteration 2: mid=3 → hours = 1+2+3+4 = 10 > 8 → s=4
Iteration 3: mid=4 → hours = 1+2+2+3 = 8 ≤ 8 → ans=4, e=3
Loop ends: s=4 > e=3 → return ans=4 ✅
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n × log(max(piles)))
```

Because:
- Binary search runs `O(log(max(piles)))` iterations.
- Each iteration computes total hours in `O(n)`.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only a few variables used (excluding input).

---

# 💻 Code

```cpp
class Solution {
public:
    long long cal(vector<int>& p, int mid) {
        long long h = 0;
        for (auto x : p) {
            h += (x + mid - 1) / mid;
        }
        return h;
    }

    int minEatingSpeed(vector<int>& p, int h) {
        sort(p.begin(), p.end());

        long long e = p[p.size() - 1];
        long long s = 1;
        long long ans = e;

        while (s <= e) {
            long long mid = s + (e - s) / 2;
            long long time = cal(p, mid);

            if (time <= h) {
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

✅ h equals number of piles (maximum speed needed)

```cpp
piles = [3, 6, 7, 11], h = 4
// Output: 11 (must eat each pile in 1 hour)
```

---

✅ h is very large (minimum speed = 1)

```cpp
piles = [3, 6, 7, 11], h = 100
// Output: 1
```

---

✅ Single pile

```cpp
piles = [10], h = 5
// Output: 2 (ceil(10/2) = 5 hours)
```

---

✅ All piles same size

```cpp
piles = [5, 5, 5], h = 3
// Output: 5
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

**Binary search on the answer** — instead of searching in the array, we binary search on the solution space `[1, max(piles)]`. The monotonic relationship between speed and time enables this.

---

## Common Mistakes

❌ Integer overflow:

Sum of `ceil(x/mid)` for large arrays can overflow `int`. Use `long long` for the total hours calculation.

---

❌ Wrong ceiling formula:

`ceil(a/b)` in integer math is `(a + b - 1) / b`, **not** `a / b + 1` (which is wrong when `a` is divisible by `b`).

---

❌ Search range errors:

Minimum speed is `1` (not `0` — division by zero). Maximum speed is `max(piles)` (not sum).

---

## Related Problems

- 1011 — Capacity To Ship Packages Within D Days (same pattern)
- 410 — Split Array Largest Sum
- 1283 — Find the Smallest Divisor Given a Threshold

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Minimize the maximum / minimize speed / find optimal rate
- Monotonic relationship between parameter and feasibility
- "Can we do it with this parameter?" → binary search on parameter

Think:

```cpp
Binary Search on Answer Space
// 1. Define search range [lo, hi]
// 2. Write feasibility check function
// 3. Binary search: feasible → try smaller, infeasible → try larger
```

---
