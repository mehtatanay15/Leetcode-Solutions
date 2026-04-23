// LeetCode 5: Longest Palindromic Substring
// Problem: Find the longest palindromic substring in a given string
// Approach: Expand Around Center (check each position as center)

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        int start = 0;
        int maxLen = 0;

        // Check each position as potential center of palindrome
        for(int i = 0; i < n; i++) {
            // Case 1: Odd length palindrome (single character center)
            int l = i, r = i;
            while(l >= 0 && r < n && s[l] == s[r]) {
                if(r - l + 1 > maxLen) {
                    start = l;
                    maxLen = r - l + 1;
                }
                l--;
                r++;
            }

            // Case 2: Even length palindrome (two character center)
            l = i;
            r = i + 1;
            while(l >= 0 && r < n && s[l] == s[r]) {
                if(r - l + 1 > maxLen) {
                    start = l;
                    maxLen = r - l + 1;
                }
                l--;
                r++;
            }
        }

        return s.substr(start, maxLen);
    }
};

/*
Time Complexity: O(n^2)
- For each of n positions, expand around center: O(n)
- Total: O(n) positions × O(n) expansion = O(n^2)

Space Complexity: O(1)
- Only using pointers (l, r, start, maxLen)
- Output string doesn't count as extra space

Algorithm (Expand Around Center):
1. For each position i in string (as potential center):
   a. Check odd-length palindromes (center = single char at i)
      - Expand left and right simultaneously
      - Stop when chars don't match or boundary reached
      - Update maxLen if found longer palindrome
   b. Check even-length palindromes (center = between i and i+1)
      - Expand left and right simultaneously
      - Stop when chars don't match or boundary reached
      - Update maxLen if found longer palindrome
2. Return substring from start with length maxLen

Key Insight:
- Every palindrome has a center
- Odd-length palindromes have single character center
- Even-length palindromes have two character center
- By checking all centers, we find all palindromes
- No need to check all substrings (O(n^3) with DP would work too)

Why Both Odd and Even:
- "aba" is odd-length (center = 'b')
- "abba" is even-length (center = between two 'b's)
- A string may have multiple palindromic substrings
- We need to check both types to find the longest

Example:
Input: "babad"

i=0 (center='b'):
- Odd: s[0]='b', length=1, start=0, maxLen=1
- Even: s[0:1]="ba", not palindrome

i=1 (center='a'):
- Odd: expand from 'a'
  - s[0:2]="ba", not palindrome
  - Start over: s[1]='a', length=1 (no update, maxLen still 1)
- Even: s[1:2]="ab", not palindrome

i=2 (center='b'):
- Odd: expand from 'b'
  - s[2]='b', length=1
  - s[1:3]="ab", not palindrome
- Even: s[2:3]="ba", not palindrome

i=3 (center='a'):
- Odd: expand from 'a'
  - s[3]='a', length=1
  - s[2:4]="ba", not palindrome
- Even: s[3:4]="ad", not palindrome

i=4 (center='d'):
- Odd: s[4]='d', length=1
- Even: out of bounds

Actually let me trace "babad" properly:

i=0 ('b'):
- Odd: l=0, r=0: s[0]='b'=='b' ✓ → len=1, start=0, maxLen=1
       l=-1: stop
- Even: l=0, r=1: s[0]='b'≠s[1]='a' ✗

i=1 ('a'):
- Odd: l=1, r=1: s[1]='a'=='a' ✓ → len=1
       l=0, r=2: s[0]='b'≠s[2]='b' ✗
- Even: l=1, r=2: s[1]='a'≠s[2]='b' ✗

i=2 ('b'):
- Odd: l=2, r=2: s[2]='b'=='b' ✓ → len=1
       l=1, r=3: s[1]='a'==s[3]='a' ✓ → len=3, start=1, maxLen=3
       l=0, r=4: s[0]='b'!=s[4]='d' ✗
- Even: l=2, r=3: s[2]='b'≠s[3]='a' ✗

i=3 ('a'):
- Odd: l=3, r=3: s[3]='a'=='a' ✓ → len=1
       l=2, r=4: s[2]='b'≠s[4]='d' ✗
- Even: l=3, r=4: s[3]='a'≠s[4]='d' ✗

i=4 ('d'):
- Odd: l=4, r=4: s[4]='d'=='d' ✓ → len=1
       l=3, r=5: r >= n, stop
- Even: l=4, r=5: r >= n, stop

Result: start=1, maxLen=3 → s.substr(1, 3) = "bab"
Output: "bab" (also "aba" is valid, both length 3)

Another Example:
Input: "ac"

i=0 ('a'):
- Odd: s[0]='a', len=1, maxLen=1
- Even: s[0]='a'≠s[1]='c' ✗

i=1 ('c'):
- Odd: s[1]='c', len=1 (no update)
- Even: out of bounds

Output: "a"

Edge Cases:
- Single character: always palindrome (length 1)
- All same characters: entire string is palindrome
- No palindromes longer than 1: return any single character
- Empty string: handled by returning empty

Advantages:
- Simple to understand and implement
- O(n^2) is acceptable for most constraints
- No extra space needed

Alternative Approaches:
- DP (O(n^2) time, O(n^2) space): create table of all palindromes
- Manacher's Algorithm (O(n) time): more complex, uses preprocessing
- Brute Force (O(n^3)): check all substrings
*/