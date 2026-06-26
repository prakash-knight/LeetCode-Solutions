# 211. Design Add and Search Words Data Structure

[Link to LeetCode Problem](https://leetcode.com/problems/design-add-and-search-words-data-structure/)

---

## 📝 Problem Statement

Design a data structure that supports:
- `addWord(word)` — Adds a word to the data structure.
- `search(word)` — Returns `true` if the word matches any previously added word. The word may contain dots `.` where each dot can match **any** letter.

### Example

```
WordDictionary wd;
wd.addWord("bad");
wd.addWord("dad");
wd.addWord("mad");
wd.search("pad");   → false
wd.search("bad");   → true
wd.search(".ad");   → true
wd.search("b..");   → true
```

---

# 💡 Intuition & Approach

## Trie + DFS for Wildcard

1. **addWord**: Standard trie insertion — walk character by character, create nodes as needed, mark `isend = true` at the end.
2. **search**: Use DFS with backtracking:
   - If character is a letter → follow the specific child (standard trie search).
   - If character is `.` → try **all 26 children**. If any branch returns `true`, the word matches.
   - Base case: when `idx == word.size()`, return `isend`.

### Visual

```
Trie after inserting "bad", "dad", "mad":

root
 ├── 'b' → 'a' → 'd' (isend=T)
 ├── 'd' → 'a' → 'd' (isend=T)
 └── 'm' → 'a' → 'd' (isend=T)

search(".ad"):
  '.' matches 'b','d','m' → try all three
  → 'b'->'a'->'d' isend=T → return true!
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
addWord:  O(L)        where L = word length
search:   O(26^D × L) worst case, where D = number of dots
          O(L)        best case (no dots)
```

## Space Complexity

```
O(26 × N × L)
```

- N = number of words, L = average word length

---

# 💻 Code

```cpp
class WordDictionary {
public:
    struct TrieNode {
        bool isend;
        vector<TrieNode*> child = vector<TrieNode*>(26, NULL);

        TrieNode() { isend = false; }
    };

    TrieNode* root;

    WordDictionary() { root = new TrieNode(); }

    void addWord(string word) {
        TrieNode* ptr = root;

        for (auto ch : word) {
            if (ptr->child[ch - 'a'] == nullptr)
                ptr->child[ch - 'a'] = new TrieNode();
            ptr = ptr->child[ch - 'a'];
        }
        ptr->isend = true;
    }

    bool dfs(string word, int idx, TrieNode* root) {
        if (root == NULL)
            return false;
        if (idx == word.size())
            return root->isend;

        if (word[idx] == '.') {
            for (int i = 0; i < 26; i++) {
                if (root->child[i] != nullptr) {
                    if (dfs(word, idx + 1, root->child[i]))
                        return true;
                }
            }
        } else {
            if (root->child[word[idx] - 'a'] == nullptr)
                return false;
            root = root->child[word[idx] - 'a'];

            return dfs(word, idx + 1, root);
        }
        return false;
    }

    bool search(string word) {
        TrieNode* ptr = root;
        return dfs(word, 0, ptr);
    }
};
```

---

# 🔍 Edge Cases Handled

✅ All dots `"..."` → matches any 3-letter word

✅ No dots → standard trie search (fast path)

✅ Word not found (no matching prefix) → returns `false` early

✅ Prefix exists but `isend` is `false` → correctly returns `false`

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
'.' wildcard → DFS branching into ALL 26 children
Normal char  → follow single child (standard trie)
```

## Common Mistakes

❌ Forgetting to check `root == NULL` at the start of DFS → null pointer crash.

❌ Returning `true` at `idx == word.size()` without checking `isend` → prefix matches incorrectly.

❌ Not short-circuiting on the first `true` result when expanding `.` → wasted work.

---

## Related Problems

- 208. Implement Trie (Prefix Tree) (prerequisite)
- 212. Word Search II (Trie + DFS on grid)

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- String matching with wildcards
- Pattern search across a dictionary

Think:

```
Trie + DFS: normal chars follow one path,
wildcards branch into all children.
```
