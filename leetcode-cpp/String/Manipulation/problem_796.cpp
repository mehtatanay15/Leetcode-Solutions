// LeetCode 796: Rotate String
// Problem: Given two strings s and goal, determine if s can be rotated to equal goal
// A rotation moves the first character to the end: "abcd" → "bcda" → "cdab" → "dabc" → "abcd"
// Approach: String rotation via cyclic shift and comparison

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool rotateString(string s, string goal) {
        // Quick length check: rotation preserves length
        if (s.length() != goal.length()) {
            return false;
        }
        
        int n = s.length();
        
        // Try each possible rotation
        for (int i = 0; i < n; i++) {
            if (s == goal) {
                return true;
            }
            
            // Rotate left by 1: move first character to end
            // s = "abcd" → "bcda"
            char first = s[0];
            s = s.substr(1) + first;
        }
        
        return false;
    }
};

/*
Time Complexity: O(n²) - n rotations, each rotation and comparison takes O(n)
  - substr() + concatenation: O(n)
  - string comparison: O(n)
  - Total: n iterations × O(n) per iteration = O(n²)
Space Complexity: O(n) - creating substring and rotated string

Algorithm:
1. Check if lengths are equal (necessary condition for any rotation)
2. For each rotation k from 0 to n-1:
   - Compare current s with goal
   - If match found, return true
   - Rotate s left by 1: move first character to end
3. Return false if no rotation matches

Rotation Pattern:
Original: s = "abcd"
k=0: "abcd" (compare with goal)
k=1: "bcda" (move 'a' to end)
k=2: "cdab" (move 'b' to end)
k=3: "dabc" (move 'c' to end)
k=4: "abcd" (full cycle, back to original)

Key Insight:
- If goal is a rotation of s, then goal will appear as a substring in s+s
- More efficient alternative: if s and goal have same length and goal is in s+s, 
  then goal is a rotation of s (KMP or string find could make this O(n))

Example 1:
s = "abcd", goal = "cdab"
- k=0: "abcd" ≠ "cdab"
- k=1: "bcda" ≠ "cdab"
- k=2: "cdab" = "cdab" ✓ return true

Example 2:
s = "abcd", goal = "acbd"
- k=0: "abcd" ≠ "acbd"
- k=1: "bcda" ≠ "acbd"
- k=2: "cdab" ≠ "acbd"
- k=3: "dabc" ≠ "acbd"
- return false (no rotation matches)

Optimization Note:
- Could use (s+s).find(goal) for O(n) solution using KMP
- Current solution is straightforward but less efficient for large strings
*/
