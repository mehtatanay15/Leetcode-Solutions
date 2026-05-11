// LeetCode 2553: Separate the Digits in an Array
// Problem: Given an array of positive integers, separate all digits and return them in a new array
// Example: [123, 45] → [1, 2, 3, 4, 5]
// Approach: Extract digits from each number and append to result

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> ans;

        // Process each number in the input array
        for (int i = 0; i < nums.size(); i++) {
            int n = nums[i];
            vector<int> temp;
            
            // Step 1: Extract all digits from the current number
            // Digits are extracted in reverse order (from rightmost to leftmost)
            while (n != 0) {
                int digit = n % 10;  // Extract rightmost digit
                n = n / 10;           // Remove rightmost digit
                temp.push_back(digit);
            }
            
            // Step 2: Reverse the extracted digits to get correct order
            // Since we extracted from right to left, we need to reverse
            for (int j = temp.size() - 1; j >= 0; j--) {
                ans.push_back(temp[j]);
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n * m) where:
  - n = number of elements in nums array
  - m = average number of digits per element
  - For each element, we extract its digits and reverse them
Space Complexity: O(d) where:
  - d = total number of digits in all numbers
  - Temporary array for digits of single number: O(log(max_num))
  - Output array: O(d)

Algorithm Explanation:

Step 1 - Extract Digits:
1. For each number in the input array:
   - Initialize a temporary vector to store digits
   - While number > 0:
     * Extract rightmost digit using modulo: digit = n % 10
     * Remove rightmost digit using division: n = n / 10
     * Add digit to temporary vector
   - Digits are stored in reverse order (units → tens → hundreds, etc.)

Step 2 - Reverse and Append:
1. Reverse the temporary digit array to get correct order
2. Append all reversed digits to the result array

Why Reverse is Needed:
- Extracting with modulo gives digits from right to left
- Example: 123
  - First extraction: 123 % 10 = 3, then 123 / 10 = 12
  - Second extraction: 12 % 10 = 2, then 12 / 10 = 1
  - Third extraction: 1 % 10 = 1, then 1 / 10 = 0
  - Extracted sequence: [3, 2, 1]
  - After reversing: [1, 2, 3] ✓

Example 1:
nums = [123, 45]

Processing 123:
- Extract: temp = [3, 2, 1]
- Reverse and append: ans = [1, 2, 3]

Processing 45:
- Extract: temp = [5, 4]
- Reverse and append: ans = [1, 2, 3, 5, 4]

Result: [1, 2, 3, 5, 4]

Example 2:
nums = [1, 22, 333]

Processing 1:
- Extract: temp = [1]
- Reverse and append: ans = [1]

Processing 22:
- Extract: temp = [2, 2]
- Reverse and append: ans = [1, 2, 2]

Processing 333:
- Extract: temp = [3, 3, 3]
- Reverse and append: ans = [1, 2, 2, 3, 3, 3]

Result: [1, 2, 2, 3, 3, 3]

Alternative Approach - Using String Conversion:
Could convert each number to string, iterate through characters, and add to result:
```cpp
for (int num : nums) {
    string s = to_string(num);
    for (char c : s) {
        ans.push_back(c - '0');
    }
}
```
This approach:
- Time: O(n * m) - same as modulo approach
- Space: O(m) - for string conversion
- Arguably cleaner but involves string conversion overhead

Number Extraction vs String Approach:
- Modulo approach: Pure arithmetic, no string overhead
- String approach: More readable, leverages built-in functions
- Both have same time complexity

Key Insights:
- Modulo extracts digits from right to left
- Division by 10 removes the rightmost digit
- Reversing after extraction gives correct digit order
- Can also extract into string for potentially cleaner code
- Number of digits in n is floor(log10(n)) + 1

Edge Cases:
- Single digit numbers: temp size = 1, no reversal needed
- Numbers with trailing zeros after extraction: none (leading zeros in result)
- Single number array: works correctly
- Large numbers: works up to integer limits
*/
