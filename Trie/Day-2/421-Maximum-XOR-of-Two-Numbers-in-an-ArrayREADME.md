# 421. Maximum XOR of Two Numbers in an Array

[Link to LeetCode Problem](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/)

---

## 📝 Problem Statement

Given an integer array `nums`, return the maximum result of `nums[i] XOR nums[j]`, where `0 <= i <= j < n`.

### Example

```
Input:  nums = [3,10,5,25,2,8]
Output: 28
Explanation: The maximum result is 5 XOR 25 = 28.
```

---

# 💡 Intuition & Approach

## Binary Trie (Bit-by-Bit Greedy)

1. **Insert** every number into a binary trie (each path = 32 bits, MSB to LSB).
   - `left` child = bit 0, `right` child = bit 1.
2. For each number, **greedily traverse** the trie trying to pick the **opposite** bit at every level to maximize XOR.
   - If current bit is 0, try to go `right` (1) to get a 1 in the XOR result.
   - If current bit is 1, try to go `left` (0) to get a 1 in the XOR result.
   - If the opposite branch doesn't exist, take the same-side branch (contributes 0 to XOR).
3. Track the maximum XOR across all numbers.

### Visual

```
Insert 3  (000...011) and 25 (000...11001):

For num=5 (000...101), greedily pick opposite bits:
  bit 31...: same (both have 0s in high bits)
  bit 4: 5 has 0 → try right (1 from 25) → XOR bit = 1
  bit 3: 5 has 1 → try left  (0 from 25) → XOR bit = 1
  ...
  Result: 5 XOR 25 = 28
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(32 × N) = O(N)
```

- Insert: O(32) per number
- Query: O(32) per number

## Space Complexity

```
O(32 × N)
```

- At most 32 × N trie nodes

---

# 💻 Code

```cpp
class Solution {
public:
    struct TrieNode {
        TrieNode* left;  // 0
        TrieNode* right; // 1

        TrieNode() {
            left = nullptr;
            right = nullptr;
        }
    };

    void insert(TrieNode* root, int n) {
        TrieNode* crawl = root;
        for (int i = 31; i >= 0; i--) {

            if ((n & (1u << i)) == 0) {

                if (crawl->left == nullptr)
                    crawl->left = new TrieNode();

                crawl = crawl->left;
            } else {

                if (crawl->right == nullptr)
                    crawl->right = new TrieNode();

                crawl = crawl->right;
            }
        }
    }

    int maxor(TrieNode* root, int n) {
        TrieNode* ptr = root;
        int maxi = 0;
        for (int i = 31; i >= 0; i--) {
            if ((n & (1u << i)) == 0) {
                if (ptr->right != nullptr) {
                    maxi += 1u << i;
                    ptr = ptr->right;
                } else {
                    ptr = ptr->left;
                }
            } else {
                if (ptr->left != nullptr) {
                    maxi += 1u << i;
                    ptr = ptr->left;
                } else {
                    ptr = ptr->right;
                }
            }
        }
        return maxi;
    }

    int findMaximumXOR(vector<int>& nums) {
        TrieNode* root = new TrieNode();

        for (auto n : nums) {
            insert(root, n);
        }
        int maxi = 0;
        for (auto n : nums) {
            maxi = max(maxi, maxor(root, n));
        }
        return maxi;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Single element array → XOR with itself = 0

✅ All identical elements → XOR = 0

✅ Numbers with leading zeros handled correctly via `1u << i` (unsigned shift)

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
To maximize XOR, greedily pick the OPPOSITE bit at each level of the binary trie.
```

The trie lets us efficiently find, for each number, the number that differs in the most significant bits.

## Common Mistakes

❌ Using signed shift `1 << 31` instead of `1u << 31` → undefined behavior for bit 31.

❌ Forgetting to traverse all 32 bits (using `log2(max)` bits can miss cases).

---

## Related Problems

- 1707. Maximum XOR With an Element From Array (offline + trie)
- 1938. Maximum Genetic Difference Query

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Maximum XOR of two elements
- Bit-level optimization across pairs

Think:

```
Binary Trie: insert all numbers bit-by-bit (MSB→LSB),
then greedily pick opposite bits to maximize XOR.
```
