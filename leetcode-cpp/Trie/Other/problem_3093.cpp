// LeetCode 3093: Longest Common Suffix Queries (with Trie optimization)
// Problem: For each query string in B, find the index of string in A that:
// 1. Shares the longest common suffix with the query
// 2. Among strings with same suffix length: prefer shorter string
// 3. Among strings with same length: prefer smaller index
// Approach: Reverse Trie built from suffixes, tracking best candidate at each node

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    struct Node {
        // Children pointers for each of 26 letters
        int c[26] = {0};
        // Best string index at this node (best = shortest, then smallest index)
        int b = -1;
    };

public:
    vector<int> stringIndices(vector<string>& A, vector<string>& B) {
        vector<Node> t;
        t.reserve(500005);  // Reserve space for efficiency
        t.push_back(Node()); // Root node at index 0
        
        // Lambda function to update best candidate at a node
        auto ub = [&](int u, int i) {
            if (t[u].b == -1) {
                // First string at this node, set it as best
                t[u].b = i;
            } else {
                // Compare with existing best
                int cb = t[u].b;           // Current best index
                int cl = A[cb].length();   // Current best length
                int nl = A[i].length();    // New candidate length
                
                // Update if:
                // 1. New string is shorter
                if (nl < cl) {
                    t[u].b = i;
                }
                // 2. Same length but new string has smaller index
                else if (nl == cl && i < cb) {
                    t[u].b = i;
                }
            }
        };

        // Build reverse Trie from array A
        for (int i = 0; i < A.size(); ++i) {
            int u = 0;  // Start at root
            
            // Update best at root (handles empty suffix match)
            ub(u, i);
            
            // Traverse string from right to left (building suffix Trie)
            for (int j = A[i].length() - 1; j >= 0; --j) {
                int k = A[i][j] - 'a';  // Convert character to index 0-25
                
                // Create new node if path doesn't exist
                if (t[u].c[k] == 0) {
                    t.push_back(Node());
                    t[u].c[k] = t.size() - 1;
                }
                
                // Move to child node
                u = t[u].c[k];
                
                // Update best candidate at this node
                ub(u, i);
            }
        }

        vector<int> ans;
        ans.reserve(B.size());
        
        // Process each query
        for (const string& q : B) {
            int u = 0;  // Start at root
            
            // Traverse query string from right to left as far as possible
            for (int j = q.length() - 1; j >= 0; --j) {
                int k = q[j] - 'a';
                
                // Stop if path doesn't exist
                if (t[u].c[k] == 0) {
                    break;
                }
                
                // Move to next node
                u = t[u].c[k];
            }
            
            // Add the best string found (could be root if no path matched)
            ans.push_back(t[u].b);
        }

        return ans;
    }
};

