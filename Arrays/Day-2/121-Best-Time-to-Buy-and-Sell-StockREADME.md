# 121. Best Time to Buy and Sell Stock

[Link to LeetCode Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

---

## 📝 Problem Statement

You are given an array `prices` where `prices[i]` is the price of a given stock on the `i`-th day.

You want to maximize your profit by choosing a single day to buy and a single day to sell.

Return the maximum profit you can achieve. If no profit is possible, return `0`.

### Example

```cpp
Input:
prices = [7,1,5,3,6,4]

Output:
5
```

Because:

```cpp
Buy on day 2 (price = 1), sell on day 5 (price = 6).
Profit = 6 - 1 = 5.
```

---

# 💡 Intuition & Approach

## 1. Brute Force Approach

The most straightforward method is:
- For every day, check all future days for the maximum selling price.
- Track the maximum profit.

### Why is it inefficient?

```cpp
O(n²)
```

time complexity due to nested loops.

---

## 2. Optimized Approach (One Pass — Track Minimum)

### Pattern Used

```cpp
Greedy — Track Minimum So Far
```

### Main Idea

As we traverse the prices:
- Keep track of the **minimum price** seen so far (best day to buy).
- At each day, compute the profit if we sell today.
- Update the maximum profit.

```cpp
profit_today = prices[i] - min_price_so_far
```

Since we always buy at the lowest past price, this guarantees the maximum profit.

---

## Step-by-Step Logic

1. Initialize:

```cpp
mini = INT_MAX   // minimum price seen so far
sum = 0          // maximum profit
```

2. For each day:
   - Update minimum: `mini = min(prices[i], mini)`
   - Update profit: `sum = max(prices[i] - mini, sum)`

3. Return `sum`.

---

# ⏱️ Complexity Analysis

## Time Complexity

```cpp
O(n)
```

Because:
- Single pass through the array.

---

## Space Complexity

```cpp
O(1)
```

Because:
- Only two variables used.

---

# 💻 Code

```cpp
class Solution {
public:
    int maxProfit(vector<int>& p) {
        int mini = INT_MAX;
        int sum = 0;

        for (int i = 0; i < p.size(); i++) {
            mini = min(p[i], mini);
            sum = max(p[i] - mini, sum);
        }

        return sum;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Prices only decrease

```cpp
prices = [7, 6, 4, 3, 1]
// Output: 0 (no profitable transaction)
```

---

✅ Single day

```cpp
prices = [5]
// Output: 0
```

---

✅ All same prices

```cpp
prices = [3, 3, 3]
// Output: 0
```

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

Instead of checking all pairs:
- Track the minimum price seen so far.
- At each day, the best profit is `current_price - min_so_far`.
- This is a greedy approach — always buy at the cheapest past price.

---

## Common Mistakes

❌ Selling before buying:

The problem requires buying **before** selling. By iterating left to right and tracking the minimum, we naturally enforce this constraint.

---

❌ Returning negative profit:

If prices only decrease, the answer is `0`, not a negative number. Initializing `sum = 0` handles this.

---

## Related Problems

- Best Time to Buy and Sell Stock II (multiple transactions)
- Best Time to Buy and Sell Stock III (at most 2 transactions)
- Best Time to Buy and Sell Stock IV (at most k transactions)
- Best Time to Buy and Sell Stock with Cooldown

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Maximize difference (sell - buy) with order constraint
- Track minimum/maximum so far
- One-pass greedy optimization

Think:

```cpp
Track Min So Far + Greedy
```

---
