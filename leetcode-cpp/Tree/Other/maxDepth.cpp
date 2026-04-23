// LeetCode 1614: Maximum Nesting Depth of the Parentheses
// Problem: Find maximum depth of nested parentheses in a valid parentheses string
// Approach: Single Pass Tracking Current Depth

class Solution {
public:
    int maxDepth(string s) {
        int n = s.length();
        int maxi = 0;      // Maximum depth seen so far
        int curr = 0;      // Current depth
        
        for(int i = 0; i < n; i++) {
            if(s[i] == '(') {
                curr++;    // Opening parenthesis increases depth
                maxi = max(curr, maxi);  // Update maximum if needed
            }
            else if(s[i] == ')') {
                curr--;    // Closing parenthesis decreases depth
            }
            // Ignore all other characters (digits, operators, etc.)
        }
        
        return maxi;
    }
};

/*
Time Complexity: O(n)
- Single pass through the string
- O(1) operations at each character

Space Complexity: O(1)
- Only using two integer variables (maxi, curr)

Algorithm (Single Pass Depth Tracking):
1. Initialize: maxi = 0 (max depth), curr = 0 (current depth)
2. For each character in string:
   a. If '(': increment curr, update maxi = max(curr, maxi)
   b. If ')': decrement curr
   c. Ignore all other characters
3. Return maxi

Key Insight:
- Don't need to store parentheses or use stack
- Simply track current depth level
- Maximum depth is the highest level reached
- Simpler than traditional parentheses matching problems

Why Track Maximum:
- We only care about the deepest nesting level
- Not about validity (problem guarantees valid)
- Not about matching specific pairs
- Just the maximum nesting count

Example 1:
Input: s = "(1+(2*3)+((8)/3))"

Traversal:
i=0: '(' → curr=1, maxi=1
i=1: '1' → skip
i=2: '+' → skip
i=3: '(' → curr=2, maxi=2
i=4: '2' → skip
i=5: '*' → skip
i=6: '3' → skip
i=7: ')' → curr=1
i=8: '+' → skip
i=9: '(' → curr=2
i=10: '(' → curr=3, maxi=3
i=11: '8' → skip
i=12: ')' → curr=2
i=13: '/' → skip
i=14: '3' → skip
i=15: ')' → curr=1
i=16: ')' → curr=0

Output: 3

The deepest nesting is "((8)/3)" with depth 3.

Example 2:
Input: s = "(1)+((2))+3)"

Traversal:
i=0: '(' → curr=1, maxi=1
i=1: '1' → skip
i=2: ')' → curr=0
i=3: '+' → skip
i=4: '(' → curr=1
i=5: '(' → curr=2, maxi=2
i=6: '2' → skip
i=7: ')' → curr=1
i=8: ')' → curr=0
i=9: '+' → skip
i=10: '3' → skip

Output: 2

Example 3:
Input: s = "()(()())"

Traversal:
i=0: '(' → curr=1, maxi=1
i=1: ')' → curr=0
i=2: '(' → curr=1
i=3: '(' → curr=2, maxi=2
i=4: ')' → curr=1
i=5: '(' → curr=2
i=6: ')' → curr=1
i=7: ')' → curr=0

Output: 2

Edge Cases:
- No parentheses: maxi=0
- Single pair "()": maxi=1
- Deeply nested "", maxi=n/2
- All opening "": maxi=n (but problem guarantees valid)

Difference from Other Parentheses Problems:
- Problem 20 (Valid Parentheses): determine if valid
  * Need to match opening/closing pairs
  * Use stack to validate matching
  * Return true/false
- This problem: find maximum depth
  * Don't care about matching
  * Only track current level
  * Return maximum level reached

String Contents:
- Contains parentheses: ( )
- Contains digits: 0-9
- Contains operators: +, -, *, /
- Contains spaces (sometimes)
- Problem only cares about parentheses

Optimal Solution:
- This is the optimal approach
- Time: O(n), Space: O(1)
- Can't do better than O(n) since we must read entire string
- No additional space needed
*/