# 29. Divide Two Integers

[Link to LeetCode Problem](https://leetcode.com/problems/divide-two-integers/)

---

## 📝 Problem Statement

Given two integers `dividend` and `divisor`, divide them **without using multiplication, division, or mod operators**. Return the quotient truncated toward zero. The result is clamped to `[−2³¹, 2³¹ − 1]`.

### Example

```
Input:  dividend = 10, divisor = 3   → Output: 3
Input:  dividend = 7,  divisor = -3  → Output: -2
```

---

# 💡 Intuition & Approach

## Exponential Bit Doubling

Instead of subtracting the divisor one at a time (O(dividend/divisor)), we **double** the divisor using bit shifts:

```
Find the largest  n × divisor ≤ dividend  where  n  is a power of 2
Subtract  n × divisor  from dividend and add  n  to the quotient
Repeat until dividend < divisor
```

### Trace for 10 ÷ 3

```
d=10, n=3
  pow=1: 3*(1<<1)=6 ≤ 10 → pow<<=1 → pow=2
  pow=2: 3*(1<<1)=12 > 10 → stop
  d = 10 - 3*2 = 4,  count = 2

d=4, n=3
  pow=1: 3*(1<<1)=6 > 4 → stop
  d = 4 - 3*1 = 1,  count = 3

d=1 < n=3 → stop
Result = 3 ✅
```

## Sign Handling

- Determine result sign using XOR of signs: `positive XOR positive = positive`
- Work with absolute values (`long long` to avoid overflow)
- Apply sign at the end

## Overflow Guard

- `INT_MIN / -1 = 2³¹` which overflows → return `INT_MAX`

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(log²(dividend))
```

- Outer loop runs O(log(dividend/divisor)) times
- Inner while loop runs O(log(dividend)) times

## Space Complexity

```
O(1)
```

---

# 💻 Code

```cpp
class Solution {
public:
    int divide(int div, int divi) {
        if (div == INT_MIN && divi == -1)
            return INT_MAX;

        bool sign = !((div < 0) ^ (divi < 0));

        long long d = llabs((long long)div);
        long long n = llabs((long long)divi);

        long long count = 0;

        while (d >= n) {
            long long pow = 1;

            while ((n * (pow << 1)) <= d) {
                pow <<= 1;
            }

            d -= n * pow;
            count += pow;
        }

        return sign ? count : -count;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ `INT_MIN / -1` → would overflow → return `INT_MAX`

✅ Negative dividend or divisor → sign handled separately

✅ `dividend < divisor` → outer while doesn't execute → returns `0`

✅ `divisor = 1` → quotient = dividend

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Bit-shift doubling: find largest power-of-2 multiple of divisor ≤ remaining dividend
```

This is essentially long division in binary, reducing O(n) subtractions to O(log² n).

## Common Mistakes

❌ Using `int` instead of `long long` → `INT_MIN` cast to `abs` overflows.

❌ Forgetting the `INT_MIN / -1` edge case → undefined behavior.

❌ Using `pow * 2` instead of `pow << 1` — both work, but bit shift is more idiomatic here.

---

## Related Problems

- 50. Pow(x, n)
- 69. Sqrt(x)
- 231. Power of Two

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question forbids `*`, `/`, `%` and asks for division:

Think:

```
Exponential doubling with bit shifts (binary long division)
```

Key template:
```
while (d >= n) {
    pow = 1
    while (n * (pow << 1) <= d) pow <<= 1
    d -= n * pow
    count += pow
}
```
