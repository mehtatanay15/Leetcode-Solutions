// LeetCode 2452: Two Edit Words
// Problem: Find words from queries that can be transformed to a dictionary word with at most 2 edits
// Approach: Character-by-character comparison to count differences

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        int m = queries.size();
        int n = dictionary.size();
        vector<string> ans;

        // For each query word
        for(int i = 0; i < m; i++) {
            // Check against each dictionary word
            for(int j = 0; j < n; j++) {
                int change = 0;
                
                // Count character differences
                for(int k = 0; k < queries[i].length(); k++) {
                    if(queries[i][k] != dictionary[j][k]) {
                        change++;
                    }
                    // Early termination if more than 2 changes needed
                    if(change > 2) break;
                }
                
                // If can be edited with at most 2 changes, add to answer
                if(change <= 2) {
                    ans.push_back(queries[i]);
                    break;  // Found a match for this query, move to next query
                }
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(m * n * L)
- m: number of queries
- n: number of dictionary words
- L: length of words
- Worst case: check each query against all dictionary words

Space Complexity: O(1) excluding the output vector

Algorithm:
1. For each query word:
   a. Check against each dictionary word
   b. Count the number of character differences
   c. If differences <= 2, add query to answer and move to next query
   d. If no dictionary word matches, query is not added to answer
2. Return the result vector

Definition:
- Edit: Change one character to another
- Two edit words: Words that differ in at most 2 positions

Example 1:
Input: queries = ["word","note","ants","wood"], dictionary = ["wood","note","ants"]
Output: ["word","note","ants","wood"]

Explanation:
- "word" → "wood": 1 difference (r→o), ≤ 2 ✓
- "note" → "note": 0 differences, ≤ 2 ✓
- "ants" → "ants": 0 differences, ≤ 2 ✓
- "wood" → "wood": 0 differences, ≤ 2 ✓

Example 2:
Input: queries = ["yes"], dictionary = ["not"]
Output: []

Explanation:
- "yes" → "not": 3 differences (y→n, e→o, s→t), > 2 ✗

Example 3:
Input: queries = ["ab"], dictionary = ["ba"]
Output: ["ab"]

Explanation:
- "ab" → "ba": 2 differences (positions 0 and 1), ≤ 2 ✓

Key Points:
- All words have the same length
- Two edits means at most 2 character changes
- Early termination when change count exceeds 2 saves time
- Once a match is found in dictionary, move to next query
*/
