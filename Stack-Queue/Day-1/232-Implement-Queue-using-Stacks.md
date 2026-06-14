# 232. Implement Queue using Stacks

[Link to LeetCode Problem](https://leetcode.com/problems/implement-queue-using-stacks/)

---

## 1. 📝 Problem Statement

Implement a **first-in-first-out (FIFO) queue** using only **two stacks**. The implemented queue should support all the functions of a normal queue (`push`, `peek`, `pop`, and `empty`).

### Implement the `MyQueue` class:
- `void push(int x)` — Pushes element `x` to the back of the queue.
- `int pop()` — Removes the element from the front of the queue and returns it.
- `int peek()` — Returns the element at the front without removing it.
- `boolean empty()` — Returns `true` if the queue is empty, `false` otherwise.

### Constraints
- `1 <= x <= 9`
- At most `100` calls will be made.
- All calls to `pop` and `peek` are valid.
- **Follow-up**: Can you implement the queue such that each operation is **amortized O(1)** time complexity?

---

## 2. 💡 Intuition

### How should I think about this problem?

A stack is **LIFO** but a queue is **FIFO**. By maintaining a **peek variable** that tracks the current front, and carefully managing two stacks, we can simulate FIFO behavior.

### Key Observations

1. **Push is always to `q1`**.
2. The **peek** (front of queue) is always the first element ever pushed that hasn't been popped.
3. On `pop()`, we need to remove the **bottom** of `q1` — we move elements to `q2` temporarily, pop the bottom from `q1`, then move everything back.

---

## 3. 🚀 Approach — Two Stacks with Peek Cache

### Logic (Step-by-Step)

**push(x)**:
- Push to `q1`.
- If this is the first element (`!yeh`), record it as `pek` (front of queue).

**pop()**:
1. Move all but the last element from `q1` to `q2`.
2. The last element in `q1` is the front of the queue — pop and return it.
3. Update `pek`: the new front is `q2.top()` if `q2` is non-empty.
4. Move everything from `q2` back to `q1`.

**peek()**: Return `pek` directly. `O(1)`.

**empty()**: `q1.empty()`.

### 🔍 Dry Run

```
push(1): q1=[1], pek=1, yeh=true
push(2): q1=[1,2]
push(3): q1=[1,2,3]

peek() → 1 ✅   (pek cached)

pop():
  Move 2,3 to q2: q1=[1], q2=[3,2]
  q2 not empty → pek = q2.top() = 2
  Pop q1.top() = 1 → q1=[]
  Move back: q1=[2,3], q2=[]
  return 1 ✅

peek() → 2 ✅
```

---

## 4. 💻 Code (C++)

```cpp
class MyQueue {
public:
    stack<int> q1;
    stack<int> q2;
    int pek = INT_MIN;
    bool yeh = false;

    MyQueue() {}

    void push(int x) {
        q1.push(x);
        if (!yeh) {
            pek = x;
            yeh = true;
        }
    }

    int pop() {
        while (q1.size() != 1) {
            q2.push(q1.top());
            q1.pop();
        }
        if (!q2.empty()) pek = q2.top();
        else {
            pek = INT_MIN;
            yeh = false;
        }

        int x = q1.top();
        q1.pop();

        while (!q2.empty()) {
            q1.push(q2.top());
            q2.pop();
        }
        return x;
    }

    int peek() { return pek; }

    bool empty() { return q1.empty(); }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `q1` | Primary stack — holds all elements |
| `q2` | Temporary stack for rearranging during pop |
| `pek` | Cached front of queue for O(1) peek |
| `yeh` | Whether the queue is non-empty (front is valid) |

---

## 5. 💡 Cleaner Alternative — Amortized O(1) (Two-Stack Lazy Transfer)

The standard interview approach uses **lazy transfer**: only move elements from `q1` to `q2` when `q2` is empty.

```cpp
class MyQueue {
public:
    stack<int> in, out;

    void push(int x) {
        in.push(x);
    }

    int pop() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        int x = out.top();
        out.pop();
        return x;
    }

    int peek() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        return out.top();
    }

    bool empty() { return in.empty() && out.empty(); }
};
```

- **Push**: O(1)
- **Pop/Peek**: Amortized O(1) — each element is moved at most once from `in` to `out`.

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Stack Simulation of Queue**

### When to use:
- Classic interview problem about data structure simulation.
- When you need amortized O(1) for all queue operations using stacks.

| Pattern | How it applies |
|---------|---------------|
| **Two Stacks** | `in` for push, `out` for pop — reversing order twice = original order |
| **Lazy Transfer** | Move elements only when `out` is empty (amortized O(1)) |

> 🧠 **Mental Model**: "Two reversals = original order. Stack reverses once. Two stacks reverse twice = FIFO."

---

## 7. ⚠️ Common Mistakes

### ❌ Moving elements back after every pop
The lazy transfer approach is key — only move when `out` is empty, not on every operation.

### ❌ Forgetting empty() must check both stacks
```cpp
// WRONG: only checks one stack
bool empty() { return q1.empty(); }

// CORRECT (lazy approach)
bool empty() { return in.empty() && out.empty(); }
```

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "Prove amortized O(1) for pop."
**Answer**: Each element is pushed to `in` once and moved to `out` once. Total work per element = 2 operations. Amortized O(1) per pop.

### Q2: "Can you do it with one stack?"
**Answer**: Not efficiently. You'd need recursion (the call stack acts as a second stack), but that's essentially the same idea.

---

## 9. 📊 Complexity Analysis

| Operation | Time (Original) | Time (Lazy) |
|-----------|-----------------|-------------|
| `push` | O(1) | O(1) |
| `pop` | O(n) | Amortized O(1) |
| `peek` | O(1) | Amortized O(1) |
| `empty` | O(1) | O(1) |

**Space**: `O(n)` — all elements stored across the two stacks.
