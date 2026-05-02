// LeetCode 788: Rotated Digits
// Problem: Count how many numbers in range [1, n] have the property that
// the number is different from its rotated version and the rotated version is also valid
// Valid rotations: 0→0, 1→1, 2→5, 5→2, 6→9, 8→8, 9→6
// Invalid digits that can't be rotated: 3, 4, 7
// Approach: Digit validation - Check each number for valid rotatable digits

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rotatedDigits(int n) {
        int ans = 0;
        
        // Check each number from 1 to n
        for (int i = 1; i <= n; i++) {
            if (isRotated(i)) {
                ans++;
            }
        }
        return ans;
    }

private:
    bool isRotated(int num) {
        bool hasRotated = false;  // Must have at least one digit that changes
        int temp = num;
        
        // Check each digit
        while (temp != 0) {
            int digit = temp % 10;
            temp /= 10;

            // Invalid digits: 3, 4, 7 cannot be rotated
            if (digit == 3 || digit == 4 || digit == 7) {
                return false;
            }

            // Digits that change when rotated: 2, 5, 6, 9
            if (digit == 2 || digit == 5 || digit == 6 || digit == 9) {
                hasRotated = true;
            }
            // Digits that don't change: 0, 1, 8 (valid but don't count as "rotated")
        }
        
        // Valid only if has at least one digit that changes
        return hasRotated;
    }
};

/*
Time Complexity: O(n * log n) - For each number from 1 to n, check its digits
  - log n is average number of digits in numbers up to n
Space Complexity: O(1) - Only using constant extra space

Algorithm:
1. For each number i from 1 to n:
   - Extract each digit
   - Check if digit is invalid (3, 4, 7) → return false
   - Check if digit changes when rotated (2, 5, 6, 9) → mark as rotated
   - Valid digits that don't change (0, 1, 8) → continue
   - If all digits are valid and at least one changes → increment count
2. Return total count

Valid Rotations:
- 0 rotates to 0 (same)
- 1 rotates to 1 (same)
- 2 rotates to 5 (different)
- 5 rotates to 2 (different)
- 6 rotates to 9 (different)
- 8 rotates to 8 (same)
- 9 rotates to 6 (different)

Invalid rotations:
- 3, 4, 7 cannot be rotated to valid digits

Key Insight:
- A number is valid ONLY if:
  1. ALL its digits are from {0, 1, 2, 5, 6, 8, 9}
  2. At least ONE digit is from {2, 5, 6, 9} (must be different from original)
- The "different" requirement ensures rotated number ≠ original number

Example:
n = 10

Numbers 1-10:
1: digits={1} → no rotating digit → NOT valid
2: digits={2} → has rotating digit, no invalid → VALID ✓
3: digits={3} → invalid digit → NOT valid
4: digits={4} → invalid digit → NOT valid
5: digits={5} → has rotating digit, no invalid → VALID ✓
6: digits={6} → has rotating digit, no invalid → VALID ✓
7: digits={7} → invalid digit → NOT valid
8: digits={8} → no rotating digit → NOT valid
9: digits={9} → has rotating digit, no invalid → VALID ✓
10: digits={1,0} → no rotating digit → NOT valid

Answer: 4 (numbers: 2, 5, 6, 9)
*/
