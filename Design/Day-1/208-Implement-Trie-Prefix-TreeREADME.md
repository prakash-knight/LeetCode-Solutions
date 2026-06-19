# 208. Implement Trie (Prefix Tree)

[Link to LeetCode Problem](https://leetcode.com/problems/implement-trie-prefix-tree/)

---

## 📝 Problem Statement

Implement a **Trie** (prefix tree) data structure with the following operations:

- `insert(word)` — Insert a string into the trie
- `search(word)` — Returns `true` if the word is in the trie
- `startsWith(prefix)` — Returns `true` if any word in the trie starts with the given prefix

### Example

```
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");    → true
trie.search("app");      → false
trie.startsWith("app");  → true
trie.insert("app");
trie.search("app");      → true
```

---

# 💡 Intuition & Approach

## Trie Node Structure

Each node stores:
- `bool isend` — marks whether a complete word ends here
- `vector<Trienode*> childs(26, nullptr)` — one pointer per lowercase letter

## Insert

Walk the trie character by character. If a child doesn't exist for a character, create it. At the end, mark `isend = true`.

## Search

Walk the trie character by character. If any child is `nullptr`, the word doesn't exist. At the end, return `crawl->isend` (must be a complete word, not just a prefix).

## startsWith

Same as search, but return `true` at the end regardless of `isend` (prefix doesn't need to be a complete word).

### Visual for insert("app") and insert("apple")

```
root
 └── 'a' (isend=F)
      └── 'p' (isend=F)
           └── 'p' (isend=T)   ← "app"
                └── 'l' (isend=F)
                     └── 'e' (isend=T)  ← "apple"
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
insert:     O(L)    where L = length of word
search:     O(L)
startsWith: O(L)
```

## Space Complexity

```
O(ALPHABET_SIZE × N × L)
```

- N = number of words, L = average word length
- Each node has 26 child pointers

---

# 💻 Code

```cpp
class Trie {
public:
    struct Trienode {
        bool isend = false;
        vector<Trienode*> childs = vector<Trienode*>(26, nullptr);
    };

    Trienode* root;

    Trienode* getnode() {
        Trienode* get = new Trienode();
        return get;
    }

    Trie() { root = new Trienode(); }

    void insert(string word) {
        Trienode* crawl = root;
        for (auto ch : word) {
            int idx = ch - 'a';
            if (crawl->childs[idx] == NULL) {
                crawl->childs[idx] = getnode();
            }
            crawl = crawl->childs[idx];
        }
        crawl->isend = true;
    }

    bool search(string word) {
        Trienode* crawl = root;
        for (auto ch : word) {
            int idx = ch - 'a';
            if (crawl->childs[idx] == nullptr)
                return false;
            crawl = crawl->childs[idx];
        }
        return crawl->isend;
    }

    bool startsWith(string word) {
        Trienode* crawl = root;
        for (auto ch : word) {
            int idx = ch - 'a';
            if (crawl->childs[idx] == nullptr)
                return false;
            crawl = crawl->childs[idx];
        }
        return true;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ `search("app")` before inserting `"app"` → returns `false` (only prefix exists, `isend=false`)

✅ `startsWith("app")` when `"apple"` is inserted → returns `true`

✅ Empty string → `crawl` stays at root, `root->isend` is `false` by default

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
search  → walk + check isend at end
startsWith → walk + return true (ignore isend)
```

The **only** difference between `search` and `startsWith` is the final return value.

## Common Mistakes

❌ Returning `true` in `search` without checking `isend` → confuses prefix with complete word.

❌ Using `map<char, Trienode*>` instead of `vector[26]` → correct but slower for lowercase-only problems.

❌ Not initializing `childs` to `nullptr` → dangling pointers.

---

## Related Problems

- 211. Design Add and Search Words Data Structure (wildcard `.`)
- 212. Word Search II (Trie + DFS on grid)
- 648. Replace Words
- 720. Longest Word in Dictionary

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Store and lookup strings by prefix
- Autocomplete, word suggestion, prefix matching

Think:

```
Trie: 26-child array node + isend flag
```

Core template:
```
insert:     create nodes along path, set isend=true at end
search:     walk path, return isend at end
startsWith: walk path, return true at end
```
