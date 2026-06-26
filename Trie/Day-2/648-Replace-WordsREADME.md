# 648. Replace Words

[Link to LeetCode Problem](https://leetcode.com/problems/replace-words/)

---

## 📝 Problem Statement

Given a dictionary of root words and a sentence, replace every word in the sentence with its **shortest root** (prefix) from the dictionary. If a word has no root in the dictionary, keep it unchanged.

### Example

```
Input:  dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
```

---

# 💡 Intuition & Approach

## Trie-based Shortest Prefix Search

1. **Insert** all dictionary roots into a trie, marking `isend = true` at each root's end.
2. For each word in the sentence:
   - Walk the trie character by character.
   - If we hit `isend = true` → return the prefix built so far (shortest root found).
   - If we hit a `nullptr` child → no root exists, return original word.
   - If we exhaust the word → return root if `isend`, else original word.

### Visual

```
Dictionary: ["cat", "bat"]

Trie:
root
 ├── 'b' → 'a' → 't' (isend=T)
 └── 'c' → 'a' → 't' (isend=T)

Word "cattle":
  c → a → t → isend=T → return "cat" (stop early!)
```

---

# ⏱️ Complexity Analysis

## Time Complexity

```
O(D × L + S)
```

- D = number of dictionary words, L = average root length (trie build)
- S = total characters in sentence (search)

## Space Complexity

```
O(26 × D × L)
```

- Trie storage for dictionary

---

# 💻 Code

```cpp
class Solution {
public:
    struct TrieNode {
        bool isend;
        vector<TrieNode*> child = vector<TrieNode*>(26, nullptr);

        TrieNode() { isend = false; }
    };
    TrieNode* root = new TrieNode();

    void insert(vector<string>& dic) {
        for (auto d : dic) {
            TrieNode* ptr = root;
            for (auto ch : d) {
                if (ptr->child[ch - 'a'] == nullptr)
                    ptr->child[ch - 'a'] = new TrieNode();

                ptr = ptr->child[ch - 'a'];
            }
            ptr->isend = true;
        }
    }

    string search(string s) {
        TrieNode* ptr = root;
        if (root->child[s[0] - 'a'] == nullptr)
            return s;
        string ans = "";

        for (int i = 0; i < s.size(); i++) {
            if (ptr->isend)
                return ans;
            if (ptr->child[s[i] - 'a'] == nullptr)
                return s;

            ans += s[i];
            ptr = ptr->child[s[i] - 'a'];
        }
        return ptr->isend ? ans : s;
    }

    string replaceWords(vector<string>& dic, string sen) {
        TrieNode* ptr = root;

        insert(dic);

        string ans = "";
        string s = "";
        for (int i = 0; i < sen.size(); i++) {
            if (sen[i] == ' ') {
                ans += search(s);
                ans += " ";
                s = "";
            } else
                s += sen[i];
        }
        ans += search(s);
        return ans;
    }
};
```

---

# 🔍 Edge Cases Handled

✅ Word has no matching root → returned unchanged

✅ Multiple roots match → shortest one is returned (trie stops at first `isend`)

✅ Last word in sentence (no trailing space) → handled after the loop

✅ Root is the word itself → returned as-is

---

# 🤔 Key Takeaways (For Revision)

## Main Trick

```
Trie gives the SHORTEST prefix automatically —
just stop at the first isend=true encountered during traversal.
```

## Common Mistakes

❌ Not handling the last word (no space after it) → missing from output.

❌ Checking `isend` after moving the pointer instead of before → off-by-one in prefix.

❌ Using `stringstream` vs manual split — both work, manual split used here.

---

## Related Problems

- 208. Implement Trie (Prefix Tree) (prerequisite)
- 211. Design Add and Search Words Data Structure
- 720. Longest Word in Dictionary

---

# 🧠 Revision Notes

## Pattern Recognition

Whenever the question asks:
- Replace words with their shortest prefix/root
- Dictionary-based prefix matching

Think:

```
Trie: insert all roots, walk each word —
stop at first isend for shortest match.
```
