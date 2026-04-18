// LeetCode 3783: Mirror Distance
// Problem: Find the absolute difference between a number and its mirror (reverse)
// Approach: Number Reversal + Absolute Difference

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mirrorDistance(int n) {
        int rev = 0;
        int temp = n;

        // Reverse the number
        while(n != 0) {
            int digit = n % 10;
            rev = rev * 10 + digit;
            n = n / 10;
        }

        // Return absolute difference between reversed and original
        return abs(rev - temp);
    }
};

/*
Time Complexity: O(d) where d is the number of digits in n
- We iterate through each digit of the number

Space Complexity: O(1) - only using constant extra space

Algorithm:
1. Store the original number in temp
2. Extract digits from n one by one (using % 10)
3. Build the reversed number by appending digits (rev = rev * 10 + digit)
4. Calculate absolute difference between reversed and original
5. Return the difference

Example 1:
Input: n = 123
Output: 198

Explanation:
- Original: 123
- Reversed: 321
- Difference: |321 - 123| = 198

Example 2:
Input: n = 100
Output: 99

Explanation:
- Original: 100
- Reversed: 001 = 1
- Difference: |1 - 100| = 99

Example 3:
Input: n = 505
Output: 0

Explanation:
- Original: 505
- Reversed: 505
- Difference: |505 - 505| = 0

Example 4:
Input: n = 42
Output: 15

Explanation:
- Original: 42
- Reversed: 24
- Difference: |24 - 42| = 18

Note:
- Palindromic numbers (like 121, 555) will have mirror distance of 0
- Single digit numbers will have mirror distance of 0
- The mirror distance measures how different a number is from its digit-reversed version
*/
