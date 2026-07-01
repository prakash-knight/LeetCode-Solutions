# 846. Hand of Straights

[Link to LeetCode Problem](https://leetcode.com/problems/hand-of-straights/)

---

## 📝 Problem Statement

Alice has some number of cards in a `hand`. She wants to rearrange the cards into groups so that each group is of size `groupSize`, and consists of `groupSize` **consecutive** cards.

Return `true` if she can rearrange the cards, or `false` otherwise.

### Example

```
Input:  hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
Output: true

Groups: [1,2,3], [2,3,4], [6,7,8]
```

---

# 💡 Intuition & Approach

## Sort + Greedy Frequency Map

1. If `hand.size() % groupSize != 0`, impossible → return false.
2. Sort the hand and count frequencies using a hash map.
3. For each card (in sorted order), if it still has frequency > 0, try to build a group starting from it:
   - Need `groupSize` consecutive numbers starting from this card.
   - Decrement frequency for each. If any is missing → return false.
4. Skip cards with frequency already 0.

```
hand = [1,2,2,3,3,4,6,7,8], gsize = 3
Start at 1: form [1,2,3] ✓
Start at 2: form [2,3,4] ✓
Start at 6: form [6,7,8] ✓
All consumed → true
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N log N + N * G) — sorting + greedy grouping
where N = hand.size(), G = groupSize
```

## Space Complexity

```
O(N) — hash map for frequencies
```

---

# 💻 Code

```cpp
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int gsize) {
        unordered_map<int, int> mp;

        if (hand.size() % gsize != 0)
            return false;
        sort(hand.begin(), hand.end());

        for (auto x : hand) {
            mp[x]++;
        }
        int j = 0;
        int i = 0;
        while (i < hand.size()) {
            int small = hand[i];
            if (mp[hand[i]] == 0) {
                i++;
                continue;
            }
            j = 0;
            while (j < gsize) {
                if (mp.find(small) == mp.end() || mp[small] == 0)
                    return false;
                mp[small]--;

                if (mp[small] == 0)
                    mp.erase(small);
                small++;
                j++;
            }
            i++;
        }

        return true;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Hand size not divisible by groupSize → early false

✅ Duplicate cards → frequency map handles multiple groups

✅ Single card groups (groupSize = 1) → always true

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Sort + start from smallest available card each time.
Greedily form consecutive groups from the smallest unused card.
Use frequency map to track available cards.
```

## Common Mistakes

❌ Not sorting first → can't guarantee starting from the smallest.

❌ Forgetting the modulo check → wastes time on impossible inputs.

---

## Related Problems

- 1296. Divide Array in Sets of K Consecutive Numbers (identical problem)
- 659. Split Array into Consecutive Subsequences

---

# 🧠 Revision Notes

## Pattern Recognition

When grouping into consecutive sequences:

```
Sort + frequency map + greedy from smallest.
Always try to start a group from the smallest unused element.
```
