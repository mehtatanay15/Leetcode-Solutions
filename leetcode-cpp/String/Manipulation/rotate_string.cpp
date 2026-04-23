// LeetCode 796: Rotate String
// Problem: Check if goal is a rotation of string s
// Approach: Simulate rotations (rotate s and check each rotation)

class Solution {
public:
    bool rotateString(string s, string goal) {
        bool ans = false;
        int n = s.length();
        
        // If lengths don't match, goal can't be rotation of s
        if(s.length() != goal.length()) return false;

        // Try all n possible rotations
        for(int i = 0; i < n; i++) {
            if(s == goal) {
                ans = true;
                break;  // Found, no need to continue
            }
            
            // Rotate: move first character to end
            char first = s[0];
            s = s.substr(1) + first;
        }

        return ans;
    }
};

/*
Time Complexity: O(n^2)
- n rotations
- Each rotation creates new string: O(n)
- Each string comparison: O(n)
- Total: O(n) * O(n) = O(n^2)

Space Complexity: O(n)
- String s is modified in-place (but creates new strings internally)
- substr and concatenation create O(n) space

Algorithm (Simulation):
1. Check if lengths match (necessary condition)
2. For each of n possible rotations:
   a. Check if current s equals goal
   b. If yes, return true
   c. Rotate s: move first character to end
3. If none match after n rotations, return false

How Rotation Works:
- s = "abcd"
- Rotation 1: "bcda" (move 'a' to end)
- Rotation 2: "cdab" (move 'b' to end)
- Rotation 3: "dabc" (move 'c' to end)
- Rotation 4: "abcd" (move 'd' to end, back to original)

Example 1:
Input: s = "abcd", goal = "cdab"

Rotation 0: s="abcd" != goal="cdab"
Rotation 1: s="bcda" != goal="cdab"
Rotation 2: s="cdab" == goal="cdab" ✓

Output: true

Example 2:
Input: s = "abcd", goal = "acbd"

Rotation 0: s="abcd" != goal="acbd"
Rotation 1: s="bcda" != goal="acbd"
Rotation 2: s="cdab" != goal="acbd"
Rotation 3: s="dabc" != goal="acbd"

Output: false (acbd is not a rotation of abcd)

Edge Cases:
- Different lengths: return false immediately
- Single character: s==goal or false
- Same string: return true (rotation by 0)
- All same characters: always true if same length

Optimization - Clever Trick:
- If goal is a rotation of s, then goal appears in s+s
- Example: s="abcd", s+s="abcdabcd"
- Rotations are substrings of s+s:
  * "abcd", "bcda", "cdab", "dabc" all in "abcdabcd"
- Check: goal in (s+s) if same length

Comparison with Optimized Approach:
- This approach: O(n^2)
- Optimized (find in s+s): O(n) with efficient string search
- For competitive programming, consider optimized version

String Methods Used:
- s.substr(1): substring from index 1 to end
- str1 + str2: string concatenation
- s == goal: string comparison
- s.length(): get length

Why Simulation Works:
- Every possible rotation is generated
- Checking all rotations guarantees finding answer
- Simple to understand and implement
- Acceptable time for small strings

Optimized Solution (O(n)):
return s.length() == goal.length() && (s+s).find(goal) != string::npos;
- Uses find() which is O(n) with efficient algorithm
- Much better for large strings
*/
    }
};