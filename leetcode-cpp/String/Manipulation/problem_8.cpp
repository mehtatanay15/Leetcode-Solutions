// LeetCode 8: String to Integer (atoi)
// Problem: Convert a string to an integer with proper validation and overflow handling
// Approach: String parsing with sign and overflow checks

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        int i = 0, n = s.size();

        // Step 1: Skip leading whitespaces
        while(i < n && s[i] == ' ')
            i++;

        // Step 2: Check for sign
        int sign = 1;
        if(i < n && (s[i] == '+' || s[i] == '-')) {
            if(s[i] == '-') sign = -1;
            i++;
        }

        // Step 3: Read digits and construct the number
        long long num = 0;
        while(i < n && isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');

            // Check for overflow before returning
            if(sign * num <= INT_MIN) return INT_MIN;
            if(sign * num >= INT_MAX) return INT_MAX;

            i++;
        }

        return sign * num;
    }
};

/*
Time Complexity: O(n) - single pass through the string
Space Complexity: O(1) - only using constant extra space

Algorithm:
1. Skip leading whitespaces
2. Read the optional sign (+ or -)
3. Read digits and build the number
4. Check for overflow during construction
5. Return the result with the appropriate sign

Rules:
- Read leading whitespaces
- Read optional sign (+ or -)
- Read non-negative integers until non-digit character
- If no digits found, return 0
- Handle integer overflow (INT_MIN = -2^31, INT_MAX = 2^31 - 1)

Example 1:
Input: s = "42"
Output: 42

Example 2:
Input: s = "   -42"
Output: -42

Explanation:
- Skip 3 spaces
- Read sign: -
- Read digits: 42
- Result: -42

Example 3:
Input: s = "4193 with words"
Output: 4193

Explanation:
- No leading spaces
- No sign
- Read digits: 4193
- Stop at space (non-digit)
- Result: 4193

Example 4:
Input: s = "words and 987"
Output: 0

Explanation:
- No leading spaces
- First character is 'w' (not digit or sign)
- No digits read
- Result: 0

Example 5:
Input: s = "-91283472332"
Output: -2147483648 (INT_MIN)

Explanation:
- Number exceeds INT_MIN limit
- Return INT_MIN
*/