/*
Time Complexity: O(N * L + Q * L) where:
  - N = number of strings in A, L = average length
  - Q = number of queries in B, L = average query length
  - Building Trie: O(N * L) - insert each character of each string
  - Processing queries: O(Q * L) - traverse each query as far as possible
  - Total: O((N + Q) * L)

Space Complexity: O(N * L)
  - Trie nodes: at most N * L nodes (one per character)
  - Each node stores 26 pointers and 1 best index
  - O(N * L * 26) = O(N * L)

Algorithm Explanation:

Problem Overview:
Given:
- Array A of strings (candidates)
- Array B of query strings

For each query in B, find which string in A is the "best match":
- Best match = longest common suffix
- Tiebreaker 1: prefer shortest string
- Tiebreaker 2: prefer smallest index

Why Reverse Trie (Suffix Trie):
- We're finding common SUFFIXES, not prefixes
- Building Trie from right to left (suffix direction)
- Allows efficient suffix matching by traversing backwards
- Query also traversed backwards to find longest suffix match

Key Insight - Best Candidate Tracking:
- Store best string index at EACH node
- Best = shortest length, or smallest index if tied
- When traversing, the node we reach has already computed the best for that suffix
- No need to search further; we already have the optimal answer

Example 1: A = ["abc", "ab", "a"], B = ["abb", "ba"]

Building Trie (processing backwards):
- Insert A[0]="abc": root → 'c' (node 1, best=0) → 'b' (node 2, best=0) → 'a' (node 3, best=0)
- Insert A[1]="ab": 
  - root → 'b' (node 4, best=1 since len(ab)=2 < len(abc)=3) 
  - → 'a' (node 5, best=1)
- Insert A[2]="a":
  - root → 'a' (node 6, best=2 since len(a)=1 < len(ab)=2)

Trie structure (suffixes read backwards):
```
root (best=2, "a" is shortest)
├─ 'a' → node 6 (best=2, "a")
│        └─ 'b' → node 5 (best=1, "ab")
│                 └─ 'c' → node 3 (best=0, "abc")
├─ 'b' → node 4 (best=1, "ab")
│        └─ 'a' → (same as node 5)
└─ 'c' → node 1 (best=0, "abc")
         └─ 'a' → (same as node 3)
         └─ 'b' → (same as node 2)
```

Query B[0]="abb" (backwards: 'b','b','a'):
- Start: u=0
- j=2 (q[2]='b'): t[0].c['b']=4, u=4 (suffix "b", best=1)
- j=1 (q[1]='b'): t[4].c['b']=0 (no 'b' under node 4), break
- Answer: t[4].b=1 (index of "ab")

Why "ab"? Both "ab" and "b" end with "b", but:
- "ab" has suffix match "b" (last char matches)
- But we only go one level deep (can't match 'b' twice)
- So best at node 4 is "ab" (length 2)
- Compare to "abc" (length 3): "ab" is shorter ✓

Query B[1]="ba" (backwards: 'a','b'):
- Start: u=0
- j=1 (q[1]='a'): t[0].c['a']=6, u=6 (suffix "a", best=2)
- j=0 (q[0]='b'): t[6].c['b']=0 (no 'b' under node 6), break
- Answer: t[6].b=2 (index of "a")

Why "a"? Query "ba" has suffix "a". All strings end with something:
- "a" ends with 'a' (perfect suffix match)
- "ab" ends with 'b'
- "abc" ends with 'c'
- So "a" with suffix "a" is best (it's shortest) ✓

Example 2: A = ["hello", "world", "hi"], B = ["world", "world"]

Building Trie (backwards):
- "hello": o → l → l → e → h
- "world": d → l → r → o → w
- "hi": i → h

When inserting:
- Root (best = "hi" since len=2, shortest)
- After each string, update best at each node

Query "world" (backwards: d,l,r,o,w):
- u=0, d matched, move to node for 'd' suffix
- 'd' exists (from "world")
- Continue matching: l, r, o, w
- Reach node representing full "world" suffix
- Return best at that node: "world" itself ✓

Edge Cases Handled:

1. Empty query: If B[i] = "", then:
   - Loop j from -1 to 0 doesn't execute
   - u stays at root
   - Return t[0].b = best overall shortest string ✓

2. Very long query: If query longer than all A strings:
   - We traverse as far as Trie exists
   - When character not found, break
   - Return best at reached node ✓

3. All different lengths: Best preference is correct:
   - Shorter strings preferred
   - Among same length, smaller index preferred ✓

4. Query not matching any suffix: All strings in A should match at root at least
   - Return best at root (shortest overall string) ✓

Algorithm Visualization:

Query matching process:
```
Query: "abb"
String: "ab"
Suffix check: does "ab" end with some suffix of "abb"?

Reverse matching:
'b' (position 2 of query) vs 'b' (position 1 of "ab") ✓
'b' (position 1 of query) vs 'a' (position 0 of "ab") ✗

Stop: matched 1 character
Found best: "ab" ✓
```

Why Reverse Order Works:
- Suffixes are best compared from end to start
- Common suffix of two strings = longest matching tail
- Reversing allows Trie to work naturally (Trie works left-to-right on reversed strings)
- Same as converting suffix problem to prefix problem

Performance Optimizations:

1. Reserve space: `t.reserve(500005)` prevents reallocation
2. Lambda function: captures reference to allow Trie access
3. Early termination: break when character not found in Trie
4. Single pass: both construction and queries are linear

Why Not Use String Comparison:
- Naive: compare each query with each string = O(Q * N * L) with string comparison
- Trie: O((N + Q) * L) by grouping strings with common suffixes
- Trie is exponentially faster for multiple queries

Alternative Approach (Suffix Array):
- Build suffix array with lengths
- For each query, binary search suffix array
- Time: O(N*L*log(N*L) + Q*L*log(N*L)) - slower than Trie

Why Trie is Best:
- Perfect for multiple suffix queries
- Best candidates already computed at each node
- No redundant comparisons
- Space-efficient for grouped suffixes

Common Mistakes to Avoid:
1. Not reversing strings (trying prefix matching instead of suffix)
2. Forgetting to create new nodes in Trie
3. Not updating best at every node during insertion
4. Breaking on first mismatch (correct, but easy to overlook)
5. Not handling empty query case
6. Wrong tiebreaker logic (length first, then index)

Memory Consideration:
- Reserve 500005 nodes for 50000 strings of avg length 10
- Each node: 26 ints (104 bytes) + 1 int (4 bytes) = 108 bytes
- Total: 500005 * 108 ≈ 54 MB (within typical memory limits)

Why This Problem is Hard:
- Requires understanding both Trie structure and suffix concepts
- Reverse Trie is less intuitive than standard Trie
- Multiple tiebreaking criteria
- Efficient tracking of best candidate at each node
- Test case design typically includes edge cases
*/
