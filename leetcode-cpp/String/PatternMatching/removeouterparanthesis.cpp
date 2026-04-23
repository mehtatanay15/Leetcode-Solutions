// LeetCode 1021: Remove Outermost Parentheses
// Problem: Remove outermost parentheses from each primitive valid parentheses string
// Approach: Count depth, skip outer parentheses

class Solution {
public:
    string removeOuterParentheses(string s) {
        string result = "";  // Result string
        int n = s.length();
        int c = 0;           // Depth counter (balance of parentheses)
        
        for(int i = 0; i < n; i++)
        {
            if(s[i] == '(')
            {
                // Add opening paren only if it's not the outermost
                // (outermost has c=0 before adding)
                if(c > 0)
                {
                    result += s[i];
                }
                c++;  // Increase depth
            }
            else  // s[i] == ')'
            {
                c--;  // Decrease depth first
                // Add closing paren only if it's not the outermost
                // (outermost has c=0 after decreasing)
                if(c > 0)
                {
                    result += s[i];
                }
            }
        }
        return result;
    }
};

/*
Time Complexity: O(n)
- Single pass through string
- n: length of input string

Space Complexity: O(n)
- Result string can be up to n characters
- In worst case (single group), result size is n-2

Algorithm (Depth Tracking with Balance):
1. Use counter 'c' to track balance (depth of nesting)
2. For each character:
   a. If '(' and c > 0: add to result (not outermost), increment c
   b. If '(' and c = 0: skip (outermost), increment c
   c. If ')': decrement c, then add if c > 0 (not outermost)
3. Return result

Key Insight - Primitive Valid Parentheses String:
- Input contains multiple primitive groups
- Each group is completely independent
- Outermost parentheses marked by c=0 at start and after end
- Only include chars with c > 0 (inner parentheses)

Definition - Primitive Valid String:
- Cannot be split into two non-empty valid strings
- Outermost '(' matches with outermost ')'
- Everything inside is the primitive core

Example 1:
Input: s = "(()())(())"

Group 1: "(()())"  -> remove outer -> "()()"
Group 2: "(())"    -> remove outer -> "()"
Output: "()()()"  (concat all primitives)

Detailed trace of "(()())":
i=0, s[0]='(', c=0: skip, c=1
i=1, s[1]='(', c=1: add '(', c=2
i=2, s[2]=')', c=2: c=1, add ')', c=1
i=3, s[3]='(', c=1: add '(', c=2
i=4, s[4]=')', c=2: c=1, add ')', c=1
i=5, s[5]=')', c=1: c=0, skip (outermost)

Result: "()()" ✓

Example 2:
Input: s = "()(())"

Group 1: "()"     -> remove outer -> ""
Group 2: "(())"   -> remove outer -> "()"
Output: "()"      (concat: "" + "()")

Trace:
i=0, '(', c=0: skip, c=1
i=1, ')', c=1: c=0, skip
i=2, '(', c=0: skip, c=1
i=3, '(', c=1: add '(', c=2
i=4, ')', c=2: c=1, add ')', c=1
i=5, ')', c=1: c=0, skip

Result: "()" ✓

Example 3:
Input: s = "()()"

Group 1: "()"    -> ""
Group 2: "()"    -> ""
Output: ""       (both primitive, no inner content)

Trace:
i=0, '(', c=0: skip, c=1
i=1, ')', c=1: c=0, skip
i=2, '(', c=0: skip, c=1
i=3, ')', c=1: c=0, skip

Result: "" ✓

Edge Cases:
- Single pair "()": return ""
- Nested "(())": return "()"
- Multiple groups "()()()":
  Each "()" becomes "" when outer removed
  Result empty
- Deeply nested "(((())))":
  Outermost pair removed
  Inner content: "(())" -> remove its outer -> "()"
  Continue recursively

Balance Counter Concept:
- 'c' represents nesting depth
- c=0: at root level, next char is outermost
- c>0: inside primitive group, include char
- When c returns to 0, one primitive group complete

Why This Works:
- Parentheses validity guaranteed by problem
- Every group starts with c=0 and opening '('
- Every group ends with closing ')' and c returns to 0
- Only include chars where c > 0 (inner content)

Visual - Balance Counter:
"(()())(())"
 ^ ^          group 1
      ^ ^^    group 2

Counter values:
 ( ( ) ( ) ) ( ( ) )
0 1 2 1 2 1 0 1 2 1 0
         ^
    Include when counter > 0
    Skip when counter = 0 (outermost)

Alternative Approach - Stack:

string removeOuterParentheses(string s) {
    string result = "";
    stack<char> st;
    for(char c : s) {
        if(c == '(') {
            if(!st.empty()) result += c;
            st.push(c);
        } else {
            st.pop();
            if(!st.empty()) result += c;
        }
    }
    return result;
}

Stack vs Counter:
- Stack: explicit data structure, more intuitive
- Counter: simpler, just need depth
- Both O(n) time, but counter uses O(1) extra space
- Counter approach is preferred (space-efficient)

Application Pattern:
- Balance/nesting tracking
- Parentheses matching
- Valid bracket sequences
- Removing outer structures

Why Order Matters (Check Before Adding):
- Opening: check if c > 0 BEFORE incrementing
  * At start of group, c=0, should skip
- Closing: decrement FIRST, then check if c > 0
  * At end of group, after decrement c becomes 0, should skip
- This ensures outermost pair not included
*/
