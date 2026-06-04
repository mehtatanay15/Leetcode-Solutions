// LeetCode 3751: Total Waviness of a Number Range
// Problem: Count peaks and valleys in digit sequences across range
// A peak: digit greater than both neighbors
// A valley: digit less than both neighbors
// Approach: Iterate range, check each middle digit for peak/valley property

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalWaviness(int num1, int num2) {
        int total_waviness = 0;
        
        // Loop through the inclusive range of numbers
        for (int num = num1; num <= num2; ++num) {
            string s = to_string(num);
            int len = s.length();
            
            // Numbers with fewer than 3 digits have 0 waviness
            if (len < 3) continue;
            
            // Loop through the digits, skipping the first (0) and last (len-1)
            for (int i = 1; i < len - 1; ++i) {
                // Check for peak: digit greater than both neighbors
                if (s[i] > s[i - 1] && s[i] > s[i + 1]) {
                    total_waviness++;
                }
                // Check for valley: digit less than both neighbors
                else if (s[i] < s[i - 1] && s[i] < s[i + 1]) {
                    total_waviness++;
                }
            }
        }
        
        return total_waviness;
    }
};

/*
Time Complexity: O((num2 - num1) * d) where:
  - (num2 - num1) = number of integers to process
  - d = average number of digits per integer
  - For each number: convert to string O(d) + check digits O(d)
  - Total: O((num2 - num1) * d)

Space Complexity: O(d)
  - String conversion allocates temporary string of length d
  - No additional data structures
  - d is number of digits in largest number

Algorithm Explanation:

Problem Overview:
Given a range [num1, num2], count total peaks and valleys across all numbers.

Definitions:
- Peak: A digit is a peak if it's greater than both its neighbors
- Valley: A digit is a valley if it's less than both its neighbors
- Waviness: Sum of all peaks and valleys in the range

Why String Conversion:
- Need to access individual digits
- String indexing gives easy character access
- Character comparison works (s[i] compares ASCII values, which represent digit order)

Key Insight - Only Check Middle Digits:
- First digit: no left neighbor, can't be peak/valley
- Last digit: no right neighbor, can't be peak/valley
- Only digits at positions 1 to len-2 can be peak/valley
- Loop range: i from 1 to len-1 (exclusive upper bound)

Why Numbers < 3 Digits Have 0 Waviness:
- 1-digit number: no neighbors at all
- 2-digit number: each digit has at most 1 neighbor
- Can't have peak (needs 2 neighbors)
- Can't have valley (needs 2 neighbors)
- Must have >= 3 digits for any peak/valley to exist

Example 1: num1=123, num2=127

Number 123:
- String: "123"
- Length: 3
- Check digit at i=1 (value '2'):
  - Left neighbor: '1', Right neighbor: '3'
  - '2' > '1'? Yes, '2' > '3'? No → Not a peak
  - '2' < '1'? No → Not a valley
- Waviness for 123: 0

Number 124:
- String: "124"
- Length: 3
- Check digit at i=1 (value '2'):
  - Left neighbor: '1', Right neighbor: '4'
  - '2' > '1'? Yes, '2' > '4'? No → Not a peak
  - '2' < '1'? No → Not a valley
- Waviness for 124: 0

Number 125:
- String: "125"
- Length: 3
- Check digit at i=1 (value '2'):
  - '2' > '1'? Yes, '2' > '5'? No → Not a peak
- Waviness for 125: 0

Number 126:
- String: "126"
- Length: 3
- Check digit at i=1 (value '2'):
  - '2' > '1'? Yes, '2' > '6'? No → Not a peak
- Waviness for 126: 0

Number 127:
- String: "127"
- Length: 3
- Check digit at i=1 (value '2'):
  - '2' > '1'? Yes, '2' > '7'? No → Not a peak
- Waviness for 127: 0

Total waviness: 0 + 0 + 0 + 0 + 0 = 0 ✓

Example 2: num1=131, num2=135

Number 131:
- String: "131"
- Check i=1 (value '3'):
  - '3' > '1'? Yes, '3' > '1'? Yes → PEAK!
  - total_waviness = 1

Number 132:
- String: "132"
- Check i=1 (value '3'):
  - '3' > '1'? Yes, '3' > '2'? Yes → PEAK!
  - total_waviness = 2

Number 133:
- String: "133"
- Check i=1 (value '3'):
  - '3' > '1'? Yes, '3' > '3'? No → Not a peak
  - total_waviness = 2

Number 134:
- String: "134"
- Check i=1 (value '3'):
  - '3' > '1'? Yes, '3' > '4'? No → Not a peak
  - total_waviness = 2

Number 135:
- String: "135"
- Check i=1 (value '3'):
  - '3' > '1'? Yes, '3' > '5'? No → Not a peak
  - total_waviness = 2

Total: 2 ✓

Example 3: num1=212, num2=215

Number 212:
- String: "212"
- Check i=1 (value '1'):
  - '1' > '2'? No
  - '1' < '2'? Yes, '1' < '1'? No → Not a valley
  - total_waviness = 0

Number 213:
- String: "213"
- Check i=1 (value '1'):
  - '1' > '2'? No
  - '1' < '2'? Yes, '1' < '3'? Yes → VALLEY!
  - total_waviness = 1

Number 214:
- String: "214"
- Check i=1 (value '1'):
  - '1' < '2'? Yes, '1' < '4'? Yes → VALLEY!
  - total_waviness = 2

Number 215:
- String: "215"
- Check i=1 (value '1'):
  - '1' < '2'? Yes, '1' < '5'? Yes → VALLEY!
  - total_waviness = 3

Total: 3 ✓

Example 4: num1=1234, num2=1237

Number 1234:
- String: "1234"
- Check i=1 (value '2'):
  - '2' > '1'? Yes, '2' > '3'? No → Not a peak
  - '2' < '1'? No → Not a valley
- Check i=2 (value '3'):
  - '3' > '2'? Yes, '3' > '4'? No → Not a peak
  - '3' < '2'? No → Not a valley
- Waviness: 0

Number 1235:
- String: "1235"
- Check i=1 (value '2'):
  - '2' > '1'? Yes, '2' > '3'? No → Not a peak
  - '2' < '1'? No → Not a valley
- Check i=2 (value '3'):
  - '3' > '2'? Yes, '3' > '5'? No → Not a peak
- Waviness: 0

Number 1236:
- String: "1236"
- Similar analysis
- Waviness: 0

Number 1237:
- String: "1237"
- Similar analysis
- Waviness: 0

Total: 0 ✓

Example 5: num1=131415, num2=131415 (single number with multiple peaks/valleys)

Number 131415:
- String: "131415"
- Length: 6
- Check i=1 (value '3'):
  - '3' > '1'? Yes, '3' > '1'? Yes → PEAK! (position 1)
  - total = 1
- Check i=2 (value '1'):
  - '1' < '3'? Yes, '1' < '4'? Yes → VALLEY! (position 2)
  - total = 2
- Check i=3 (value '4'):
  - '4' > '1'? Yes, '4' > '1'? Yes → PEAK! (position 3)
  - total = 3
- Check i=4 (value '1'):
  - '1' < '4'? Yes, '1' < '5'? Yes → VALLEY! (position 4)
  - total = 4

Total: 4 ✓

This shows alternating peaks and valleys create high waviness.

Example 6: num1=1, num2=10

Number 1: 1 digit, skip
Number 2: 1 digit, skip
...
Number 9: 1 digit, skip
Number 10: 2 digits, skip (need >= 3)

Total: 0

All single and double digit numbers have waviness 0.

Example 7: num1=100, num2=101

Number 100:
- String: "100"
- Check i=1 (value '0'):
  - '0' > '1'? No
  - '0' < '1'? Yes, '0' < '0'? No → Not a valley
- Waviness: 0

Number 101:
- String: "101"
- Check i=1 (value '0'):
  - '0' < '1'? Yes, '0' < '1'? Yes → VALLEY!
- Waviness: 1

Total: 1 ✓

Example 8: num1=909, num2=912

Number 909:
- String: "909"
- Check i=1 (value '0'):
  - '0' < '9'? Yes, '0' < '9'? Yes → VALLEY!
- Waviness: 1

Number 910:
- String: "910"
- Check i=1 (value '1'):
  - '1' < '9'? Yes, '1' < '0'? No → Not a valley
- Waviness: 0

Number 911:
- String: "911"
- Check i=1 (value '1'):
  - '1' < '9'? Yes, '1' < '1'? No → Not a valley
- Waviness: 0

Number 912:
- String: "912"
- Check i=1 (value '1'):
  - '1' < '9'? Yes, '1' < '2'? Yes → VALLEY!
- Waviness: 1

Total: 1 + 0 + 0 + 1 = 2 ✓

Edge Cases Handled:

1. Single digit range (num1=num2=5):
   - Number 5: 1 digit, skipped
   - Result: 0 ✓

2. Two digit range (num1=10, num2=99):
   - All 2-digit numbers
   - All skipped (< 3 digits)
   - Result: 0 ✓

3. First 3-digit number (100):
   - Digits: 1, 0, 0
   - Middle digit 0: not peak (0 < 0 is false), not valley (0 not < 1)
   - Result: 0 ✓

4. Number with repeated digits (111):
   - Middle digit: not peak (1 > 1 is false), not valley (1 < 1 is false)
   - Result: 0 ✓

5. Maximum peaks/valleys (alternating):
   - 101010... pattern: many valleys and peaks
   - Correctly counted

Why This Algorithm Works:

1. Character Comparison:
   - '0' < '1' < '2' ... < '9' in ASCII
   - Comparing characters directly gives correct digit order

2. Exhaustive Check:
   - Check every number in range
   - Check every middle digit in each number
   - No optimization or shortcuts

3. Clear Peak/Valley Definition:
   - Peak: strictly greater than both neighbors
   - Valley: strictly less than both neighbors
   - Not >= or <=, must be strict inequality

Alternative Approaches:

1. Mathematical approach (digit extraction):
```cpp
while (num > 0) {
    int digit = num % 10;
    num /= 10;
    // Process digit
}
```
- More complex (digits extracted in reverse)
- Same time complexity

2. Digit DP (dynamic programming):
- Optimizes counting in a range
- More complex code
- Better for very large ranges
- Overkill for normal constraints

3. Precomputation:
- Precompute waviness for all numbers up to 10^9
- Fast queries but requires preprocessing
- Not practical

Why String Approach is Best:
- Simplest and clearest code
- Direct digit access
- Easy to understand and debug
- Sufficient for typical constraints

Performance Considerations:

For range [num1, num2]:
- If range is large (10^9 numbers):
  - 10^9 * 10 digits ≈ 10^10 operations
  - Might be too slow
  - Would need digit DP optimization

For typical constraints (range ≤ 10^5):
- 10^5 numbers * 10 digits ≈ 10^6 operations
- Completes in < 10ms

Optimization Opportunity (if needed):

Digit DP:
```cpp
// Count waviness from 0 to n using digit DP
// State: (position, tight, previous_digit, current_digit)
// Transitions: try each digit at current position
```
- Time: O(d^2 * 10) where d is digits
- Space: O(d^2)
- For ranges [num1, num2]: answer(num2) - answer(num1-1)

For this problem:
- String iteration is simpler
- Sufficient efficiency
- Easier to understand

Common Mistakes to Avoid:

1. Checking first or last digit:
   - These can't be peaks/valleys (missing one neighbor)
   - Loop must start at 1, end at len-2

2. Using >= or <= instead of > and <:
   - Need strict inequality for peak/valley
   - 2 is not a peak if neighbors are 2, 3

3. Confusing peak and valley:
   - Peak: high point (greater than neighbors)
   - Valley: low point (less than neighbors)

4. Not converting to string:
   - Could use digit extraction with modulo
   - But string is simpler and clearer

5. Off-by-one in loop:
   - for (int i = 1; i < len - 1; ++i) is correct
   - Starting at 0 or ending at len would be wrong

Why This Problem Matters:

1. Teaches character/digit comparison
2. Shows when to use string conversion
3. Simple pattern recognition (peaks and valleys)
4. Good for string and number manipulation practice
5. Real-world application: signal processing, data analysis

When to Use This Approach:

1. Digit-level analysis needed
2. String representation helpful
3. Range iteration required
4. Straightforward enumeration

Real-world Applications:

1. Time series analysis: find peaks and valleys in data
2. Signal processing: identify local extrema
3. Stock price analysis: find local highs and lows
4. Terrain analysis: find ridges and valleys
5. Data quality: identify anomalies in sequences

Related Problems (Digit/Character Analysis):
- Valid Number (character classification)
- First Unique Character (character frequency)
- Zigzag Conversion (arrangement pattern)
- Delete and Earn (digit/value consideration)

Variants:

1. Count only peaks (ignore valleys):
```cpp
if (s[i] > s[i-1] && s[i] > s[i+1])
    total_peaks++;
```

2. Count only valleys (ignore peaks):
```cpp
if (s[i] < s[i-1] && s[i] < s[i+1])
    total_valleys++;
```

3. Return maximum consecutive peaks/valleys:
```cpp
// Track streak of alternating peaks/valleys
```

4. Find numbers with most peaks/valleys:
```cpp
// Store (number, waviness) pairs
// Return top k
```

Learning Points:

1. String conversion for digit access
2. Character comparison in C++
3. Loop boundary selection
4. Peak and valley definitions
5. Range enumeration patterns
6. Time complexity analysis
7. Edge cases with number ranges
8. When string approach beats digit math

This problem teaches:
- Simple but systematic approach
- Character manipulation
- Clear problem understanding
- Enumeration without optimization
- When optimization isn't needed

Complexity Analysis:

Time:
- Outer loop: (num2 - num1 + 1) iterations
- Inner loop: d iterations (d = digits in num)
- Per iteration: O(1) comparisons
- Total: O((num2 - num1) * d)

Space:
- String: O(d)
- No other allocations
- Total: O(d)

Practical Performance:

For range size:
- 10: < 1μs
- 100: < 10μs
- 1,000: < 100μs
- 10,000: < 1ms
- 100,000: < 10ms
- 1,000,000: < 100ms
- 10,000,000: < 1s

String conversion overhead is minimal.

Final Notes:

This is a good problem because:
- Clear problem statement
- Simple solution
- Good for learning string/digit handling
- Shows when enumeration is acceptable
- Interview-friendly difficulty

The key insight:
- Character comparison works for digits
- String provides easy digit access
- Check only middle positions
- Count peaks and valleys

This problem would require optimization if:
- Range exceeds 10^7 (use digit DP)
- Need to answer many queries (precompute)
- Range boundaries are very large

But for typical constraints, simple iteration is perfect.
*/
