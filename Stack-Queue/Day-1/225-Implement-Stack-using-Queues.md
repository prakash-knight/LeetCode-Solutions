# 225. Implement Stack using Queues

[Link to LeetCode Problem](https://leetcode.com/problems/implement-stack-using-queues/)

---

## 1. 📝 Problem Statement

Implement a **last-in-first-out (LIFO) stack** using only **two queues**. The implemented stack should support all the functions of a normal stack (`push`, `top`, `pop`, and `empty`).

### Implement the `MyStack` class:
- `void push(int x)` — Pushes element `x` to the top of the stack.
- `int pop()` — Removes the element on the top of the stack and returns it.
- `int top()` — Returns the element on the top of the stack.
- `boolean empty()` — Returns `true` if the stack is empty, `false` otherwise.

### Constraints
- `1 <= x <= 9`
- At most `100` calls will be made to `push`, `pop`, `top`, and `empty`.
- All calls to `pop` and `top` are valid (stack is non-empty).

---

## 2. 💡 Intuition

### How should I think about this problem?

A queue is **FIFO** (first-in-first-out), but a stack is **LIFO** (last-in-first-out). To simulate LIFO using FIFO queues, we need to rearrange elements on every `pop`/`top` operation.

### Key Idea

- Keep **all elements in `q1`** (active queue).
- On `pop`/`top`: move all elements **except the last** from `q1` to `q2`. The last element in `q1` is the "top" of the stack.
- Swap `q1` and `q2` so `q1` is always the active queue.

### Visualization

```
push(1), push(2), push(3)
q1: [1, 2, 3]   (front → back, so 3 is back = top of stack)

pop():
  Move 1, 2 to q2 → q1: [3], q2: [1, 2]
  Pop q1.front() = 3 ✅
  swap → q1: [1, 2], q2: []
```

---

## 3. 🐢 Brute Force Approach

Use a single queue. On `push`, enqueue and then rotate all previous elements to the back, making the new element the front.

```cpp
void push(int x) {
    q1.push(x);
    for (int i = 0; i < q1.size() - 1; i++) {
        q1.push(q1.front());
        q1.pop();
    }
}
// Now q1.front() is always the "top"
```

- **Push**: `O(n)` — rotate queue
- **Pop/Top**: `O(1)` — just access front

---

## 4. 🚀 Optimal Approach — Two Queues (Lazy Pop)

### Logic (Step-by-Step)

**push(x)**: Simply push to `q1`. `O(1)`.

**pop()**:
1. Move all elements except the last from `q1` → `q2`.
2. The remaining element in `q1` is the top → save it, pop it.
3. Swap `q1` and `q2`.
4. Return saved value.

**top()**: Same as `pop()`, but also re-enqueue the top element into `q2` before swapping.

**empty()**: `q1.empty()`.

### 🔍 Dry Run

```
push(1): q1=[1], q2=[]
push(2): q1=[1,2], q2=[]
push(3): q1=[1,2,3], q2=[]

top():
  Move 1,2 to q2 → q1=[3], q2=[1,2]
  x = q1.front() = 3
  Re-enqueue 3 into q2 → q2=[1,2,3]
  q1.pop() → q1=[]
  swap → q1=[1,2,3], q2=[]
  return 3 ✅

pop():
  Move 1,2 to q2 → q1=[3], q2=[1,2]
  x = q1.front() = 3, pop → q1=[]
  swap → q1=[1,2], q2=[]
  return 3 ✅
```

---

## 5. 💻 Code (C++)

```cpp
class MyStack {
public:
    queue<int> q1;
    queue<int> q2;

    MyStack() {}

    void push(int x) { q1.push(x); }

    int pop() {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }

        int x = q1.front();
        q1.pop();

        swap(q1, q2);

        return x;
    }

    int top() {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }

        int x = q1.front();

        q2.push(x);
        q1.pop();

        swap(q1, q2);

        return x;
    }

    bool empty() { return q1.empty(); }
};
```

### Variable Purpose Table

| Variable | Purpose |
|----------|---------|
| `q1` | Active queue — always holds all elements |
| `q2` | Temporary queue — used during pop/top to hold prefix |
| `x` | The top element being returned |

---

## 6. 🧩 Pattern Recognition

### Primary Pattern: **Queue Simulation of Stack (Lazy Operation)**

### When to use:
- Interview question asking to implement one data structure using another.
- When you only have FIFO primitives but need LIFO behavior.

| Pattern | How it applies |
|---------|---------------|
| **Two Queues** | One active, one temporary buffer |
| **Swap trick** | After each operation, the active queue is restored |

> 🧠 **Mental Model**: "To get the last element of a queue, drain everything before it into a second queue, grab it, then put everything back."

---

## 7. ⚠️ Common Mistakes

### ❌ Forgetting to re-enqueue the top element in `top()`
In `top()`, the element must be re-enqueued into `q2` before swapping — unlike `pop()` where it's discarded.

### ❌ Not swapping after pop/top
Without the swap, `q1` would be empty and `q2` would hold the remaining elements, breaking the invariant.

### ❌ Using `q1.back()` directly
`std::queue` doesn't support `back()` access in all versions without caution. The drain-and-swap approach is safer and more general.

---

## 8. 🎤 Interview Follow-up Questions

### Q1: "Can you do it with one queue?"
**Answer**: Yes. On `push`, enqueue `x`, then rotate all previous elements to the back (dequeue and re-enqueue `size-1` elements). Now `x` is at the front = top.

### Q2: "Which operation do you want to be O(1)?"
**Answer**: Trade-off. You can make `push` O(1) and `pop`/`top` O(n), or `push` O(n) and `pop`/`top` O(1). This solution does the former.

### Q3: "What's the space complexity?"
**Answer**: O(n) — all elements are stored between the two queues.

---

## 9. 📊 Complexity Analysis

| Operation | Time | Space |
|-----------|------|-------|
| `push` | O(1) | O(1) |
| `pop` | O(n) | O(1) |
| `top` | O(n) | O(1) |
| `empty` | O(1) | O(1) |

**Overall Space**: `O(n)` — `n` elements stored across `q1` and `q2`.
