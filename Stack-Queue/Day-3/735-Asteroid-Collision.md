# 735. Asteroid Collision

[Link to LeetCode Problem](https://leetcode.com/problems/asteroid-collision/)

---

## 1. 📝 Problem Statement

We are given an array `asteroids` of integers representing asteroids in a row. For each asteroid, the **absolute value** represents its size, and the **sign** represents its direction (`+` = right, `-` = left).

All asteroids move at the same speed. Find out the state of the asteroids after all collisions. If two asteroids meet:
- The smaller one explodes.
- If the same size, **both** explode.
- Two asteroids moving in the **same direction** never meet.

### Example

```
Input:  asteroids = [5,10,-5]
Output: [5,10]

Input:  asteroids = [8,-8]
Output: []

Input:  asteroids = [10,2,-5]
Output: [10]
```

### Constraints
- `2 <= asteroids.length <= 10⁴`
- `-1000 <= asteroids[i] <= 1000`
- `asteroids[i] != 0`

---

## 2. 💡 Intuition

### How should I think about this problem?

A collision only happens when a **positive asteroid** (moving right) is followed by a **negative asteroid** (moving left). Use a **stack** to simulate.

### Key Rules

1. **Positive asteroid**: Push to stack (moves right, will potentially collide with future left-movers).
2. **Negative asteroid**: Collide with the stack top if the top is positive:
   - `|top| < |current|` → top explodes, continue checking.
   - `|top| == |current|` → both explode (pop top, skip current).
   - `|top| > |current|` → current explodes (skip current).
3. If no collision (stack empty or top is negative): push current.

### Visualization

```
asteroids = [10, 2, -5]

Push 10 → stack: [10]
Push 2  → stack: [10, 2]
-5 arrives:
  top=2, |2| < |-5| → 2 explodes → stack: [10]
  top=10, |10| > |-5| → -5 explodes → stop
Result: [10] ✅
```

---

## 3. 🐢 Brute Force Approach

Repeatedly scan the array, find the first collision, resolve it, repeat until no collisions remain.

- **Time**: `O(n²)` — repeated scanning
- **Space**: `O(n)`

---

## 4. 🚀 Optimal Approach — Stack Simulation

### Logic (Step-by-Step)

For each asteroid `as[i]`:
- If `as[i] > 0`: push (no collision possible).
- If `as[i] < 0`:
  1. While stack non-empty AND `s.top() > 0` AND `s.top() < |as[i]|`: pop (top explodes).
  2. If stack non-empty AND `s.top() > 0` AND `s.top() == |as[i]|`: pop both (mutual destruction), skip `as[i]`.
  3. If stack non-empty AND `s.top() > 0` AND `s.top() > |as[i]|`: skip `as[i]` (current explodes).
  4. Otherwise (stack empty or top is negative): push `as[i]`.

At the end, collect the stack contents.

---

## 5. 💻 Code (C++)

```cpp
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& as) {
        stack<int> s;

        for (int i = 0; i < as.size(); i++) {
            if (as[i] < 0) {
                // Collision possible: keep destroying right-movers
                while (!s.empty() && abs(as[i]) > s.top() && s.top() > 0)
                    s.pop();

                // Equal size: both explode
                if (!s.empty() && s.top() > 0 && s.top() == abs(as[i])) {
                    s.pop();
                    continue;
                }

                // Current asteroid destroyed by larger right-mover
                if (!s.empty() && s.top() > abs(as[i]) && s.top() > 0)
                    continue;
            }

            s.push(as[i]);
        }

        vector<int> ans;
        while (!s.empty()) {
            ans.push_back(s.top());
            s.pop();
        }
        reverse(ans.begin(), ans.end());

        return ans;
    }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `s` | Stack of surviving asteroids |
| `as[i]` | Current asteroid being processed |
| `ans` | Final result (reversed stack contents) |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Stack — Event-driven Simulation**

### When to use:
- Simulating physical interactions where items "collide" or "cancel" based on a rule.
- Processing a stream where new items interact with the most recent item.

| Pattern | How it applies |
|---------|---------------|
| **Stack** | Stores "unresolved" asteroids waiting for collision |
| **Greedy Simulation** | Resolve collisions immediately as they appear |

> 🧠 **Mental Model**: "The stack holds all right-movers still alive. A left-mover fights the rightmost right-mover. Keep fighting until the left-mover survives or explodes."

---

## 7. ⚠️ Common Mistakes

### ❌ Forgetting to check `s.top() > 0` in the while loop
Two left-movers (both negative) should never collide.

### ❌ Handling equal-size case incorrectly
Both explode → pop top AND skip current (`continue`).

### ❌ Pushing the current asteroid when it was destroyed
The three `if/continue` branches handle cases where the current asteroid is destroyed. If none triggered → push.

### ❌ Not reversing the stack at the end
Stack gives elements in LIFO order; reverse to get left-to-right order.

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "What if asteroids could also collide with same-direction neighbors?"
**Answer**: Same-direction asteroids never collide (they move at the same speed), so no change needed.

### Q2: "Can you solve without reversing at the end?"
**Answer**: Use a `deque` and push to front; or collect into a vector and return it (the stack gives reverse order, so push front or reverse).

### Q3: "What's the maximum number of collisions?"
**Answer**: At most `n-1` collisions for an input of size `n`.

---

## 9. 📊 Complexity Analysis

### Time Complexity: `O(n)`
- Each asteroid is pushed and popped at most once.

### Space Complexity: `O(n)`
- Stack stores at most `n` asteroids.
