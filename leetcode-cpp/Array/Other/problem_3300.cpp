// LeetCode 3300: Minimum Element After Replacement With Digit Sum
// Problem: For each element in array, replace it with the sum of its digits
// Return the minimum value after replacement
// Approach: Calculate digit sum for each element, track minimum

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minElement(vector<int>& nums) {
        int min_element = INT_MAX;
        
        for (int num : nums) {
            int current_sum = 0;
            
            // Calculate digit sum for current number
            while (num > 0) {
                current_sum += num % 10;  // Add last digit
                num /= 10;                 // Remove last digit
            }
            
            // Update minimum
            min_element = min(min_element, current_sum);
        }
        
        return min_element;
    }
};

/*
Time Complexity: O(n * d) where:
  - n = number of elements in array
  - d = average number of digits per element
  - For each element, we extract digits in O(d) time
  - Digit extraction: O(log10(num)) = O(d)
  - Overall: O(n * log10(max_value))

Space Complexity: O(1)
  - Only using constant extra space for variables
  - No additional data structures needed

Algorithm Explanation:

Problem Overview:
Given an array of positive integers, replace each element with the sum of its digits,
then return the minimum value in the transformed array.

Example: [10, 12, 13, 14]
- 10 → 1+0 = 1
- 12 → 1+2 = 3
- 13 → 1+3 = 4
- 14 → 1+4 = 5
Result: min(1, 3, 4, 5) = 1

Key Insight - Digit Extraction:
To extract digits from a number, repeatedly:
1. Get last digit: num % 10
2. Remove last digit: num / 10
3. Accumulate the sum

Example: Digit sum of 12345
- 12345 % 10 = 5, sum = 5, num = 1234
- 1234 % 10 = 4, sum = 9, num = 123
- 123 % 10 = 3, sum = 12, num = 12
- 12 % 10 = 2, sum = 14, num = 1
- 1 % 10 = 1, sum = 15, num = 0
Result: 15 ✓

Why This Works:
- Modulo 10 gives us the last digit in decimal representation
- Division by 10 removes the last digit
- Combined with loop, extracts all digits left to right
- Sum accumulates all digits

Single Pass Optimization:
- Calculate digit sum and track minimum in one pass
- No need to store all digit sums
- Update min as we go: O(1) extra space

Example 1: nums = [10, 12, 13, 14]

Processing:
- i=0, num=10: digits 1,0 → sum=1, min=1
- i=1, num=12: digits 1,2 → sum=3, min=1
- i=2, num=13: digits 1,3 → sum=4, min=1
- i=3, num=14: digits 1,4 → sum=5, min=1

Result: 1

Verification:
- Array after replacement: [1, 3, 4, 5]
- Minimum: 1 ✓

Example 2: nums = [1, 2, 3, 4, 5]

Processing:
- i=0, num=1: digits [1] → sum=1, min=1
- i=1, num=2: digits [2] → sum=2, min=1
- i=2, num=3: digits [3] → sum=3, min=1
- i=3, num=4: digits [4] → sum=4, min=1
- i=4, num=5: digits [5] → sum=5, min=1

Result: 1

Explanation:
- All single-digit numbers have digit sum equal to themselves
- Minimum of 1-5 is 1

Example 3: nums = [999, 888, 777]

Processing:
- i=0, num=999: 9+9+9 = 27, min=27
- i=1, num=888: 8+8+8 = 24, min=24
- i=2, num=777: 7+7+7 = 21, min=21

Result: 21

Calculation verification for 999:
- 999 % 10 = 9, sum = 9
- 99 % 10 = 9, sum = 18
- 9 % 10 = 9, sum = 27
- 0 % 10 = 0, loop ends
- Result: 27 ✓

Example 4: nums = [100, 200, 300]

Processing:
- i=0, num=100: 1+0+0 = 1, min=1
- i=1, num=200: 2+0+0 = 2, min=1
- i=2, num=300: 3+0+0 = 3, min=1

Result: 1

Key observation: Zeros in number don't contribute to digit sum

Example 5: nums = [9, 99, 999, 9999]

Processing:
- i=0, num=9: sum = 9, min=9
- i=1, num=99: sum = 18, min=9
- i=2, num=999: sum = 27, min=9
- i=3, num=9999: sum = 36, min=9

Result: 9

Pattern: Digit sum increases with more digits (if digit is 9)
- Single 9: 9
- Two 9s: 18
- Three 9s: 27
- Four 9s: 36

Edge Cases Handled:

1. Single element array [5]:
   - num=5: sum=5, min=5
   - Result: 5 ✓

2. All same digits [111, 111, 111]:
   - Each: 1+1+1 = 3
   - min=3 ✓

3. Large numbers [1000000, 10]:
   - 1000000: 1+0+0+0+0+0+0 = 1
   - 10: 1+0 = 1
   - min=1 ✓

4. Mix of large and small [12345, 1]:
   - 12345: 1+2+3+4+5 = 15
   - 1: 1
   - min=1 ✓

5. Leading zeros not relevant (numbers don't have leading zeros in integer representation)
   - 100: extracted as 1,0,0 (not 001)

Algorithm Complexity Analysis:

Time Complexity: O(n * d)
- Outer loop: n iterations (for each element)
- Inner loop: d iterations (where d = number of digits)
- For number x, digits = floor(log10(x)) + 1
- Maximum digits in 32-bit int: 10 (for 2^31-1 ≈ 2.1*10^9)
- Maximum digits in 64-bit int: 19
- So d is O(log max_value)
- Overall: O(n * log max_value)

Space Complexity: O(1)
- Only using:
  - min_element: one integer
  - num: one integer (modified in loop)
  - current_sum: one integer
- No dynamic allocation or recursion
- Constant space regardless of input size

Why Digit Extraction Works:
- In decimal system, each digit represents a power of 10
- 12345 = 1*10^4 + 2*10^3 + 3*10^2 + 4*10^1 + 5*10^0
- num % 10 extracts the 10^0 component
- num / 10 shifts all digits right by one position
- Repeating gives us all digits from right to left

Alternative Approach - String Conversion:
```cpp
int digitSum(int num) {
    int sum = 0;
    string s = to_string(num);
    for (char c : s) {
        sum += (c - '0');
    }
    return sum;
}
```
Time: O(d * log max_value) due to string conversion
Space: O(d) for temporary string
Status: Simpler code, but slightly slower and more space

Why Math Approach is Better:
- No string conversion overhead
- Direct digit extraction
- Constant space
- Slightly faster in practice

Bit Manipulation Note:
- Could use bit operations in some languages
- But decimal digit extraction requires modulo/division
- Bit operations not applicable here
- Stick with arithmetic approach

Common Mistakes to Avoid:

1. Not initializing min_element properly:
   - Wrong: int min_element = 0; (would fail for all positive digit sums)
   - Correct: int min_element = INT_MAX;

2. Modifying original array (if immutability required):
   - Our approach creates local variable: fine
   - If original nums array modified: use vector copy

3. Integer overflow (in sum calculation):
   - For 32-bit int, max value is ~2*10^9
   - Max digits: 10, each digit ≤ 9
   - Max digit sum: 10 * 9 = 90
   - No overflow risk for digit sum of 32-bit int
   - But be careful if extended to larger numbers

4. Off-by-one errors:
   - While loop condition: num > 0 (correct)
   - Stops when num becomes 0 (all digits processed)

5. Forgetting to initialize current_sum:
   - Wrong: int current_sum; (uninitialized)
   - Correct: int current_sum = 0;

Optimization Opportunities:

1. Early termination (if minimum digit sum is found to be 1):
   - Digit sum can never be 0 (except for 0 itself)
   - Digit sum of single digit number equals itself
   - Could skip remaining if min becomes 1
   - But typically not worth the extra check

2. Caching digit sums (if called multiple times):
   - Use unordered_map<int, int> for memoization
   - Trade space for time
   - Only beneficial if function called repeatedly with same inputs

3. Vectorization (for parallel processing):
   - SIMD operations on multiple elements
   - Compiler auto-vectorization might optimize this
   - Unlikely to provide significant speedup for this problem

Why This Problem Matters:

1. Teaches digit extraction techniques
2. Simple but fundamental algorithm
3. Builds foundation for more complex digit manipulation
4. Shows importance of proper initialization (INT_MAX)
5. Single-pass algorithm pattern

Related Problems (Digit Manipulation):
- Sum of Digits of String After Convert
- Sum of Digit Root
- Add Digits (iterative digit sum)
- Digital Root

Variants:

1. Return all digit sums (not just minimum):
   ```cpp
   vector<int> allDigitSums(vector<int>& nums) {
       vector<int> result;
       for (int num : nums) {
           result.push_back(digitSum(num));
       }
       return result;
   }
   ```

2. Find number with maximum digit sum:
   ```cpp
   int maxElement(vector<int>& nums) {
       int max_sum = INT_MIN;
       for (int num : nums) {
           max_sum = max(max_sum, digitSum(num));
       }
       return max_sum;
   }
   ```

3. Replace with digit sum recursively (digital root):
   ```cpp
   // Keep replacing until single digit
   int digitalRoot(int num) {
       while (num >= 10) {
           int sum = 0;
           while (num > 0) {
               sum += num % 10;
               num /= 10;
           }
           num = sum;
       }
       return num;
   }
   ```

4. Find elements with specific digit sum:
   ```cpp
   vector<int> findWithDigitSum(vector<int>& nums, int target) {
       vector<int> result;
       for (int num : nums) {
           if (digitSum(num) == target) {
               result.push_back(num);
           }
       }
       return result;
   }
   ```

Learning Points:

1. Modulo for digit extraction: num % 10
2. Division for removing digit: num / 10
3. Proper initialization: INT_MAX for minimum
4. Single-pass optimization: track min while computing
5. Loop termination: num > 0 for all digits
6. Time complexity analysis with logarithmic component
7. When to use arithmetic vs string approaches

This problem is straightforward but important for:
- Understanding basic digit manipulation
- Learning proper loop patterns
- Recognizing single-pass optimization opportunities
- Practicing complexity analysis
*/
