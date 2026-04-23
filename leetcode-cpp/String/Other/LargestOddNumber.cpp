// LeetCode 1903: Largest Odd Number in String
// Problem: Find largest odd number that can be formed by a substring
// Approach: Find rightmost odd digit and return substring up to it

class Solution {
public:
    string largestOddNumber(string num) {
        // Scan from right to left to find rightmost odd digit
        for(int i = num.length() - 1; i >= 0; i--) {
            // Check if digit is odd: '1', '3', '5', '7', '9'
            if((num[i] - '0') % 2 != 0) {
                // Found rightmost odd digit
                // Return substring from start to this position (inclusive)
                return num.substr(0, i + 1);
            }
        }
        
        // No odd digit found (all digits are even)
        return "";
    }
};

/*
Time Complexity: O(n)
- Worst case: scan entire string from right to left
- n: length of the number string

Space Complexity: O(n)
- substr() creates a new string of length i+1
- Output string takes O(n) space

Algorithm (Find Rightmost Odd Digit):
1. Start from rightmost character (index n-1)
2. Move leftward through digits
3. When odd digit found:
   - Return substring from index 0 to i (inclusive)
   - This is the largest odd number
4. If no odd digit exists, return empty string

Key Insight - Why Rightmost Odd Works:
- A number is odd if its last digit is odd
- Removing even trailing digits never changes oddness
- The rightmost odd digit marks the largest odd number
- Everything to the right of it must be removed
- Everything to the left should be kept (larger number)

Example 1:
Input: num = "52"

i=1: num[1]='2', (2-'0')%2=0 (even), continue
i=0: num[0]='5', (5-'0')%2=1 (odd), return num.substr(0, 1)="5"

Output: "5" (5 is odd, 52 is even, largest odd is 5)

Example 2:
Input: num = "4206"

i=3: '6' is even
i=2: '0' is even
i=1: '2' is even
i=0: '4' is even
Loop ends without finding odd digit

Return ""

Output: "" (all digits even, no odd number possible)

Example 3:
Input: num = "35427"

i=4: '7' is odd, return num.substr(0, 5)="35427"

Output: "35427" (whole number is odd since ends with 7)

Example 4:
Input: num = "2468"

Scan: 8(even), 6(even), 4(even), 2(even)
No odd digit found

Return ""

Output: "" (even number, no odd substring ending here)

Example 5:
Input: num = "246897"

i=5: '7' is odd, return num.substr(0, 6)="246897"

Output: "246897"

Example 6:
Input: num = "24689"

i=4: '9' is odd, return num.substr(0, 5)="24689"

Output: "24689"

Why Remove Trailing Evens:
- 135 (ends with 5 - odd) is odd
- 1350 (ends with 0 - even) is even
- 13502 (ends with 2 - even) is even
- To make 1350X odd, the rightmost digit must be odd
- The largest substring ending with odd is from start to rightmost odd

Why Not Keep Everything:
- Can't keep even digits after odd digit
- They would make the final number even
- Example: "1357" is odd
- But "13578" is even (can't use both 7 and 8)

Edge Cases:
- Single digit odd: return that digit
- Single digit even: return empty
- All odd digits: return entire string
- All even digits: return empty
- Mix: return prefix up to rightmost odd

String Method - substr():
- substr(pos): substring from pos to end
- substr(pos, len): substring of length len starting at pos
- Here: substr(0, i+1) means from start, length i+1
- Returns num[0]...num[i]

Character to Digit Conversion:
- (num[i] - '0'): converts '0' to 0, '1' to 1, ..., '9' to 9
- Odd: 1, 3, 5, 7, 9
- Even: 0, 2, 4, 6, 8
- num[i] % 2 != 0 checks if odd

Optimality:
- Cannot do better than O(n) (must read string)
- But early termination possible if odd found early
- Best case: O(1) if last digit is odd
- Worst case: O(n) if no odd digit

Comparison - Left to Right:
If we scanned left to right and found first odd:
- Wrong approach
- Example: "1234567"
- First odd: '1'
- Would return "1"
- But correct answer: "1234567" (largest odd)

So rightmost approach is crucial
*/
