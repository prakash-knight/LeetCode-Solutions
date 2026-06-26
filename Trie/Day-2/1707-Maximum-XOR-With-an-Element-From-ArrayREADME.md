# 1707. Maximum XOR With an Element From Array

[Link to LeetCode Problem](https://leetcode.com/problems/maximum-xor-with-an-element-from-array/)

---

## 📝 Problem Statement

Given an array `nums` and queries where each query is `[xi, mi]`, find the maximum `xi XOR nums[j]` such that `nums[j] <= mi`. If no such element exists, return `-1`.

### Example

```
Input:  nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
Output: [3,3,7]
Explanation:
  query [3,1]: nums elements ≤ 1 are {0,1}. Max XOR = 3 XOR 0 = 3.
  query [1,3]: nums elements ≤ 3 are {0,1,2,3}. Max XOR = 1 XOR 2 = 3.
  query [5,6]: all elements qualify. Max XOR = 5 XOR 2 = 7.
```

---

# 💡 Intuition & Approach

## Offline Queries + Binary Trie

1. **Sort `nums`** in ascending order.
2. **Sort queries by `mi`** (the upper bound), keeping track of original indices.
3. Process queries in order of increasing `mi`:
   - Insert all `nums[j] <= mi` into the binary trie.
   - If no elements have been inserted, answer is `-1`.
   - Otherwise, greedily find max XOR of `xi` against the trie (same as LC 421).
4. Place each answer at its original index.

### Why Offline?

By sorting queries by `mi`, we only need to **incrementally add** elements to the trie (never remove), making it efficient.

```
nums (sorted): [0, 1, 2, 3, 4]
queries sorted by mi: [[3,1], [1,3], [5,6]]

Query [3,1]: insert 0,1 → maxXOR(3) = 3
Query [1,3]: insert 2,3 → maxXOR(1) = 3
Query [5,6]: insert 4   → maxXOR(5) = 7
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(N log N + Q log Q + 32(N + Q))
```

- Sorting nums: O(N log N)
- Sorting queries: O(Q log Q)
- Insert + query: O(32) each

## Space Complexity

```
O(32 × N + Q)
```

- Trie: O(32 × N) nodes
- Answer array: O(Q)

---

# 💻 Code

```cpp
class Solution {
public:
    static bool cmp(vector<int>& a, vector<int>& b) { return a[1] < b[1]; }

    struct TrieNode {
        TrieNode* left;
        TrieNode* right;

        TrieNode() {
            left = nullptr;
            right = nullptr;
        }
    };

    void insert(TrieNode* root, int n) {
        TrieNode* ptr = root;

        for (int i = 31; i >= 0; i--) {
            if ((n & (1u << i)) == 0) {
                if (ptr->left == nullptr)
                    ptr->left = new TrieNode();
                ptr = ptr->left;
            } else {
                if (ptr->right == nullptr)
                    ptr->right = new TrieNode();
                ptr = ptr->right;
            }
        }
    }

    int maxor(TrieNode* root, int n) {
        TrieNode* ptr = root;
        int maxi = 0;

        for (int i = 31; i >= 0; i--) {
            if ((n & (1u << i)) == 0) {
                if (ptr->right != nullptr) {
                    maxi |= (1u << i);
                    ptr = ptr->right;
                } else {
                    ptr = ptr->left;
                }
            } else {
                if (ptr->left != nullptr) {
                    maxi |= (1u << i);
                    ptr = ptr->left;
                } else {
                    ptr = ptr->right;
                }
            }
        }
        return maxi;
    }

    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& q) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> queries;

        for (int i = 0; i < q.size(); i++) {
            queries.push_back({q[i][0], q[i][1], i});
        }

        sort(queries.begin(), queries.end(), cmp);

        TrieNode* root = new TrieNode();

        vector<int> ans(q.size());
        int idx = 0;

        for (int i = 0; i < queries.size(); i++) {

            int x = queries[i][0];
            int m = queries[i][1];
            int originalIdx = queries[i][2];

            while (idx < nums.size() && nums[idx] <= m) {
                insert(root, nums[idx]);
                idx++;
            }

            if (idx == 0) {
                ans[originalIdx] = -1;
            } else {
                ans[originalIdx] = maxor(root, x);
            }
        }

        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ No elements ≤ `mi` → return `-1`

✅ All elements ≤ `mi` → full trie search

✅ Multiple queries with same `mi` → handled by sort stability

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Offline processing: sort queries by constraint (mi),
then incrementally build the trie — never need to delete.
```

## Common Mistakes

❌ Processing queries online (re-building trie per query) → TLE.

❌ Forgetting to track original query indices → wrong answer placement.

❌ Not handling the `idx == 0` case (empty trie) → null pointer crash.

---

## Related Problems

- 421. Maximum XOR of Two Numbers in an Array (simpler version)
- 1938. Maximum Genetic Difference Query

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Maximum XOR with a constraint on element values
- Queries with upper/lower bounds on which elements to consider

Think:

```
Offline queries: sort by constraint, incrementally build trie.
Same greedy XOR logic as LC 421.
```
